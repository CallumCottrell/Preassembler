#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"

extern struct emulation table[];

/*
The purpose of this file is to hold the function Emulate Tokens. The function is responsible for returning
to the main file a char** that holds tokens that have been emulated. Via pass by reference, the number of tokens and
the boolean integer "set" are brought back to the main. The pointer to noComments is the part of the Record
that comes before the first ";" symbol. This means that no comments will get processed by this algorithm.

The main variable being altered is "tokens". This is an array of character pointers of the size 200. This was
the largest size allocated to tokenizing seen in use with the X-Makina on Dr Hughes website, and is certainly
large enough to accomodate even heavy use. Since a record consists of only a few words, most of which
are instructions (which only take 3-5 bytes) exceeding 256 would require abnormally large subroutine/label/ operand names.
There is a risk for large records when considering the fact that comments will be stored somewhere. This comment already is
itself very large, but it has been separated by lines and does not exceed 123 characters and 20 whitespaces.

There is a smaller buffer referred to as smallBuff that holds emulation sizes.

*/
#define True 1
#define False 0
#define Neither 0x00
#define Right 0x01
#define Left 0x10
#define Both 0x11
#define MAX_RECORD_SIZE 100
#define MAX_EMULATE_SIZE 15

char** EmulateTokens(char *noComments, int *numOfTokens, int *set) {
	char bigBuff[MAX_RECORD_SIZE]; // A char array to hold the Non-Comment tokens from the Record
	char smallBuff[MAX_EMULATE_SIZE]; //buffer required for each token in the array
	int sizeOfRecord = sprintf(bigBuff, "%s" , noComments); // Makes the character pointer into a character array, also returns size of array
	char *toker = strtok(bigBuff, ", \n\t"); // toker holds the values during the tokenize process
	char *tokens[MAX_RECORD_SIZE]; // The emulated Tokens to return
	int newTokens = 0;
	int i = 0; // For iterating

	// Initiliaze as false
	*set = False; 

	//Read through the input Record and store the tokens in a character pointer array
	while (toker != NULL) {
		tokens[i++] = toker;
		toker = strtok(NULL, ", \n\t");
	}
	//Store the number of tokens. Number is one extra. Maybe change above lines to save
	// Having to set tokens[i] as null since toker is null at the end anyway
	*numOfTokens = i ;
	tokens[i] = NULL;
	if (*numOfTokens > 4) {
		*set = True;
	}
	//Check each token
	for (i = 0; i < *numOfTokens; i++) {
		//Check every instruction in the table against current token
		for (int k = 0; k < sizeOfTable(); k++) {
			//If there is a match...
			if (_stricmp(tokens[i], table[k].instruction) == 0) { 
				//Check how the handle the emulation. Dependent on the amount of arguments.
				switch (table[k].position) {
				case Neither: 
					tokens[i] = table[k].emulation;
					break;
				case Right:
					printf("Tokens[i+2] = %s\n", tokens[i + 2]);
					if ((tokens[i + 2] != NULL) | (tokens[i + 1] == NULL)) {
						printf("Error found");
						*set = True;
					}
					tokens[i++] = table[k].emulation;
					break;
				case Left:
					if ((tokens[i + 2] != NULL) | (tokens[i + 1] == NULL)) {
						printf("Error found");
						*set = True;
					}
					//Assign the current string in the token array to equal the emulation table. Increment i
					tokens[i] = table[k].emulation;
					//Assign the next token to be the right side constant from the table.
					tokens[i + 2] = table[k].rightSide;
					newTokens++;
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
				//default should not be hit. 
				default:

					break;
				}
			}
		}
	}

	//Correct the number of tokens.
	*numOfTokens = *numOfTokens + newTokens;
	//The tokens have been correctly assembled. Return to the main
		return tokens;

}