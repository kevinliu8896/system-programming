#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int fd[2];
	int fd2 = open("result.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777); // fd to create result.txt
									// and w/r to file
	int pid; // create pid
	int status; // status for wait
	if(pipe(fd) == -1) {
		exit(1); // exit
	}

	pid = fork(); // fork a child process
	if(pid == 0) { // child
		close(fd[0]); // close fd[0]
		dup2(fd[1], STDOUT_FILENO); // STDOUT_FILENO points to fd[1]
		execlp(argv[1], argv[1], NULL);
	}
	else { // parent
		wait(&status); // wait
		close(fd[1]); // close fd[1]
		int size; // create size variable to keep track of bytes
		char buffer; // buffer tom read byte by byte
		
		while(read(fd[0], &buffer, 1) > 0) { // while loop
			write(fd2, &buffer, 1); // write to result.txt
			size++; // incrememnt size
		}
		//display info
		printf("The result of %s is written into result.txt with total %d bytes\n", argv[1], size);
	}
}
