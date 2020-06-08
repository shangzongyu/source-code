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

/* userns_child_exec.c

   Create a child process that executes a shell command in new
   namespace(s); allow UID and GID mappings to be specified when
   creating a user namespace.

   See https://lwn.net/Articles/532593/
*/
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#ifndef CLONE_NEWCGROUP         /* Added in Linux 4.6 */
#define CLONE_NEWCGROUP         0x02000000
#endif

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

struct child_args {
    char **argv;        /* Command to be executed by child, with args */
    int    pipe_fd[2];  /* Pipe used to synchronize parent and child */
};

static int verbose;

static void
usage(char *pname)
{
    fprintf(stderr, "Usage: %s [options] cmd [arg...]\n\n", pname);
    fprintf(stderr, "Create a child process that executes a shell "
            "command in a new user namespace,\n"
            "and possibly also other new namespace(s).\n\n");
    fprintf(stderr, "Options can be:\n\n");
#define fpe(str) fprintf(stderr, "    %s", str);
    fpe("-C          New cgroup namespace\n");
    fpe("-i          New IPC namespace\n");
    fpe("-m          New mount namespace\n");
    fpe("-n          New network namespace\n");
    fpe("-p          New PID namespace\n");
    fpe("-u          New UTS namespace\n");
    fpe("-U          New user namespace\n");
    fpe("-M uid_map  Specify UID map for user namespace\n");
    fpe("-G gid_map  Specify GID map for user namespace\n");
    fpe("-D          Do not write \"deny\" to /proc/PID/setgroups before\n");
    fpe("            updating GID map\n");
    fpe("-z          Map user's UID and GID to 0 in user namespace\n");
    fpe("            (equivalent to: -M '0 <uid> 1' -G '0 <gid> 1')\n");
    fpe("-v          Display verbose messages\n");
    fpe("\n");
    fpe("If -z, -M, or -G is specified, -U is required.\n");
    fpe("It is not permitted to specify both -z and either -M or -G.\n");
    fpe("\n");
    fpe("Map strings for -M and -G consist of records of the form:\n");
    fpe("\n");
    fpe("    ID-inside-ns   ID-outside-ns   len\n");
    fpe("\n");
    fpe("A map string can contain multiple records, separated"
        " by commas;\n");
    fpe("the commas are replaced by newlines before writing"
        " to map files.\n");

    exit(EXIT_FAILURE);
}

/* Update the mapping file 'map_file', with the value provided in
   'mapping', a string that defines a UID or GID mapping. A UID or
   GID mapping consists of one or more newline-delimited records
   of the form:

       ID_inside-ns    ID-outside-ns   length

   Requiring the user to supply a string that contains newlines is
   of course inconvenient for command-line use. Thus, we permit the
   use of commas to delimit records in this string, and replace them
   with newlines before writing the string to the file. */

static void
update_map(char *mapping, char *map_file)
{
    int fd, j;
    size_t map_len;     /* Length of 'mapping' */

    /* Replace commas in mapping string with newlines */

    map_len = strlen(mapping);
    for (j = 0; j < map_len; j++)
        if (mapping[j] == ',')
            mapping[j] = '\n';

    fd = open(map_file, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "ERROR: open %s: %s\n", map_file, strerror(errno));
        return;
        //exit(EXIT_FAILURE);
    }

    if (write(fd, mapping, map_len) != map_len) {
        fprintf(stderr, "ERROR: write %s: %s\n", map_file, strerror(errno));
        //exit(EXIT_FAILURE);
    }

    close(fd);
}

/* Linux 3.19 made a change in the handling of setgroups(2) and the
   'gid_map' file to address a security issue. The issue allowed
   *unprivileged* users to employ user namespaces in order to drop
   groups from their supplementary group list using setgroups(2).
   (Formerly, this possibility was available only to privileged
   processes.) The effect was to create possibilities for unprivileged
   process to access files for which they would not otherwise have had
   permission. (For further details, see the user_namespaces(7) man
   page.)

   The upshot of the 3.19 changes is that in order for a process lacking
   suitable privileges (i.e., one that lacks the CAP_SETGID capability
   in the parent user namespace) to update the 'gid_maps' file, use of the
   setgroups() system call in this user namespace must first be
   disabled by writing "deny" to one of the /proc/PID/setgroups files
   for this namespace.  That is the purpose of the following function. */

static void
proc_setgroups_write(pid_t child_pid, char *str)
{
    char setgroups_path[PATH_MAX];
    int fd;

    snprintf(setgroups_path, PATH_MAX, "/proc/%ld/setgroups",
            (long) child_pid);

    fd = open(setgroups_path, O_RDWR);
    if (fd == -1) {

        /* We may be on a system that doesn't support
           /proc/PID/setgroups. In that case, the file won't exist,
           and the system won't impose the restrictions that Linux 3.19
           added. That's fine: we don't need to do anything in order
           to permit 'gid_map' to be updated.

           However, if the error from open() was something other than
           the ENOENT error that is expected for that case, let the
           user know. */

        if (errno != ENOENT)
            fprintf(stderr, "ERROR: open %s: %s\n", setgroups_path,
                strerror(errno));
        return;
    }

    if (verbose)
        printf("Writing to \"%s\" to %s\n", str, setgroups_path);

    if (write(fd, str, strlen(str)) == -1)
        fprintf(stderr, "ERROR: write %s: %s\n", setgroups_path,
            strerror(errno));

    close(fd);
}

