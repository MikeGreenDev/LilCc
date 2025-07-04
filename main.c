#include "defines.h"
#define extern_
#include "vars.h"
#undef extern_
#include "scan.h"
#include "expression.h"
#include "translator.h"
#include <stdio.h>


int main(int argc, char** argv) {
    Line = 0;
    SavedChar = '\n';

    if ((InputFile = fopen(argv[1], "r")) == NULL){
        printf("Error opening file");
        return 1;
    }

    if ((OutFile = fopen("out.s", "w")) == NULL){
        printf("Error opening file");
        return 1;
    }

    scan(true, &Tok);
    ASTnode* n = opExpr(0);
    printf("Calculated answer: %d\n", interpretAST(n));
    createOutFileAsm(n);

    fclose(OutFile);
    fclose(InputFile);
    return 0;
}
