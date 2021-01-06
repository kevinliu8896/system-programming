#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){  
	FILE *fd;
	
	int ch;

	int fileSize=-1;

	fd = fopen(argv[1], "r+"); // this was the problem in the code there the original code
				   //never checks if there is an invalid file when running program
	//the next few lines will check if file is valid or if it should print out an error 
	if (fd == NULL) { // check if file is valid if not valid prints out an error. This is the problem.
		perror("FILE PROBLEM"); // print error
		exit(-1); // exit status
	}  // end if statement

	do{
		ch=getc(fd);  //printf("ch=%c ", ch);
		fileSize++;
		printf("fileSize=%d\n", fileSize);
	} while( ch != EOF);
	
	printf("Size of %s is %d\n", argv[1], fileSize);
}
