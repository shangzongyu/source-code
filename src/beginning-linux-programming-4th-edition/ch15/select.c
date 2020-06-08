/*  Begin as usual with the includes and declarations
    and then initialize inputs to handle input from the keyboard.  */

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char buffer[128];
    int result, nread;

    fd_set inputs, testfds;
    struct timeval timeout;

    FD_ZERO(&inputs);
    FD_SET(0,&inputs);

/*  Wait for input on stdin for a maximum of 2.5 seconds.  */

    while(1) {
        testfds = inputs;
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;

        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, &timeout);

/*  After this time, we test result. If there has been no input, the program loops again.
    If there has been an error, the program exits.  */

        switch(result) {
        case 0:
            printf("timeout\n");
            break;
        case -1:
            perror("select");
            exit(1);

/*  If, during the wait, we have some action on the file descriptor,
    we read the input on stdin and echo it whenever an <end of line> character is received,
    until that input is Ctrl-D.  */

        default:
            if(FD_ISSET(0,&testfds)) {
                ioctl(0,FIONREAD,&nread);
                if(nread == 0) {
                    printf("keyboard done\n");
                    exit(0);
                }
                nread = read(0,buffer,nread);
                buffer[nread] = 0;
                printf("read %d from keyboard: %s", nread, buffer);
            }
            break;
        }
    }
}

