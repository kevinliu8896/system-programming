#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int size;
  if ( argc < 2 ){
	 return 0; // return statement
	}
  int fd = open(argv[1],O_RDONLY); // open file descriptor and set it so that it refers to a file
				   // and the file descriptor refering to the opening of the file

	if (fd < 0) {
		perror("Error opening file.");
		exit(1);
	}
  size = lseek(fd, 0, SEEK_END);   // variable size of int type uses lseek to change location of 
				   // r/w pointer from the file descriptor.
  printf("%d bytes.\n", size); // displays size of file
  close(fd); // closes file descrriptor
  return 0; // return statement
} // end of main function
