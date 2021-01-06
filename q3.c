#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd; // create file descriptor
	int buffer[1]; // create buffer 
	int count = 1; // create counter variable for line count

	fd = open(argv[1], O_RDONLY, 777); // open file 
			if (fd < 0) { // checks if it can open an exiting file 
		perror("Error opening file.");
		exit(1);
	}

	while(read(fd,buffer,1) > 0) {
		if((char) buffer[0] == '\n') { // if char buffer[0] reaches '\n' in file then increasecount
			count++;
		
		}
	}
	printf("There are %d lines in the file.\n", count);
	close(fd);
}