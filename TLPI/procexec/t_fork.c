#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
static int date=111;
int main(int argc,char * argv[]){
	int stack=222;
	
	pid_t child_pid;
	
	switch(child_pid=fork()){
	case -1:
		printf("fork is error!!!\n");
	case 0:
		printf("child");
		stack*=3;
		date*=3;
		break;
	default:
		printf("parent");
		break;
	
	}
	
	printf("pid=%ld date=%d stack=%d\n",(long)getpid(),date,stack);
	
	
	
	exit(EXIT_SUCCESS);
}