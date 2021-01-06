/*
FINAL EXAM

QUESTION 1

Kevin Liu
105191861

*/
#include<stdio.h>
#include <unistd.h>
#include<signal.h>
#include<time.h>
#include <sys/types.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


void action(int dummy) { // create signal handler called action with dummy variable
}
char *fifo = "fifo"; // create some fifos
char *fifo2 = "fifo2";

void player1(char *s); // function declaration for player 1 for signals
void player2(char *s, int *fd1, int *fd2); // function declaration for player2 for pipes
void player3(char *s, int fifo, int fifo2);

int main(int argc, char *argv[]){ 
	
	int pid, pid2, pid3; // creating pid's for 3 players

	int fd1[2], fd2[2], fd3[2], fd4[2]; // pipes for player 2

	int fifofd, fifo2fd; // create fifo file descriptors

	char *fifo = "fifo";
	char *fifo2 = "fifo2";


	char turn='T';

	printf("This is a 3-player game with a referee\n");  

	if((pid = fork()) == 0) { // child 1, first player use signal
		player1("TOTO"); // call player 12 function
	}

	if((pid2 = fork()) == 0) { // child 2, 2nd player use pipe
		player2("TITI", fd3, fd4); // call playuer 2 function
	}
	close(fd3[0]); // closing fd3 for reading
	close(fd4[1]); // closing for writing for fd4

	unlink(fifo); // deletes fifo if it existss
	unlink(fifo2); // delete fifo2 if it exists

	// ----------------------------CREATING FIFO's---------------------------------- 

	if(mkfifo(fifo, 0777) == -1) { // 0777 octal code to allow all permissions for fifo
		perror("fifo 1");
		exit(1);//exit if fifo creation fails
	}

	if(mkfifo(fifo2, 0777)) {// 0777 octal code to allow all permissions for fifo2
		perror("fifo 2");
		exit(2); //exit if fifo2 creation fails
	}

	fifofd = open(fifo, O_RDWR, 0777); // opening up both fifo and fifo2 for read and write
	fifo2fd = open(fifo2, O_RDWR, 0777);

	if((pid3 = fork()) == 0) { // child 3, 3rd player use fifo
		player3("THTH", fifofd, fifo2fd); // call function for player 3 using fifo
	}

	signal(SIGUSR1, action); // establish signal

	//-------------------------------DISPLAY PLAYER INFORMATION--------------------------------
	while(1){
		printf("\nReferee: TOTO plays\n\n");  
		kill(pid, SIGUSR1); // sending signal to child
		pause();

		printf("\nReferee: TITI plays\n\n");  
		write(fd3[1], &turn, 1); // writing to pipe fd3[1]
		read(fd4[0],  &turn, 1);  // reading in [0] for fd4 

		printf("\nReferee: THTH plays\n\n");  
		write(fifofd, &turn, 1); // write to fifofd
		read(fifo2fd,  &turn, 1);  // reading to fifofd
	}
}

void player1(char *s){  // this is the player 2 function done with signals

	int points=0;
	int dice;
	long int ss=0;  
	
	char turn;   
	
	signal(SIGUSR1, action); // establish signal for player 1
	while(1){
		pause(); // suspends proces until signal is recieved
		printf("%s: playing my dice\n", s);
		dice =(int) time(&ss)%10 + 1;
		
		printf("%s: got %d points\n", s); 
		points = points + dice;

		printf("%s: Total so far %d\n", s, points);

		if(points >= 40) {
			printf("%s: Game over I won\n", s);
			kill(0, SIGTERM); // sending signal to child to terminate process if 40 points has been reacherd
		} 
		sleep(5); // sleep for 5 seconds
		kill(getppid(), SIGUSR1); // sending signal to parent process
	}
}

void player2(char *s, int *fd1, int *fd2){  // this is the player 2 function done with pipes

	int points=0;
	int dice;
	long int ss=0;  
	
	char turn;  
	close(fd1[1]);
	close(fd2[0]);  
	
	while(1){
		read(fd1[0], &turn, 1); // reading pipe fdq[0]
	

		printf("%s: playing my dice\n", s);  
		dice =(int) time(&ss)%10 + 1;  
		printf("%s: got %d points\n", s, dice); 
		points+=dice;
		printf("%s: Total so far %d\n\n", s, points);  

		if(points >= 40){
			printf("%s: game over I won\n", s); 
			kill(0, SIGTERM);// send signal to terminate game if points is over 40
		}
		sleep(5);// sleep for 5 seconds
		write(fd2[1], &turn, 1); // write to fd2[1]

	}
	
}

void player3(char *s, int fifo, int fifo2){  // this is the player 3 function done with fifo 

	int points=0;
	int dice;
	long int ss=0;  
	
	char turn;   
	
	while(1){
		read(fifo, &turn, 1);   // reading fifo

		printf("%s: playing my dice\n", s);  
		dice =(int) time(&ss)%10 + 1;  
		printf("%s: got %d points\n", s, dice); 
		points+=dice;
		printf("%s: Total so far %d\n\n", s, points);  

		if(points >= 40){
			printf("%s: game over I won\n", s); 
			kill(0, SIGTERM);// send signal to terminate game if points is over 40
		}
		sleep(5);  // sleep for 5 seconds
		write(fifo2, &turn, 1);  //write to fifo2

	}
	
}

