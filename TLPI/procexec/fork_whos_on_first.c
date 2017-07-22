#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
int main(int argc,char *argv[]){

	int numberChild;
	int i;
	
	numberChild=atoi(argv[1]);
	setbuf(stdout,NULL);
	for(int i=0;i<numberChild;i++){
		switch(fork()){
		case -1:
		printf("fork error\n");
		break;
		
		case 0:
			printf("%d child \n",i);
			_exit(EXIT_SUCCESS);
		default:
			printf("%d parent \n",i);
			wait(NULL);
			break;
		}
		
	}
	
	
	exit(EXIT_SUCCESS);

}