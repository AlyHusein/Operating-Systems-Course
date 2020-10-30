#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

/*
Aly Husein
CS3305 Assignment 2
Due: October 14th (Self-Reported Absence)
*/

int main(int argc, char **argv)
{

	pid_t pid, pid1, pid2;
	int port[2];
	char x[100];
	char y[100];
	char z[100];

	if (argc != 4) //check for valid number of arguments
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	if (pipe(port) < 0) { //check for pipe failure
		perror("pipe encountered an error");
		exit(0);
	}
	printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());

	pid = fork(); //Create child process

	if (pid < 0) { //Check for fork failure
		printf("fork was unable to complete");
		exit(1);
	}

	if (pid > 0) { //Parent process
		printf("parent (PID %d) created a child (PID %d)\n", getpid(), pid);
		//assign argument to x
		strcpy(x, argv[1]);
		printf("parent (PID %d) receives X = \"%s\" from the user\n", getpid(), x);
		wait(NULL);
		//receive y' from child process
		read(port[0], &y, 12);
		printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", getpid(), y);
		//concatenate x and y'
		strcat(x, y);
		printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", getpid(), x);
	}

	else { //child process
		//Assign arguments to variables
		strcpy(y, argv[2]);
		strcpy(z, argv[3]);
		printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", getpid(), y, z);
		//concatenate y & z
		strcat(y, z);
		printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", getpid(), y);
		printf("child (PID %d) writes Y' into the pipe\n", getpid());
		//Write concatenated y to port
		write(port[1], y, strlen(y));
	}
	return 0;
}
