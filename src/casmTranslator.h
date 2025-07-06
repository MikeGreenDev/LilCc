#pragma once

void freeAllRegs(void);
void freeReg(int idx);
int allocReg();
void asmPreamble();
void asmPostamble();
int asmLoadInt(int value);
int asmAdd(int r1, int r2);
int asmSub(int r1, int r2);
int asmMul(int r1, int r2);
int asmDiv(int r1, int r2);
void asmPrintInt(int r);
int asmAssignVar(int reg, char* identifier);
int asmAssignReg(char* identifier);
void asmGenVar(char* identifier);

int asmCmpEq(int r1, int r2);
int asmCmpNeq(int r1, int r2);
int asmCmpLt(int r1, int r2);
int asmCmpGt(int r1, int r2);
int asmCmpLe(int r1, int r2);
int asmCmpGe(int r1, int r2);
