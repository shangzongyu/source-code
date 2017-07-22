#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char * argv[]){
	char * argVec[10];
	char * envVec[]={"环境变量1","环境变量2",NULL};
	argVec[0]=argv[0];
	argVec[1]=argv[1];
	argVec[2]="参数1";
	execve(argv[1],argVec,envVec);
	printf("the progress can't to here\n");
	exit(EXIT_SUCCESS);
}

