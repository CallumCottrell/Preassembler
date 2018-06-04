#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"

extern struct emulation table[];

#define True 1
#define False 0
#define Neither 0x00
#define Right 0x01
#define Left 0x10
#define Both 0x11
#define MAX_RECORD_SIZE 100
#define MAX_EMULATE_SIZE 15

char** EmulateTokens(char *noComments, int *numOfTokens) {
	char bigBuff[MAX_RECORD_SIZE]; // A char array to hold the Non-Comment tokens from the Record
	char smallBuff[MAX_EMULATE_SIZE];
	int sizeOfRecord = sprintf(bigBuff, "%s" , noComments); // Makes the character pointer into a character array, also returns size of array
	int set = 0;
	char *toker = strtok(bigBuff, ", "); // start reading the buffer and parse by spaces and ,
	char *tokens[MAX_RECORD_SIZE];
	int i = 0;

	//Read through the input Record and store the tokens in a character pointer array
	while (toker != NULL) {
		tokens[i++] = toker;
		toker = strtok(NULL, ", ");
	}
	//Store the number of tokens. Number is one extra. Maybe change above lines to save
	// Having to set tokens[i] as null since toker is null at the end anyway
	numOfTokens = i ;
	tokens[i] = NULL;

	//Check each token
	for (i = 0; i < numOfTokens; i++) {
		//Check every instruction in the table
		for (int k = 0; k < sizeOfTable(); k++) {
			//If there is a match....
			if (_stricmp(tokens[i], table[k].instruction) == 0) { 
				//Check how the handle the emulation. Dependent on the amount of arguments.
				switch (table[k].position) {
				case Neither: 
					tokens[i] = table[k].emulation;
					break;
				case Right:
					if ((tokens[i + 2] != NULL) | (tokens[i + 1] == NULL)) {
						printf("Error found");
						set = True;
					}
					tokens[i++] = table[k].emulation;
					break;
				case Left:
					if ((tokens[i + 2] != NULL) | (tokens[i + 1] == NULL)) {
						printf("Error found");
						set = True;
					}
					//Assign the current string in the token array to equal the emulation table. Increment i
					tokens[i++] = table[k].emulation;
					//Assign the next token to be the right side constant from the table.
					tokens[i + 1] = table[k].rightSide;
					break;
				case Both:
					if ((tokens[i + 2] != NULL )|(tokens[i+1] == NULL)) {
						printf("Error found");
						set = True;
					}
					// May not be needed. Just trying to minimize number of tokens.
					sprintf(smallBuff, "%s, %s", tokens[i + 1], tokens[i + 1]);
					tokens[i++] = table[k].emulation; // skipping over to the next 
					tokens[i] = smallBuff;
					break;

				default:
					break;
				}
			}
		}
	}

	return tokens;

}