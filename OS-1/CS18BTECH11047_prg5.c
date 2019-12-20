#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int 
main() 
{
	pid_t child1;
	pid_t child2;

    	int parentVar = 0;	
    	int childVar1 = 0;
    	int childVar2 = 0;

    	int fd1[2]; //creating arrays to store the ends of the pipe
    	int fd2[2];
    	pipe(fd1); //creating pipes for inter process communication
    	pipe(fd2);

    	if ((child1 = fork()) > 0) { //Parent code, creating child1
		if((child2 = fork()) > 0) { //Parent Code, creating child2
			int buffer;
			printf("Parent : Waiting for child processes to end : %d \n", getpid());
			while(wait(NULL) != -1);
			close(fd1[1]); //closing both the writing ends as they are of no use.
			close(fd2[1]);
			read(fd1[0], &buffer, sizeof(buffer)); //reading from the first child
			close(fd1[0]); //closing reading end after reading
			parentVar = buffer;
			read(fd2[0], &buffer, sizeof(buffer)); //reading from the second child
			close(fd2[0]); //closing reading end after reading
			parentVar *= buffer;
			printf("Parent : Product of the two child variables is : %d : %d \n", parentVar, getpid());
		} else if(child2 == 0) { //Child2 code
			printf("Child2 : Calculating sum of odd numbers less than 100 : %d \n", getpid());
			for(int i = 1;i < 100;i += 2) //calculating the sum of odd numbers less than 100
				childVar2 += i;

			printf("Child2 : Sum calculated = %d : %d \n", childVar2, getpid());
			close(fd2[0]); //closing reading end as it is of no use
			write(fd2[1], &childVar2, sizeof(childVar2)); //writing to the pipe 
			close(fd2[1]); //closing writing end after writing
		} else {
			perror("fork");
		}
	} else if (child1 == 0) { //Child1 code
		printf("Child1 : Calculating sum of even numbers less than 100 : %d \n", getpid());
		childVar1 = 0;
		for(int i = 2;i < 100;i += 2) //calculating the sum of even numbers less than 100
			childVar1 += i;
	
		printf("Child1 : Sum calculated = %d : %d \n", childVar1, getpid());
		close(fd1[0]); //closing reading end as it is of no use
		write(fd1[1], &childVar1, sizeof(childVar1)); //writing to the pipe 
		close(fd1[1]); //closing writing end after writing
	} else {
		perror("fork");
	}
	return 0;
}