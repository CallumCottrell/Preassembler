#include "Emulate.h"
#define Neither 0x00
#define Right 0x01
#define Left 0x10
#define Both 0x11
/* This table is the emulation table as defined by the Assignment 1 Document
The structure is as follows:
Instruction  Emulation  ArgLocation  Rightsided Argument

A table of structures is useful for returning to the table and editing 
parameters. It is also much lighter from a coding perspective to 
hardcode some of the behaviours of the certain emulations into the table.

This file also contains the size of table function. This is needed 
in order to check the table in the for loop in the Emulate.c file. 
*/
struct emulation table[] = {
{ "ADC.W", "ADDC.W #0,", Right, NULL },
{ "ADC.B", "ADDC.B #0,", Right, NULL },
{ "ADC", "ADDC #0,",  Right, NULL },
{ "CALL", "BL", Neither, NULL },
{ "CLR.W", "MOV.W #0,", Right, NULL },
{ "CLR.B", "MOV.B #0,", Right, NULL },
{ "CLR", "MOV #0,", Right, NULL },
{ "CLRC", "BIC #1,PSW ", Neither, NULL },
{ "CLRN", "BIC #4,PSW ", Neither, NULL },
{ "CLRZ", "BIC #2,PSW ", Neither, NULL },
{ "DADC.W", "DADD.W #0,", Right, NULL },
{ "DADC.B", "DADD.B #0,", Right, NULL },
{ "DADC", "DADD #0,", Right, NULL },
{ "DEC.W", "SUB.W #1,", Right, NULL },
{ "DEC.B", "SUB.B #1,", Right, NULL },
{ "DEC", "SUB #1,", Right, NULL },
{ "DECD.W", "SUB #2 #0,", Right, NULL },
{ "DECD.B", "SUB #2 #0,", Right, NULL },
{ "DECD", "SUB #2 #0,", Right, NULL },
{ "INC.W", "ADD.W #1,", Right, NULL },
{ "INC.B", "ADD.B #1,", Right, NULL },
{ "INC", "ADD #1,", Right, NULL },
{ "INCD.W", "ADD.W #2,", Right, NULL },
{ "INCD.B", "ADD.B #2,", Right, NULL },
{ "INCD", "ADD #2,", Right, NULL },
{ "INV.W", "XOR.W #-1,", Right, NULL },
{ "INV.B", "XOR.B #-1,", Right, NULL },
{ "INV", "XOR #-1,", Right, NULL },
{ "JUMP", "MOV, ", Left, ",PC" },
{ "NOP", "MOV PSW,PSW", Neither, NULL },
{ "PULL", "LD SP+,", Right, NULL },
{ "PUSH", "ST", Left, ",-SP" },
{ "RET", "MOV R4,PC", Right, NULL },
{ "RLC.W", "ADDC.W,", Both, NULL },
{ "RLC.B", "ADDC.B ", Both, NULL },
{ "RLC", "ADDC ", Both, NULL },
{ "SBC.W", "SUBC.W #0,", Right, NULL },
{ "SBC.B", "SUBC.B #0,", Right, NULL },
{ "SBC", "SUBC #0,", Right, NULL },
{ "SETC", "BIS #1,PSW", Neither, NULL },
{ "SETN", "BIS #4,PSW", Neither, NULL },
{ "SETZ", "BIS #2,PSW", Neither, NULL },
{ "SLA.W", "ADD.W ", Both, NULL },
{ "SLA.B", "ADD.B ", Both, NULL },
{ "SLA", "ADD", Both, NULL },
{ "SPL0", "MOVLZ #0,PSW", Neither, NULL },
{ "SPL1", "MOVLZ #20,PSW", Neither, NULL },
{ "SPL2", "MOVLZ #40,PSW", Neither, NULL },
{ "SPL3", "MOVLZ #60,PSW", Neither, NULL },
{ "SPL4", "MOVLZ #80,PSW", Neither, NULL },
{ "SPL5", "MOVLZ #A0,PSW", Neither, NULL },
{ "SPL6", "MOVLZ #C0,PSW", Neither, NULL },
{ "SPL7", "MOVLZ #E0,PSW", Neither, NULL },
{ "TST.W", "CMP.W #0,", Right, NULL },
{ "TST.B", "CMP.B #0,", Right, NULL },
{ "TST", "CMP #0,", Right, NULL }
};

int sizeOfTable(void) {
	/* The sizeof function returns the amount of bytes a variable takes up. The table itself
	takes up enough bytes to contain all the structures. Dividing this amount of bytes by the
	size of one structure (the one at 0 is the safest bet since it will always be filled) returns
	the number of entries in the table.
	*/
	return (sizeof(table) / sizeof(table[0]));
}

