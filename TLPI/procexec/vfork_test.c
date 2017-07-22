#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int argc,char *argv[]){
	int date=111;
	
	switch(vfork()){
	case -1:
		printf("vfork error\n");
		exit(EXIT_FAILURE);
	case 0:
		date*=3;
		break;
	default:
		wait(NULL);
		printf("chils exited\n");
		break;
	}
	
	printf("after the vfork %d\n",date);
	exit(EXIT_SUCCESS);
}