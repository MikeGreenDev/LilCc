#include "translator.h"
#include "casmTranslator.h"
#include "defines.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>

int label(){
    static int labelIdx = 0;
    return labelIdx++;
}

int transWhileAST(ASTnode* n){
    int lStart = label();
    int lEnd = label();

    asmLabel(lStart);
    transAST(n->left, lEnd, n->op);
    freeAllRegs();
    transAST(n->right, -1, n->op);
    freeAllRegs();
    asmJump(lStart);
    asmLabel(lEnd);

    return -1;
}

int transIfAST(ASTnode* n){
    int lFalse, lEnd;

    if (n->right){
        lFalse = label();
    }
    lEnd = label();

    transAST(n->left, lFalse, n->op);
    freeAllRegs();
    transAST(n->mid, -1, n->op);
    freeAllRegs();

    if (n->right){
        asmJump(lEnd);
        asmLabel(lFalse);
        transAST(n->right, -1, n->op);
        freeAllRegs();
    }
    asmLabel(lEnd);
    return -1;
}

int transAST(ASTnode* n, int reg, TokenTag parentTok) {
    int leftval, rightval;

    switch (n->op) {
        case T_WHILE_LOOP:
            return transWhileAST(n);
        case T_IF:
            return transIfAST(n);
        case T_GLUE:
            transAST(n->left, -1, n->op);
            freeAllRegs();
            transAST(n->right, -1, n->op);
            freeAllRegs();
            return -1;
    }

    // Get the left and right values
    if (n->left) {
        leftval = transAST(n->left, -1, n->op);
    }

    if (n->right) {
        rightval = transAST(n->right, leftval, n->op);
    }

    switch (n->op) {
        case T_PLUS:
            return asmAdd(leftval, rightval);
        case T_MINUS:
            return asmSub(leftval, rightval);
        case T_STAR:
            return asmMul(leftval, rightval);
        case T_SLASH:
            return asmDiv(leftval, rightval);
        case T_INTLIT:
            return asmLoadInt(n->value.intValue);
        case T_IDENT:
            return asmAssignReg(SymbolsGlobal[n->value.id].name);
        case T_LVIDENT:
            return asmAssignVar(reg, SymbolsGlobal[n->value.id].name);
        case T_ASSIGN:
        case T_EQUALS:
            return rightval;
        case T_EQ:
        case T_NEQ:
        case T_LT:
        case T_GT:
        case T_LE:
        case T_GE:
            if (parentTok == T_IF || parentTok == T_WHILE_LOOP || parentTok == T_FOR_LOOP || parentTok == T_DO_LOOP){
                return asmCompareJump(n->op, leftval, rightval, reg);
            }else{
                return asmCompareSet(n->op, leftval, rightval);
            }
        case T_PRINT:
            asmPrintInt(leftval);
            freeAllRegs();
            return -1;
        default:
            fprintf(stderr, "Unknown AST operator %s\n",
                    TOKEN_TAG_STRING[n->op]);
            exit(1);
    }
}

void createOutFileAsm(ASTnode* n) {
    asmPreamble();
    int n2 = transAST(n, -1, n->op);
    asmPrintInt(n2);
    asmPostamble();
}
