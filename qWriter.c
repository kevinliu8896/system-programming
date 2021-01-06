Script started on 2020-10-09 19:46:25-04:00 [TERM="xterm" TTY="/dev/pts/13" COLUMNS="100" LINES="35"]
]0;liu61@charlie: ~/fall2020/sysprog[01;32mliu61@charlie[00m:[01;34m~/fall2020/sysprog[00m$ cat writer.c
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
}]0;liu61@charlie: ~/fall2020/sysprog[01;32mliu61@charlie[00m:[01;34m~/fall2020/sysprog[00m$ gcc writer.c -o writer
]0;liu61@charlie: ~/fall2020/sysprog[01;32mliu61@charlie[00m:[01;34m~/fall2020/sysprog[00m$ ./writer
]0;liu61@charlie: ~/fall2020/sysprog[01;32mliu61@charlie[00m:[01;34m~/fall2020/sysprog[00m$ cat list1.txt
101   GM	Buick	2010
102   Ford	Lincoln	2005
]0;liu61@charlie: ~/fall2020/sysprog[01;32mliu61@charlie[00m:[01;34m~/fall2020/sysprog[00m$ exit
exit

Script done on 2020-10-09 19:46:44-04:00 [COMMAND_EXIT_CODE="0"]
