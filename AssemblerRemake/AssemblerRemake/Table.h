#ifndef Emulation
#define Emulation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define Neither 0x00
#define Right 0x01
#define Left 0x10
#define Both 0x11

/*
This struc holds the information in the table. Instructions and their emulations
are straightforward. Position indicates where an argument needs to be placed, and
rightSide is the string that needs to be placed after the argument for the instruction.*/
struct emulation {
	const char *instruction;
	const char *emulation;
	int position;
	char *rightSide;
};

int sizeOfTable(void);


#endif