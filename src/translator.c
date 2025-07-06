#include "translator.h"
#include "casmTranslator.h"
#include "defines.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>

int transAST(ASTnode* n, int reg) {
    int leftval, rightval;

    // Get the left and right values
    if (n->left) {
        leftval = transAST(n->left, -1);
    }

    if (n->right) {
        rightval = transAST(n->right, leftval);
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
            return asmCmpEq(leftval, rightval);
        case T_NEQ:
            return asmCmpNeq(leftval, rightval);
        case T_LT:
            return asmCmpLt(leftval, rightval);
        case T_GT:
            return asmCmpGt(leftval, rightval);
        case T_LE:
            return asmCmpLe(leftval, rightval);
        case T_GE:
            return asmCmpGe(leftval, rightval);
        default:
            fprintf(stderr, "Unknown AST operator %s\n",
                    TOKEN_TAG_STRING[n->op]);
            exit(1);
    }
}

void createOutFileAsm(ASTnode* n) {
    asmPreamble();
    int n2 = transAST(n, -1);
    asmPrintInt(n2);
    asmPostamble();
}
