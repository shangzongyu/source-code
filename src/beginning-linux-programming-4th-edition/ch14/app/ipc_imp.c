/* First, we include the appropriate headers, declare some message queue keys and define#
 a structure to hold our message data. */

#include "cd_data.h"
#include "cliserv.h"

#include <sys/msg.h>

#define SERVER_MQUEUE 1234
#define CLIENT_MQUEUE 4321

struct msg_passed {
    long int msg_key; /* used for client pid */
    message_db_t real_message;
};

/* Two variables with file scope hold the two queue identifiers returned from the
 msgget function. */

static int serv_qid = -1;
static int cli_qid = -1;

/* We make the server responsible for creating both message queues. */

int server_starting()
{
    #if DEBUG_TRACE
        printf("%d :- server_starting()\n",  getpid());
    #endif

    serv_qid = msgget((key_t)SERVER_MQUEUE, 0666 | IPC_CREAT);
    if (serv_qid == -1) return(0);

    cli_qid = msgget((key_t)CLIENT_MQUEUE, 0666 | IPC_CREAT);
    if (cli_qid == -1) return(0);

    return(1);
}

/* The server is also responsible for tidying up if it ever exits. When the server ends,
 we set our file scope variables to illegal values. This will catch any bugs if the server
 attempts to send messages after it has called server_ending. */

void server_ending()
{
    #if DEBUG_TRACE
        printf("%d :- server_ending()\n",  getpid());
    #endif

    (void)msgctl(serv_qid, IPC_RMID, 0);
    (void)msgctl(cli_qid, IPC_RMID, 0);

    serv_qid = -1;
    cli_qid = -1;
}

/* The server read function reads a message of any type (that is, from any client)
 from the queue, and returns the data part (ignoring the type) of the message. */

int read_request_from_client(message_db_t *rec_ptr)
{
    struct msg_passed my_msg;
    #if DEBUG_TRACE
        printf("%d :- read_request_from_client()\n",  getpid());
    #endif

    if (msgrcv(serv_qid, (void *)&my_msg, sizeof(*rec_ptr), 0, 0) == -1) {
        return(0);
    }
    *rec_ptr = my_msg.real_message;
    return(1);
}

/* Sending a response uses the client process ID that was stored in the request to address
 the message. */

int send_resp_to_client(const message_db_t mess_to_send)
{
    struct msg_passed my_msg;
    #if DEBUG_TRACE
        printf("%d :- send_resp_to_client()\n",  getpid());
    #endif

    my_msg.real_message = mess_to_send;
    my_msg.msg_key = mess_to_send.client_pid;

    if (msgsnd(cli_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1) {
        return(0);
    }
    return(1);
}

/* When the client starts, it needs to find the server and client queue identifiers.
 The client doesn't create the queues. This function will fail if the server isn't running,
 as the message queues won't exist. */

int client_starting()
{
    #if DEBUG_TRACE
        printf("%d :- client_starting\n",  getpid());
    #endif

    serv_qid = msgget((key_t)SERVER_MQUEUE, 0666);
    if (serv_qid == -1) return(0);

    cli_qid = msgget((key_t)CLIENT_MQUEUE, 0666);
    if (cli_qid == -1) return(0);
    return(1);
}

/* As with the server, when the client ends, we set our file scope variables to
 illegal values. This will catch any bugs where the client attempts to send messages
 after it has called client_ending. */

void client_ending()
{
    #if DEBUG_TRACE
        printf("%d :- client_ending()\n",  getpid());
    #endif

    serv_qid = -1;
    cli_qid = -1;
}

/* To send a message to the server, we store the data inside our structure.
 Notice that we must set the message key. As 0 is an illegal value for the key,
 leaving the key undefined would mean that it takes an (apparently) random value,
 so this function could occasionally fail if the value happens to be 0. */

int send_mess_to_server(message_db_t mess_to_send)
{
    struct msg_passed my_msg;
    #if DEBUG_TRACE
        printf("%d :- send_mess_to_server()\n",  getpid());
    #endif

    my_msg.real_message = mess_to_send;
    my_msg.msg_key = mess_to_send.client_pid;

    if (msgsnd(serv_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1) {
        perror("Message send failed");
        return(0);
    }
    return(1);
}

/* When the client retrieves a message from the server, it uses its process ID to
 receive only messages addressed to itself, ignoring any messages for other clients. */

int read_resp_from_server(message_db_t *rec_ptr)
{
    struct msg_passed my_msg;
    #if DEBUG_TRACE
        printf("%d :- read_resp_from_server()\n",  getpid());
    #endif

    if (msgrcv(cli_qid, (void *)&my_msg, sizeof(*rec_ptr), getpid(), 0) == -1) {
        return(0);
    }
    *rec_ptr = my_msg.real_message;
    return(1);
}

/* To retain complete compatibility with pipe_imp.c, we need to define an extra four
 functions. In our new program, however, the functions are empty. The operations they
 implemented when using pipes are simply not needed any more. */

int start_resp_to_client(const message_db_t mess_to_send)
{
    return(1);
}

void end_resp_to_client(void)
{
}

int start_resp_from_server(void)
{
    return(1);
}

void end_resp_from_server(void)
{
}
