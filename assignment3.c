#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void childFunction(char *s) { //child function to calculate
	// variable declaration
	int num;
	int num2;
	int output;
	float floatingOutput; // float variable used to store calculation for division operation
	char outputBuffer[256];
	char operation; // char variable to store +, -, *, /
	write(STDOUT_FILENO, "I am a child working for my parent\n", strlen("I am a child working for my parent\n"));
	if(sscanf(s, "%d %c %d", &num, &operation, &num2) != 3){
		exit(50); // exit 50
	}
	if(num2 == 0 && operation == '/') { // if user tries dividing by 0 exit(100)
		exit(100); // exit 100
	}

	if(operation == '+') {
		output = num + num2;
		sprintf(outputBuffer, "%d %c %d = %d\n", num, operation, num2, output);
		write(STDOUT_FILENO, outputBuffer, strlen(outputBuffer));
		exit(0);
	}
	else if(operation == '-') {
		output = num - num2;
		sprintf(outputBuffer, "%d %c %d = %d\n", num, operation, num2, output);
		write(STDOUT_FILENO, outputBuffer, strlen(outputBuffer));
		exit(0);
	}
	else if(operation == '*') {
		output = num * num2;
		sprintf(outputBuffer, "%d %c %d = %d\n", num, operation, num2, output);
		write(STDOUT_FILENO, outputBuffer, strlen(outputBuffer));
		exit(0);
	}
	else if(operation == '/'){
		floatingOutput = (float)num / (float)num2;
		sprintf(outputBuffer, "%d %c %d = %.2f\n", num, operation, num2, floatingOutput);
		write(STDOUT_FILENO, outputBuffer, strlen(outputBuffer));
		exit(0);
	}
	else if(operation != '+' && operation != '-' && operation != '*' && operation != '/'){
		exit(200); // exit 200
	}

}

int main() {
	// variable declaration
	int pid, status;
	char str[256];
	write(STDOUT_FILENO, "This program makes arithmetics\n", strlen("This program makes arithmetics\n"));
	while(1) { //infinite loop
		write(STDOUT_FILENO, "\nEnter an arithmetic statement, e.g., 34 + 132\n", strlen("\nEnter an arithmetic statement, e.g., 34 + 132\n"));
		char str[256] = ""; // reset the string
		read(STDOUT_FILENO, str, 256);
		pid = fork(); // fork
		if(pid == -1) {
			perror("fork not possible");
			exit(-1);
		}
		else if(pid == 0) { // child process
			childFunction(str); // call child function to do calculations
		}
		else if(pid > 0){ // parent process
			write(STDOUT_FILENO, "\nCreated a child to make your operation, waiting\n", strlen("\nCreated a child to make your operation, waiting\n"));
			wait(&status); // wait status
			// start of bit manipulation macros
			int error = WEXITSTATUS(status); // store WEXITSTATUS(status) in integer variable "error"
			switch(error) { // switch case for once the child terminates. 
				case 0: // case 0 break
					break;
				case 50: // case 50 wrong statement
					write(STDOUT_FILENO, "\nWrong statement.\n", strlen("\nWrong statement.\n"));
					break;
				case 100: // case 100 division by 0
					write(STDOUT_FILENO, "\nDivision by zero.\n", strlen("\nDivision by zero.\n"));
					break;
				case 200: // case 200 wrong operator
					write(STDOUT_FILENO, "\nWrong operator.\n", strlen("\nWrong operator.\n"));	
					break;				
			}

		}
	}

}
