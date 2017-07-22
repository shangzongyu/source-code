#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char * argv[],char ** environ){
	int i;
	printf("running after the execve()\n");
	printf(" pid=%d,  parent pid=%d\n",getpid(),getppid());
	printf(" uid=%d,  gid=%d\n",getuid(),getpid());
	printf("the immage over\n");
	exit(0);
}