static int              /* Start function for cloned child */
childFunc(void *arg)
{
    struct child_args *args = (struct child_args *) arg;
    char ch;

    /* Wait until the parent has updated the UID and GID mappings.
       See the comment in main(). We wait for end of file on a
       pipe that will be closed by the parent process once it has
       updated the mappings. */

    close(args->pipe_fd[1]);    /* Close our descriptor for the write
                                   end of the pipe so that we see EOF
                                   when parent closes its descriptor */
    if (read(args->pipe_fd[0], &ch, 1) != 0) {
        fprintf(stderr,
                "Failure in child: read from pipe returned != 0\n");
        exit(EXIT_FAILURE);
    }

    close(args->pipe_fd[0]);    /* We no longer need the pipe */

    /* Execute a shell command */

    if (verbose)
        printf("About to exec: %s\n", args->argv[0]);

    execvp(args->argv[0], args->argv);
    errExit("execvp");
}

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];    /* Space for child's stack */

int
main(int argc, char *argv[])
{
    int flags, opt, map_zero, deny_setgroups;
    pid_t child_pid;
    struct child_args args;
    char *uid_map, *gid_map;
    const int MAP_BUF_SIZE = 100;
    char map_buf[MAP_BUF_SIZE];
    char map_path[PATH_MAX];

    /* Parse command-line options. The initial '+' character in
       the final getopt(3) argument prevents GNU-style permutation
       of command-line options. Preventing that is useful, since
       sometimes the 'command' to be executed by this program itself
       has command-line options. We don't want getopt() to treat
       those as options to this program. */

    flags = 0;
    verbose = 0;
    gid_map = NULL;
    uid_map = NULL;
    map_zero = 0;
    deny_setgroups = 1;
    while ((opt = getopt(argc, argv, "+CimnpuvzM:G:DU")) != -1) {
        switch (opt) {
        case 'C': flags |= CLONE_NEWCGROUP;     break;
        case 'i': flags |= CLONE_NEWIPC;        break;
        case 'm': flags |= CLONE_NEWNS;         break;
        case 'n': flags |= CLONE_NEWNET;        break;
        case 'p': flags |= CLONE_NEWPID;        break;
        case 'u': flags |= CLONE_NEWUTS;        break;
        case 'v': verbose = 1;                  break;
        case 'z': map_zero = 1;                 break;
        case 'M': uid_map = optarg;             break;
        case 'G': gid_map = optarg;             break;
        case 'D': deny_setgroups = 0;           break;
        case 'U': flags |= CLONE_NEWUSER;       break;
        default:  usage(argv[0]);
        }
    }

    /* -M or -G without -U is nonsensical */

    if (((uid_map != NULL || gid_map != NULL || map_zero) &&
                !(flags & CLONE_NEWUSER)) ||
            (map_zero && (uid_map != NULL || gid_map != NULL)))
        usage(argv[0]);

    if (optind >= argc)
        usage(argv[0]);

    args.argv = &argv[optind];

    /* We use a pipe to synchronize the parent and child, in order to
       ensure that the parent sets the UID and GID maps before the child
       calls execve(). This ensures that the child maintains its
       capabilities during the execve() in the common case where we
       want to map the child's effective user ID to 0 in the new user
       namespace. Without this synchronization, the child would lose
       its capabilities if it performed an execve() with nonzero
       user IDs (see the capabilities(7) man page for details of the
       transformation of a process's capabilities during execve()). */

    if (pipe(args.pipe_fd) == -1)
        errExit("pipe");

    /* Create the child in new namespace(s) */

    child_pid = clone(childFunc, child_stack + STACK_SIZE,
                      flags | SIGCHLD, &args);
    if (child_pid == -1)
        errExit("clone");

    /* Parent falls through to here */

    if (verbose)
        printf("%s: PID of child created by clone() is %ld\n",
                argv[0], (long) child_pid);

    /* Update the UID and GID maps in the child */

    if (uid_map != NULL || map_zero) {
        snprintf(map_path, PATH_MAX, "/proc/%ld/uid_map",
                (long) child_pid);
        if (map_zero) {
            snprintf(map_buf, MAP_BUF_SIZE, "0 %ld 1", (long) getuid());
            uid_map = map_buf;
        }
        update_map(uid_map, map_path);
    }

    if (gid_map != NULL || map_zero) {
        if (deny_setgroups)
            proc_setgroups_write(child_pid, "deny");

        snprintf(map_path, PATH_MAX, "/proc/%ld/gid_map",
                (long) child_pid);
        if (map_zero) {
            snprintf(map_buf, MAP_BUF_SIZE, "0 %ld 1", (long) getgid());
            gid_map = map_buf;
        }
        update_map(gid_map, map_path);
    }

    /* Close the write end of the pipe, to signal to the child that we
       have updated the UID and GID maps */

    close(args.pipe_fd[1]);

    if (waitpid(child_pid, NULL, 0) == -1)      /* Wait for child */
        errExit("waitpid");

    if (verbose)
        printf("%s: terminating\n", argv[0]);

    exit(EXIT_SUCCESS);
}
