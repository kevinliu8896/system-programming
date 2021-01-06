#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

void parent(int *);
void child(int *);

int main(int argc, char *argv[]) {
	int fd[2]; // create 2 file descriptors

	if(pipe(fd) == -1) { // if pipe is -1 call exit
		exit(1); // exit
	}

	int pid = fork(); // fork to create a child process
	srand(time(NULL)); // randomize numbers
	if(pid == 0) { // child 1
		child(fd); // call child function
	}

	else { // parent
		sleep(1); // sleep for 1 second
		srand(time(NULL)); // randomize numbers
		int pid2 = fork(); // fork to create child 2

		if(pid2 == 0) { // child 2
			child(fd);
		}

		else { // parent
			sleep(1); // sleep for 1 seconds
			parent(fd); // call parent function
		}
	}

}

void parent(int *fd) { // parent function
	int n; // create int varaible
	for(int i = 0; i < 10; i++){ //for loop to print out 10 numbers from child function being called twice
		read(fd[0], &n, sizeof(int)); // read
		printf("%d\n", n);  // printing out the numbers

	}

}

void child(int *fd) { // child function
	int n = 0; // create integer variable and initialize it to value of 0
	close(fd[0]); // close fd[0]
	for(int i = 0; i < 5; i++) { // loop through to print out 5 numbers
		n = rand() % 100; // generate 0-99
		write(fd[1], &n, sizeof(int)); // write
	}
	
}