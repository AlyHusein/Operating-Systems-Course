#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	/*
	Aly Husein 250839669
	CS3305 A1
	*/

	pid_t pid, pid1, pid2;
	char buffer[50]="";

	if (argc != 2)
	{
		printf("Invalid arguments\n");
		exit(0);
	}
	pid = fork(); //Parent process creates child 1

	if (pid < 0) { //for potential fork failure
		printf("fork was unable to complete");
		exit(1);
	}

	if (pid > 0){ //Parent
		printf("parent process (PID %d) created child_1 (PID %d) \n", getpid(), pid);
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getpid(), pid);
		wait(NULL); //Wait till child 1 finishes process
		pid1 = fork(); //Parent creates child 2


		if (pid1 > 0){
			wait(NULL);
		}
		if (pid1 == 0) { //child 2
			pid2 = getpid();
			printf("parent (PID %d) created child_2 (PID %d)\n", getppid(), getpid());
			printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", getpid());
			sprintf(buffer, "%d", pid2);//put pid for child_2 into buffer
			execl(argv[1], "external_program.out", buffer, NULL);//call external program
		}

	}

	if (pid == 0) { //child 1

		pid1 = getpid();
		pid2 = fork(); //child1.1
		if (pid2 == 0){
			printf("child_1 (PID %d) created child_1.1 (PID %d)\n", pid1, getpid());
			printf("child_1 (PID %d) is now complete\n", pid1);
		}
	}
	return 0;
}
