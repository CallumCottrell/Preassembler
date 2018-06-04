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
//This function will tokenize the Record into separate tokens. The assumed maximum size for a Record

void doTheThing(char *noComments) {
	char bigBuff[200]; // A char array to hold the Non-Comment tokens from the Record
	char smallBuff[15];
	int sizeOfRecord = sprintf(bigBuff, "%s" , noComments);
	int numOfTokens;
	int set = 0;

	char *toker = strtok(bigBuff, ", "); // start reading the buffer and parse by spaces and ,
	char *tokens[80];
	int i = 0;

	while (toker != NULL) {
		tokens[i++] = toker;
		toker = strtok(NULL, ", ");
	}

	numOfTokens = i;
	tokens[i] = NULL;

	//Check each token
	for (i =0; i < numOfTokens; i++) {
		//Check every instruction in the table
		for (int k = 0; k < sizeOfTable(); k++) {
			//If there is a match....
			if (_stricmp(tokens[i], table[k].instruction) == 0) { // cannot just compare strings willy nilly. use strcmp.
				printf("\nsuccess! you found a match on %s and the position of the argument is: %d\n", tokens[i], table[k].position);
				//Check how the handle the emulation. Dependent on the amount of arguments.
				switch (table[k].position) {
				case Neither: 
					printf("instruction has no arguments\n");
					tokens[i] = table[k].emulation;
					break;

				case Right:
					printf("instruction has an argument on the right\n");
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
					tokens[i++] = table[k].emulation;
					tokens[i + 1] = table[k].rightSide;
					break;
				case Both:
					printf("instruction arguments both side."); 
					if ((tokens[i + 2] != NULL )|(tokens[i+1] == NULL)) {
						printf("Error found");
						set = True;
					}
					sprintf(smallBuff, "%s, %s", tokens[i + 1], tokens[i + 1]);
					tokens[i++] = table[k].emulation; // skippin over to the next 
					tokens[i] = smallBuff;
					break;

				default:
					break;
				}
			}
		}

	}
		printf("\n");
	for (i = 0; i < numOfTokens; i++) {
		printf("%s ", tokens[i]);
	}


	getchar();


}