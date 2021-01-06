#include <stdio.h> // using standard io
#include <stdlib.h>
int main(int argc, char *argv[]) {
    FILE *fp, *fp2; // create 2 file pointers 
    int position = 0;  // create position var and make it equal to 0
    char ch; // char ch
    if((fp = fopen(argv[1], "r")) && (fp2 = fopen(argv[2], "w"))) {
    	while(fread(&ch, sizeof(ch), 1, fp)>0){
        	position++;
    	}

    	int i = 0; // i = 0
    	while( i < position) { // while i < 0
			i++; // increment i by 1
       		fseek(fp, -i ,SEEK_END); // seek to the end and read backwards
       		ch = fgetc(fp); // get char from fp
        	fwrite(&ch, sizeof(ch), 1, fp2); // write it into fp2

    	}
    }  
    else {
    	perror("FILE PROBLEM");//perror
    	exit(-1); //exit status
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    fclose(fp); // close fp and fp2 file pointers
    fclose(fp2);
}
