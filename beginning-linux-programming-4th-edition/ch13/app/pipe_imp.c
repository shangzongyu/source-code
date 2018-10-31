/* Include files */

#include "cd_data.h"
#include "cliserv.h"

/* define some values that we need in different functions within the file. */

static int server_fd = -1;
static pid_t mypid = 0;
static char client_pipe_name[PATH_MAX + 1] = {'\0'};
static int client_fd = -1;
static int client_write_fd = -1;

/*
The server_starting routine creates the named pipe from which the server will read commands.
It then opens it for reading. This open will block until a client opens the pipe for writing.
We use a blocking mode, so that the server can perform blocking reads on the pipe while waiting for commands to be sent to it.
*/

int server_starting(void)
{
    #if DEBUG_TRACE    
        printf("%d :- server_starting()\n",  getpid());
    #endif

    	unlink(SERVER_PIPE);
    if (mkfifo(SERVER_PIPE, 0777) == -1) {
        fprintf(stderr, "Server startup error, no FIFO created\n");
        return(0);
    }

    if ((server_fd = open(SERVER_PIPE, O_RDONLY)) == -1) {
        fprintf(stderr, "Server startup error, no FIFO opened\n");
        return(0);
    }
    return(1);
}

/* When the server ends, it removes the named pipe, so clients can detect that no server is running. */

void server_ending(void)
{
    #if DEBUG_TRACE    
        printf("%d :- server_ending()\n",  getpid());
    #endif

    (void)close(server_fd);
    (void)unlink(SERVER_PIPE);
}

/* The read_request_from_client function, shown below, will block reading the server pipe until a client writes a message into it. */

int read_request_from_client(message_db_t *rec_ptr)
{
    int return_code = 0;
    int read_bytes;

    #if DEBUG_TRACE    
        printf("%d :- read_request_from_client()\n",  getpid());
    #endif

    if (server_fd != -1) {
        read_bytes = read(server_fd, rec_ptr, sizeof(*rec_ptr)); 

	/*
In the special case when no clients have the pipe open for writing, the read will return 0, i.e. it detects an EOF.
Then the server closes the pipe and opens it again, so that it blocks until a client also opens the pipe.
This is just the same as when the server first starts; we have re-initialized the server.
*/
        if (read_bytes == 0) {
            (void)close(server_fd);
            if ((server_fd = open(SERVER_PIPE, O_RDONLY)) == -1) {
               fprintf(stderr, "Server error, FIFO open failed\n");
               return(0);
            }
            read_bytes = read(server_fd, rec_ptr, sizeof(*rec_ptr));
        }
        if (read_bytes == sizeof(*rec_ptr)) return_code = 1;
    }
    return(return_code);
}

/* open the client pipe. */

int start_resp_to_client(const message_db_t mess_to_send)
{
    #if DEBUG_TRACE
        printf("%d :- start_resp_to_client()\n", getpid());
    #endif

    (void)sprintf(client_pipe_name, CLIENT_PIPE, mess_to_send.client_pid);
    if ((client_fd = open(client_pipe_name, O_WRONLY)) == -1) return(0);
    return(1);
}

/*
The messages are all sent using calls to this function.
We'll look at the corresponding client-side functions that field the message soon.
*/

int send_resp_to_client(const message_db_t mess_to_send)
{
    int write_bytes;

    #if DEBUG_TRACE
        printf("%d :- send_resp_to_client()\n", getpid());
    #endif

    if (client_fd == -1) return(0);
    write_bytes = write(client_fd, &mess_to_send, sizeof(mess_to_send));
    if (write_bytes != sizeof(mess_to_send)) return(0);
    return(1);
}

/* close the client pipe. */

void end_resp_to_client(void)
{
    #if DEBUG_TRACE
        printf("%d :- end_resp_to_client()\n",  getpid());
    #endif

    if (client_fd != -1) {
        (void)close(client_fd);
        client_fd = -1;
    }
}

/* After checking that a server is accessible, the client_starting function initializes the client-side pipe. */

int client_starting(void)
{
    #if DEBUG_TRACE
        printf("%d :- client_starting\n",  getpid());
    #endif

    mypid = getpid();
    if ((server_fd = open(SERVER_PIPE, O_WRONLY)) == -1) {
        fprintf(stderr, "Server not running\n");
        return(0);
    }

    (void)sprintf(client_pipe_name, CLIENT_PIPE, mypid);
    (void)unlink(client_pipe_name);
    if (mkfifo(client_pipe_name, 0777) == -1) {
        fprintf(stderr, "Unable to create client pipe %s\n", 
                   client_pipe_name);
        return(0);
    }
    return(1);
}

/* The client_ending function closes file descriptors and deletes the now redundant named pipe. */

void client_ending(void)
{
    #if DEBUG_TRACE    
        printf("%d :- client_ending()\n",  getpid()); 
    #endif

    if (client_write_fd != -1) (void)close(client_write_fd);
    if (client_fd != -1) (void)close(client_fd);
    if (server_fd != -1) (void)close(server_fd);
    (void)unlink(client_pipe_name);
}

/* The send_mess_to_server function passes the request through the server pipe. */

int send_mess_to_server(message_db_t mess_to_send)
{
    int write_bytes;

    #if DEBUG_TRACE    
        printf("%d :- send_mess_to_server()\n",  getpid());
    #endif

    if (server_fd == -1) return(0);
    mess_to_send.client_pid = mypid;
    write_bytes = write(server_fd, &mess_to_send, sizeof(mess_to_send));
    if (write_bytes != sizeof(mess_to_send)) return(0);
    return(1);
}

/* This client function starts to listen for the server response.
It opens a client pipe as read-only and then reopens this pipe's file as write-only.
We'll see why in a moment.
*/

int start_resp_from_server(void)
{
    #if DEBUG_TRACE    
        printf("%d :- start_resp_from_server()\n",  getpid());    
    #endif

    if (client_pipe_name[0] == '\0') return(0);
    if (client_fd != -1) return(1);

    client_fd = open(client_pipe_name, O_RDONLY);
    if (client_fd != -1) {
        client_write_fd = open(client_pipe_name, O_WRONLY);
        if (client_write_fd != -1) return(1);
        (void)close(client_fd);
        client_fd = -1;
    }
    return(0);
}

/* Here's the main read from the server which gets the matching database entries. */

int read_resp_from_server(message_db_t *rec_ptr)
{
    int read_bytes;
    int return_code = 0;

    #if DEBUG_TRACE    
        printf("%d :- read_resp_from_server()\n",  getpid());    
    #endif

    if (!rec_ptr) return(0);
    if (client_fd == -1) return(0);

    read_bytes = read(client_fd, rec_ptr, sizeof(*rec_ptr));
    if (read_bytes == sizeof(*rec_ptr)) return_code = 1;
    return(return_code);
}

/* And finally, the client function that marks the end of the server response. */

void end_resp_from_server(void)
{
    #if DEBUG_TRACE    
        printf("%d :- end_resp_from_server()\n",  getpid());        
    #endif

    /* This function is empty in the pipe implementation */
}

