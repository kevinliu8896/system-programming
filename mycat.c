#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd, fd2; // create 2 file descriptiors
	void filecopy(int, int); // call function filecopy
	if (argc == 1) {
		filecopy(STDIN_FILENO, STDOUT_FILENO);
	}
	else {
		while(--argc >0) {
			if ((fd = open(argv[1], O_RDONLY, 0777)) == -1) {
				printf("cat: can not open %s\n", *argv);
				return 1;
			}
			else {
				filecopy(fd, STDOUT_FILENO); // call function filecopy
				close(fd);
			}
		}
	}
	return 0;
}
void filecopy(int fd, int fd2) // replace parameters with 2 file descripters fd and fd2
{
	int c; 
	while (read(fd, &c, 1)) {
		write(fd2 , &c, 1); // writes out all the contens of the file
	}
}