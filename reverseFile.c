#include <stdio.h> // use standard io
#include <stdlib.h>

int findNewLinePos(FILE *file, int newLinePos[]){ // this function finds new line positions and stores them in an array
                                                  // as well as returning num of lines
    int count = 1, currPos = 0;
    int chr;
    newLinePos[0] = -1; // stores the starting position in the array
    while ((chr = getc(file)) != EOF) {
        if (chr == '\n') { // if it is a new line character
            newLinePos[count++] = currPos; // add the current position to the array
        }
        currPos++;
    }
    return count - 1;
}

int main(int argc, char *argv[]) {
	FILE *fp, *fp2; // create 2 file pointers
	char line[256]; // create line that reads up to 256 bytes per line
	int arr[100]; // create array that stroes 100 elements
	int lines = 0; // set lines to 0
	int c; // counter variable

	if((fp = fopen(argv[1],"r")) && (fp2 = fopen(argv[2], "w"))) { // read fp and fp2 in read
									// and write mode
		lines = findNewLinePos(fp,arr); //set line to function findNewLinePos
		for (int i = lines; i >= 0; i--) {
			fseek(fp, arr[i] + 1, SEEK_SET); //seek to beginnning with arr[i] + 1
			while((c = getc(fp)) != EOF) { // while getc(fp) is not end of file
				if (c == '\n'){
					break; // break if \n is stored in c
				}
			fputc(c,fp2); // fputc stores chars into fp2 from c
			}
		fputc('\n', fp2); // fputc puts newline in fp2
		}
	}
	    else {
    	perror("FILE PROBLEM"); // print file error
    	exit(-1); // exit status
    }   
		fclose(fp); // close fp and fp2 filepointers
		fclose(fp2);
}


