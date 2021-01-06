/*
QUESTION 2

105191861

Kevin Liu
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int sd, cd, status;
	int pid;
	char command[256];
	socklen_t len;

	struct sockaddr_in servAdd, cliAdd;

	if(sd = socket(AF_INET, SOCK_STREAM, 0)) {
		printf("Socket connected\n");
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = INADDR_ANY;
	servAdd.sin_port = 49155;

	int yes=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	bind(sd, (struct sockaddr *)&servAdd, sizeof(servAdd));


	listen(sd, 5);

	len = sizeof(cliAdd);

	if((cd = accept(sd, NULL,NULL)) > 0) {
		printf("Client connected successfully\n");
	}

	recv(cd, command, sizeof(command), 0); // receieve command to execute
	printf("The command is: %s", command);

	if((pid == fork()) < 0) { // fork a process
		perror("fork");
	}
	else if(pid == 0) { // child
		dup2(cd, STDOUT_FILENO); //stdout points to client descriptor
		execlp(command, command, NULL); // executes command stored in char command
		exit(11);
	}
	else {
		waitpid(pid, &status, 0); // waitpid for exit status
			printf("Child process terminated, the exit status is %d\n", WEXITSTATUS(status));
	}

	printf("Server terminated\n");


}