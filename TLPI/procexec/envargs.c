#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
extern char ** environ;
int main(int argc,char * argv[]){
	int i=0;
	char ** ep;
	printf("new progress\n");
	printf("参数\n");
	for(i=0;i<argc;i++)
		printf("\t%s\n",argv[i]);
	printf("环境变量：\n");
	for(ep=environ;*ep!=NULL;ep++)
		printf("\t%s\n",*ep);
	printf("new progress over\n");
	exit(EXIT_SUCCESS);
	return 0;
}