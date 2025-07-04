#pragma once

void freeAllRegs(void);
void freeReg(int idx);
int allocReg();
void asmPreamble();
void asmPostamble();
int asmLoad(int value);
int asmAdd(int r1, int r2);
int asmSub(int r1, int r2);
int asmMul(int r1, int r2);
int asmDiv(int r1, int r2);
void asmPrintInt(int r);
