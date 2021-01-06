#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	char arr[44] = ("101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n"); //create
										// char array 
										//storing up to 100 
										// elements
	int fd = open("list1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0755); // file descripter creates list1.txt file and stores array elements inside file
	write(fd, arr, 44);
	close(fd); // close file descriptior
}