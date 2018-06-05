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

struct emulation {
	const char *instruction;
	const char *emulation;
	int position;
	char *rightSide;
};

int sizeOfTable(void);


#endif