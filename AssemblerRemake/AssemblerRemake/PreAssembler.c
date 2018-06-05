#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"
#define True 1
#define False 0
#define MAX_RECORD_SIZE 200

#define NAMEEXTRA 8; //The amount of bytes being added to the name. New.txt = 7 + 1 for \0
/*
This code is reponsible for the handling of the input file. It can take a file as an argument in the .exe file and
will take the text within the input file one line at a time. Each line is to be considered a record and each record is
to be output to another file which handles the parsing and emulating of the record.

I have decided to leave comments in for the user to use. When this code is ready to be
used in a way that the file goes straight to the X-Makina, the comments can be ignored, but for now
it will be useful to the user to see the comments, as well as where the preassembler located errors.


By Callum Cottrell B00712510

File reading based on Dr Hughes in class notes
*/

FILE *newfile; // the new file that will be created. 

extern struct emulation table[]; // The table from the table file linked above. This holds the raw data to be searched.

								 /* This function will create a new file based on the old file name and the extension given.
The old file name is the name of the file that was input by the user. If the input is _______, the new file name
 is ________New.txt. */
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
	/* Files Related Variables*/
	FILE *infile; // the inut asm file pointer
	FILE *outfile; // the output file
	char *xmename; // pointer to the xme filename
	char *lisname; // pointer to the lis filename
	char *hdrname; //pointer to the filename without path
	char *xmeext; //location of "." before extension in argv[1]
	int xmelen; // length of the XME filename

	/* Algorithm Related Variables*/
	char record[MAX_RECORD_SIZE]; // One line of the input file.
	char *finalRecord[MAX_RECORD_SIZE]; // The version of the record to be written to the file
	char *parser; // The parser is the character pointer that iterates through the record
	char *commentTokens[MAX_RECORD_SIZE]; // The comments are stored in this array
	char delimiterComment[] = ";"; // The delimiter is for strtok to tokenize by
	int numOfTokens = 0; // The number of tokens.
	int i = 0; // for iterating through regular arrays
	int k = 0; // for iterating through the finalRecord Array
	int errorFlag; // Set to true if the preassembler finds an error

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
	if (newFileFromOld(&newfile, argv[1], &lisname, (char*) "New.txt", (char*) "w") != 0) {
		printf("can't open the new .asm file \n");
		getchar();
		return 1;
	}
	// Display the filename for debugging purposes.
	printf("filename: %s\n", argv[1]);

	//Read through the entire file line by line. 
	while (fgets(record, MAX_RECORD_SIZE, infile) != NULL) {
		//check if the first character is a the semicolon. if it is, the rest of the record is ignored
		switch (record[0]) {
		case ';':
			while (record[i] != NULL) {
				fprintf_s(newfile, "%c", record[i]);
				i++;
			}
			i = 0;
			break;
		default:

			//Parse the record by tokenizing via strtok with ; as a delimiter
			parser = strtok(record, delimiterComment);

			//Everything before the first ";" is non-comment
			char *tokens = parser;

			//Find the rest of the comments. must complete the line of the file incase many ; are found
			while (parser != NULL) {
				parser = strtok(NULL, delimiterComment);
				commentTokens[i++] = parser;
			}

			//Give the tokens found to the Emulation algorithm
			char **emulated_Tokens = EmulateTokens(tokens, &numOfTokens, &errorFlag);

			//Initialize k, the counter for the final Record Array
			k = 0;

			// Print the Emulated Tokens
			for (i = 0; i < numOfTokens; i++) {
				//Iterating through the pointer to a pointer of chars will iterate through the pointer by the correct amount.
				finalRecord[k++] = *emulated_Tokens++;
				//printf("the final record is now: %s \n", finalRecord[k]);
				finalRecord[k++] = " ";
			}
			i = 0;
			//Append the comments to the Emulated Tokens
			while (commentTokens[i] != NULL) {
				// printf(";%s ", commentTokens[i++]);
				finalRecord[k++] = ";";
				finalRecord[k++] = commentTokens[i++];
			}
			i = 0;

			/* If the error flag that was returned from the Emulation algorithm was set true, insert a comment
			The comment will always have a ; in case there wasn't a comment already. This is an ugly solution
			if there are already comments, since there would be multiple semicolons on one line. This may be
			ok since the error from the preassembler should stand out to the user anyway; hence the capitals letters.
			*/
			if (errorFlag == True) {
				finalRecord[k++] = ";ERROR_FOUND_BY_PREASSEMBLER\n";
			}

			// Final record assembled. Write to the file
			for (i = 0; i < k; i++) {
				fprintf_s(newfile, "%s", finalRecord[i]);
			}
			fprintf(newfile, "\n");
			i = 0;
		}

	}
	getchar();
	fclose(newfile);
	fclose(infile);
}