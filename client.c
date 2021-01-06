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

int main(int argc, char* argv[]) {
	int csd;
	char command[256];
	socklen_t len;

	struct sockaddr_in servAdd;

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = inet_addr(argv[1]);
	servAdd.sin_port = 49155;

	csd = socket(AF_INET, SOCK_STREAM, 0);
	if((connect(csd, (struct sockaddr*) &servAdd, sizeof(servAdd))) == -1) {
		perror("connect");
		exit(1);
	}

	printf("Please help me execute this command:\n");
	scanf("%s", command); // scanf for command as input
	send(csd, command, sizeof(command), 0); // send the command requested to server


	printf("The output of the command is:\n");
	char execute[10000]; // create char array to store all contents of what is executed
	recv(csd, execute, 10000, 0); // recieve from server what has been executed
	printf("%s\n", execute); // print out whta has been executed.
}