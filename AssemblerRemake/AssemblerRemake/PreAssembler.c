#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"

/*
This code is reponsible for the handling of the input file. It can take a file as an argument in the .exe file and 
will take the text within the input file one line at a time. Each line is to be considered a record and each record is
to be output to another file which handles the parsing and emulating of the record. 
- perhaps here I will eliminate the comments since there is no need to send these to the emulator

By Callum Cottrell
File reading based on Dr Hughes in class notes
*/

/* These may be better off as ints, since defining defaults to int*/
#define Neither (char)0x00
#define Right (char)0x01
#define Left (char)0x10
#define Both (char)0x11

#define MAX_RECORD_SIZE 200

#define NAMEEXTRA 5;


FILE *xmefile; // the X Makina executable file
FILE *lisfile; // .lis file for 1st and 2nd pass errors
unsigned short lc; // location counter
extern struct emulation table[]; // The table from the table file linked above. This holds the raw data to be searched.

/* This function will create a new file based on the*/
int newFileFromOld(FILE **newfptr, char *oldFileName, char **newName, char *extension, char *mode) {

	/* Create a new file from an old fie(name) by chaning the extension
	-Alllocate space for new name plus extension and copu old to new
	- Overwrite old extension (if it exists)
	- Aattempt to open in specified mode
	- Return '0' if successs, !0 otherwise
	*/

	int newlen;
	char *extaddr;
	int rc;

	// length of input file plus extra space in case "." is missing

	newlen = strlen(oldFileName) + NAMEEXTRA;
	*newName = (char*)malloc(newlen);
	strcpy_s(*newName, newlen, extension);

	if ((extaddr = strstr(*newName, ".")) != NULL) { // Found "." before the end of the extension
		*extaddr = 48; // ASCII for 0, NUL not working for me right now

		strcat_s(*newName, newlen, extension); // Concatenate the extension to the new name

		rc = fopen_s(newfptr, *newName, mode);

		return rc;
	}
}
	void common_diagnostics(char *msg) {
		fprintf_s(lisfile, msg);
		printf(msg);
	}
	

int main(int argc, char *argv[]) {
	/* Variable Declaration */
	FILE *infile; // the inut asm file pointer
	char *xmename; // pointer to the xme filename
	char *lisname; // pointer to the lis filename
	char *hdrname; //pointer to the filename without path
	char *xmeext; //location of "." before extension in argv[1]
	int xmelen; // length of the XME filename
	char record[200]; // One line of the input file.
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

	if (newFileFromOld(&lisfile, argv[1], &lisname, (char*) ".lis", (char*) "w") != 0) {
		printf("can't open the .lis file \n");
		getchar();
		return 1;
	}
	// Display the filename for debugging purposes.
	printf("filename: %s\n", argv[1]);

	char *noComments;

	while (fgets(record, 200, infile) != NULL) {
		noComments = strtok(record, ";");
		doTheThing(noComments);

		//If the end of the file is reached
		if (feof(infile)) {
			printf(" hit end of file ");
			break;
		}
	}
	getchar();

	fclose(infile);
}