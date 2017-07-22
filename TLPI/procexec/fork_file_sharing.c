#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
int main(int argc,char * argv[]){
	int fd,flags;
	fd=open("test.txt",O_RDWR,NULL);
	setbuf(stdout,NULL);
	printf("file offest before fork:%lld\n",(long long)lseek(fd,0,SEEK_CUR));
	flags=fcntl(fd,F_GETFL);
	printf("O_APPEND before the fork:%s\n",(flags&O_APPEND)?"on":"off");
	switch(fork()){
	case -1:
		printf("fork error\n");
		break;
	case 0:
		lseek(fd,1000,SEEK_SET);
		flags=fcntl(fd,F_GETFL);
		flags|=O_APPEND;
		fcntl(fd,F_SETFL,flags);
		_exit(EXIT_SUCCESS);
	default:
		wait(NULL);
		printf("control power have handed over to parent\n");
		printf("file offset after fork:%lld\n",(long long)lseek(fd,0,SEEK_CUR));
		flags=fcntl(fd,F_GETFL);
		printf("O_APPEND after fork:%s\n",(flags&O_APPEND)?"on":"off");
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}