#include "translator.h"
#include "casmTranslator.h"
#include <stdio.h>
#include <stdlib.h>

int transAST(ASTnode* n){
    int leftval, rightval;

    // Get the left and right values
    if (n->left) {
        leftval = transAST(n->left);
    }

    if (n->right) {
        rightval = transAST(n->right);
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
            return asmLoad(n->intValue);
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}

void createOutFileAsm(ASTnode* n){
    asmPreamble();
    int n2 = transAST(n);
    asmPrintInt(n2);
    asmPostamble();
}
