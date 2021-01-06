#include "smallsh.h"
#include <string.h>
#include <stdlib.h>

int gettok(char **outptr);
int runcommand(char **cline, int where);


void procline(void) 
{
	char *arg[MAXARG + 1]; 
	int toktype; 
	int narg; 
	int type; 

	narg = 0;

	for (;;) 
	{
	   switch (toktype = gettok(&arg[narg])) {
		case ARG:
			if (narg < MAXARG) {
				printf("arg[narg=%d] = %s\n", narg, arg[narg]);
				narg++;
			}
			break;
		case EOL:
		case SEMICOLON:
		case AMPERSAND:
			if (toktype == AMPERSAND)
				type = BACKGROUND;
			else
				type = FOREGROUND;
			if (narg != 0)
			{
				printf("arg[narg=%d] = %s\n", narg, arg[narg]);
				arg[narg] = NULL;
				runcommand(arg, type);
			}
			if (toktype == EOL)
				return;
			narg = 0;
			break;
	  }
	  //added for assignment 3
//          if (!strcmp(arg[narg-1],"exit"))
//		exit(5);
	}
}
