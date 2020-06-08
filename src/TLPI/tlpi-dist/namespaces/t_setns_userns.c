/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter Z */

/* t_setns.c

   Attempt to join a user namespace using setns(), displaying
   process's credentials and capabilities before and after setns().
*/
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/capability.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

static void
display_creds_and_caps(char *msg)
{
    cap_t caps;

    printf("%seUID = %ld;  eGID = %ld;  ", msg,
            (long) geteuid(), (long) getegid());

    caps = cap_get_proc();
    printf("capabilities: %s\n", cap_to_text(caps, NULL));
}

int
main(int argc, char *argv[])
{
    int fd;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s /proc/PID/ns/FILE\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    display_creds_and_caps("Initial:\n");
    printf("\n");

    fd = open(argv[1], O_RDONLY); /* Get descriptor for namespace */
    if (fd == -1)
        errExit("open");

    if (setns(fd, CLONE_NEWUSER) == -1)  /* Join that namespace */
        errExit("setns-1");

    display_creds_and_caps("After setns():\n");
    exit(EXIT_SUCCESS);
}
