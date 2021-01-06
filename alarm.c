#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig) { // signal handler
	printf("Ding!\n");
}

int main(int argc, char *argv[]) {
	int seconds; // create variable for seconds
	sscanf(argv[1], "%d", &seconds); // scan for argv[1] for amount of seconds to sleep
	int pid = fork(); // fork a process
	if(pid == 0) { // child
		//display messages
		printf("Alarm application is starting\n");
		printf("Waiting for alarm to go off\n");
		sleep(seconds); // sleep for amount of seconds from argument
		printf("<%d second pause>\n", seconds); // display amount of seconds slept
		kill(getppid(), SIGALRM); // send signal to parent process
	}
	else { // parent
		signal(SIGALRM, handler); // using signal handler to print ding
		pause(); // suspends process
		printf("Done\n");

	}
}
