#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int main(int argc,char * argv[],char ** environ){
	pid_t pid;
	printf("the example!!!\n");
	switch(fork()){
	case -1:
		printf("fork error\n");
		exit(EXIT_FAILURE);
	case 0:
		printf("child is running\n");
		printf("child pid=%d, child parent pid=%d\n",getpid(),getppid());
		printf("child uid=%d, child gid=%d\n",getuid(),getpid());
		execve(argv[1],argv,environ);
		printf("child can't in here\n");
		break;
	default:
		wait(NULL);
		printf("parent is running\n");
		break;
	}
	exit(EXIT_SUCCESS);
}