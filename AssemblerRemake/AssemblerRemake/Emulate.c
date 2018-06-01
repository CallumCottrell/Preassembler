#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Table.h"
#include "Emulate.h"

extern struct emulation table[];

void doTheThing(char *record) {

	char buff = strtok(record, " ");
	char tokens[200];
	int i = 0;

	while (buff != NULL) {
		tokens[i] = buff;
		i++;
		buff = strtok(NULL, ", ");
	}

	i = 0;
	char set = 0x00;
	while (tokens[i] != NULL) {
		for (int k = 0; k < sizeOfTable(); k++) {
			if (strcmp(tokens[i], table[k].instruction) == 0) { // cannot just compare strings willy nilly. use strcmp.
				printf("success, both equal %s \n", tokens[i]);
				set = 0x01;
				\
					tokens[i] = table[k].emulation;
			}
		}
		i++;
		set = 0x00;
	}
	int k = sizeOfTable();
	/* for (int i; i < amountOfTokens; i++) {
	for ( int k = 0; k = sizeOfTable(); k++){
	if(tokens[i] == table[k].instruction){
	printf("success");
	}
	}
	}
	*/


	/*
	switch (table[1].position) {
	case Neither: // the right
	printf("instruction has no arguments\n");
	break;
	case 0x01:
	printf("instruction has an argumen2t on the right\n");
	break;
	default:
	break;
	}
	*/



	getchar();


}