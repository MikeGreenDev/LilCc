#include "casmTranslator.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>

static char* regs[] = {"%r8", "%r9", "%r10", "%r11"};
static int availRegs[4] = {1, 1, 1, 1};

void freeAllRegs(void) {
    availRegs[0] = 1;
    availRegs[1] = 1;
    availRegs[2] = 1;
    availRegs[3] = 1;
}

void freeReg(int idx) {
    if (availRegs[idx] != 0) fprintf(stderr, "Freeing an asm reg that is already freed.");
    availRegs[idx] = 1;
}

int allocReg() {
    for (int i = 0; i < 4; i++) {
        if (availRegs[i]) {
            availRegs[i] = 0;
            return i;
        }
    }

    fprintf(stderr, "Failed to find an available register");
    exit(1);
}

// In order to print the calculated answer we need to be able to print ints
// so I just pasted that code in the preamble for now
void asmPreamble() {
    freeAllRegs();
    fputs("\t.text\n"
          ".LC0:\n"
          "\t.string\t\"%d\\n\"\n"
          "printint:\n"
          "\tpushq\t%rbp\n"
          "\tmovq\t%rsp, %rbp\n"
          "\tsubq\t$16, %rsp\n"
          "\tmovl\t%edi, -4(%rbp)\n"
          "\tmovl\t-4(%rbp), %eax\n"
          "\tmovl\t%eax, %esi\n"
          "\tleaq	.LC0(%rip), %rdi\n"
          "\tmovl	$0, %eax\n"
          "\tcall	printf@PLT\n"
          "\tnop\n"
          "\tleave\n"
          "\tret\n"
          "\n"
          "\t.globl\tmain\n"
          "\t.type\tmain, @function\n"
          "main:\n"
          "\tpushq\t%rbp\n"
          "\tmovq	%rsp, %rbp\n",
          OutFile);
}

// Print out the assembly postamble
void asmPostamble() {
    fputs("\tmovl	$0, %eax\n"
          "\tpopq	%rbp\n"
          "\tret\n",
          OutFile);
}

// Load an integer literal value into a register.
// Return the number of the register
int asmLoad(int value) {
    int r = allocReg();
    fprintf(OutFile, "\tmovq\t$%d, %s\n", value, regs[r]);
    return (r);
}

// Add two registers together and return
// the number of the register with the result
int asmAdd(int r1, int r2) {
    fprintf(OutFile, "\taddq\t%s, %s\n", regs[r1], regs[r2]);
    freeReg(r1);
    return (r2);
}

// Subtract the second register from the first and
// return the number of the register with the result
int asmSub(int r1, int r2) {
    fprintf(OutFile, "\tsubq\t%s, %s\n", regs[r2], regs[r1]);
    freeReg(r2);
    return (r1);
}

// Multiply two registers together and return
// the number of the register with the result
int asmMul(int r1, int r2) {
    fprintf(OutFile, "\timulq\t%s, %s\n", regs[r1], regs[r2]);
    freeReg(r1);
    return (r2);
}

// Divide the first register by the second and
// return the number of the register with the result
int asmDiv(int r1, int r2) {
    fprintf(OutFile, "\tmovq\t%s,%%rax\n", regs[r1]);
    fprintf(OutFile, "\tcqo\n");
    fprintf(OutFile, "\tidivq\t%s\n", regs[r2]);
    fprintf(OutFile, "\tmovq\t%%rax,%s\n", regs[r1]);
    freeReg(r2);
    return (r1);
}

// Call printint() with the given register
void asmPrintInt(int r) {
    fprintf(OutFile, "\tmovq\t%s, %%rdi\n", regs[r]);
    fprintf(OutFile, "\tcall\tprintint\n");
    freeReg(r);
}
