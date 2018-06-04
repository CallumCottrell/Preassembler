#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"
#define Neither (char)0x00
#define Right (char)0x01
#define Left (char)0x10
#define Both (char)0x11

#define MAX_RECORD_SIZE 200

#define NAMEEXTRA 8;
/*
This code is reponsible for the handling of the input file. It can take a file as an argument in the .exe file and 
will take the text within the input file one line at a time. Each line is to be considered a record and each record is
to be output to another file which handles the parsing and emulating of the record. 
- perhaps here I will eliminate the comments since there is no need to send these to the emulator

By Callum Cottrell
File reading based on Dr Hughes in class notes
*/


FILE *xmefile; // the X Makina executable file
FILE *lisfile; // .lis file for 1st and 2nd pass errors
unsigned short lc; // location counter
extern struct emulation table[]; // The table from the table file linked above. This holds the raw data to be searched.

/* This function will create a new file based on the*/
int newFileFromOld(FILE **newfptr, char *oldFileName, char **newName, char *extension, char *mode) {

	int newlen;
	char *extaddr;
	int rc;

	// length of input file plus extra space in case "." is missing

	newlen = strlen(oldFileName) + NAMEEXTRA;
	*newName = (char*)malloc(newlen);
	
	strcpy_s(*newName, newlen, oldFileName);
	strcat_s(*newName, newlen, extension);

	if ((extaddr = strstr(*newName, ".")) != NULL) { // Found "." before the end of the extension
		*extaddr = NULL; // ASCII for 0, NUL not found on Visual Studio for now
		strcat_s(*newName, newlen, extension); // Concatenate the extension to the new name
		rc = fopen_s(newfptr, *newName, mode);
		return rc;
	}
}


int main(int argc, char *argv[]) {
	/* Variable Declaration */
	FILE *infile; // the inut asm file pointer
	char *xmename; // pointer to the xme filename
	char *lisname; // pointer to the lis filename
	char *hdrname; //pointer to the filename without path
	char *xmeext; //location of "." before extension in argv[1]
	int xmelen; // length of the XME filename
	char record[MAX_RECORD_SIZE]; // One line of the input file.
	int *sizeOfRecord = 0;
	if (argc < 2) {
		printf("insufficient arguments\n");
		getchar();
		return 0;
	}

	/* Error handling with the files.*/
	if (fopen_s(&infile, argv[1], "r") != 0) {
		printf("Error opening %s \n ", argv[1]);
		getchar();
		return 1;
	}
	// This will take the old file name and make a new one, with new file ending in New.asm 
	if (newFileFromOld(&lisfile, argv[1], &lisname, (char*) "New.asm", (char*) "w") != 0) {
		printf("can't open the new .asm file \n");
		getchar();
		return 1;
	}
	// Display the filename for debugging purposes.
	printf("filename: %s\n", argv[1]);

	char *parser;
	char *comments;
	char **emulated_Tokens;
	char *delimiter = ";";
	
	//Read through the entire file line by line. 
	while (fgets(record, MAX_RECORD_SIZE, infile) != NULL) {

		parser = strtok(record, delimiter);
		printf("\ncomments %s", parser);

		emulated_Tokens = EmulateTokens(parser, *sizeOfRecord);

		parser = strtok(NULL, delimiter);

		printf("\ncomments %s", parser);
		//If the end of the file is reached
		if (feof(infile)) {
			break;
		}
		
		printf("size of record:", sizeOfRecord);
		for (int i = 0; i < sizeOfRecord; i++) {
			printf(" %s", emulated_Tokens[i]);
		}
	}
	getchar();

	fclose(infile);
}