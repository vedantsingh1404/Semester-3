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

        if((child1 = fork()) > 0) { //creating the first child process
                if((child2 = fork()) > 0) { //creating the second child process
                        printf("%s : %d \n", "Parent : Waiting for child processes to end", getpid());
                        while(wait(NULL) != -1); //waiting for all the child processes to end
                        printf("%s : %d \n", "Parent : All child processes ended", getpid());
                } else if(child2 == 0){
                        printf("%s : %d \n", "Child 2 : Sleeping for 10 seconds...", getpid());
                        sleep(10); //sleeping for 10 seconds
                        printf("%s : %d \n", "Child 2 : Killing Child 1", getpid());
                        kill(child1, 1); //killing child1
                        printf("%s : %d \n", "Child 2 : Sleeping for 10 seconds...", getpid());
                        sleep(10); //sleeping for 10 seconds
                        printf("%s : %d \n", "Child 2 : Terminating", getpid());
                        exit(1);
                } else {
                        perror("fork");
                }
        } else if(child1 == 0) {
                int i = 1;
                while(i > 0) {
                        printf("%s : %s : %d \n", "Child 1", "<Some Message>", getpid()); //printing any message
                        sleep(1); //sleeping so that the message gets printed every second
                }
        } else {
                perror("fork");
        }
        return 0;
}