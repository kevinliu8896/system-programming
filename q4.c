#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd; // create file descriptor
	int buffer[1]; // create buffer
	int buffer2[1000]; // create second buffer

	fd = open(argv[1], O_RDWR | O_APPEND, 0777); // allow file descriptor to read or write file and append
	if (fd < 0) { // checks if it can open an exiting file 
		perror("Error opening file.");
		exit(1);
	}
	while(read(fd, buffer,1) >0) {
		printf("%c", buffer[0]); //display contents of file
	}

	printf("What information would you like to append? \n"); // ask user what they would like to append
	int size = read(STDIN_FILENO, buffer2, 1000);
	write(fd, buffer2 ,size);

	lseek(fd,0,SEEK_SET);
	printf("\nYour new file is: \n\n");
	while(read(fd, buffer, 1) > 0) {
		printf("%c", buffer[0]); // display file contents
	}
	close(fd);
}