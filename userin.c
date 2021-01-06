#include "smallsh.h"

static char inpbuf[MAXBUF], *ptr = inpbuf;

int inarg(char c);

int userin(char *p)
{
	int c, count;
	ptr = inpbuf;
	char prevChar = ' '; // create a char variable that stores previous char value setting it to a space for now(' ')
	
	printf("%s", p);
	count = 0;
	while (1)
	{
		if ((c = getchar()) == EOF) {
			return(EOF);
		}

		if(inarg(c) == 0 && inarg(prevChar) == 1) { // create if statement for userin function to check if an argument ends and to check back with inarg functions return value.
			inpbuf[count++] = '\0'; // if the argument ends we add the \0 while incrementing count
		}

		if (count < MAXBUF &&c != ' ' && c != '\t')// if statement to ignore white spaces such as a space(' ') and tabs('\t')
			inpbuf[count++] = c;

		if (c == '\n' && count < MAXBUF)
		{
			inpbuf[count] = '\0';
			return count;
		}

		if (c == '\n')
		{
			printf("smallsh: input line too long\n");
			count = 0;
			printf("%s ", p);
		}
		prevChar = c; // set the previous character to the character stored in variable c
	}
}

int gettok(char **outptr)
{
	int type;
	
	*outptr = ptr;

	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;
	case '&':
		type = AMPERSAND;
		break;
	case ';':
		type = SEMICOLON;
		break;
	default:
		type = ARG;
		while(*ptr != '\0') { // while the *ptr is not the delimiter (\0) the value of ptr will be incremented
			ptr++;
		}
		ptr++; // increment ptr again by one

	}
	return type;
}

//****************************************************************************************
static char special[] = { ' ', '\t', '&', ';', '\n', '\0' };
int inarg(char c)
{
	char *wrk;
	for (wrk = special; *wrk; wrk++)
	{
		if (c == *wrk)
			return (0);
	}
	return (1);
}


