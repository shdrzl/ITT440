#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define SIZE 6
void sig_handler(int signum);

int main(void) 
{
	signal(SIGINT,sig_handler); //signal handler
	while(1) 
	{
		int fd[2];
		char num[SIZE + 1];
		char buffer[SIZE + 1];
		pipe(fd);
		int id = fork();

		if(id == 0) 
		{ //parent process
			printf("\n\n- - - - PARENT PROCESS - - - - \n");
			printf("Input 6 numbers ( 1 - 9):\n");
			for(int i = 0; i < SIZE; i++) //keyboard entry
			{
				scanf("%s", &num[i] );
			}
			num[SIZE] = '\0';
			close(fd[0]); 
			write(fd[1], num, SIZE + 1); // write numbers to pipe
			printf("Sending numbers to child...\n");
			sleep(3); 
			exit(EXIT_SUCCESS);
		}

		else
		{ //child process
			wait(NULL); //wait while parent process finish execute
			printf("\n - - - CHILD PROCESS - - - - \n");
			close(fd[1]); 
			read(fd[0], buffer, SIZE + 1); //read numbers from pipe
			close(fd[0]); 
			printf("Number received from parents : %s", buffer); //display message on terminal
		}
	}
return EXIT_SUCCESS;
}

void sig_handler(int signum)
{
	printf("\nProgam interupted!\n");
}
