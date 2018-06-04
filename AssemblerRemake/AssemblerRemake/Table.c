#include "Emulate.h"
#define Neither 0x00
#define Right 0x01
#define Left 0x10
#define Both 0x11
/* This table is the emulation table as defined by the Assignment 1 Document
The structure is as follows:
Instruction  Emulation  ArgLocation  Rightsided Argument*/
struct emulation table[] = {
{ "ADC.W", "ADDC.W #0,", Right, NULL },
{ "ADC.B", "ADDC.B #0,", Right, NULL },
{ "ADC", "ADDC #0,",  Right, NULL },
{ "CALL", "BL", Neither, NULL },
{ "CLR.W", "MOV.W #0,", Right, NULL },
{ "CLR.B", "MOV.B #0,", Right, NULL },
{ "CLR", "MOV #0,", Right, NULL },
{ "CLRC", "BIC #1,R6 ", Neither, NULL },
{ "CLRN", "BIC #4,R6 ", Neither, NULL },
{ "CLRZ", "BIC #2,R6 ", Neither, NULL },
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
{ "JUMP", "MOV, ", Left, ",R7" },
{ "NOP", "MOV R6,R6", Neither, NULL },
{ "PULL", "LD R5+,", Right, NULL },
{ "PUSH", "ST", Left, ",-R5" },
{ "RET", "MOV R4,R7", Right, NULL },
{ "RLC.W", "ADDC.W,", Both, NULL },
{ "RLC.B", "ADDC.B ", Both, NULL },
{ "RLC", "ADDC ", Both, NULL },
{ "SBC.W", "SUBC.W #0,", Right, NULL },
{ "SBC.B", "SUBC.B #0,", Right, NULL },
{ "SBC", "SUBC #0,", Right, NULL },
{ "SETC", "BIS #1,R6", Neither, NULL },
{ "SETN", "BIS #4,R6", Neither, NULL },
{ "SETZ", "BIS #2,R6", Neither, NULL },
{ "SLA.W", "ADD.W ", Both, NULL },
{ "SLA.B", "ADD.B ", Both, NULL },
{ "SLA", "ADD", Both, NULL },
{ "SPL0", "MOVLZ #0,R6", Neither, NULL },
{ "SPL1", "MOVLZ #20,R6", Neither, NULL },
{ "SPL2", "MOVLZ #40,R6", Neither, NULL },
{ "SPL3", "MOVLZ #60,R6", Neither, NULL },
{ "SPL4", "MOVLZ #80,R6", Neither, NULL },
{ "SPL5", "MOVLZ #A0,R6", Neither, NULL },
{ "SPL6", "MOVLZ #C0,R6", Neither, NULL },
{ "SPL7", "MOVLZ #E0,R6", Neither, NULL },
{ "TST.W", "CMP.W #0,", Right, NULL },
{ "TST.B", "CMP.B #0,", Right, NULL },
{ "TST", "CMP #0,", Right, NULL }
};

int sizeOfTable(void) {
	return (sizeof(table) / sizeof(table[0]));
}

