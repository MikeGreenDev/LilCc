#include "defines.h"
#define extern_
#include "vars.h"
#undef extern_
#include "scan.h"
#include <stdio.h>


int main(int argc, char** argv) {
    Line = 1;
    SavedChar = '\n';

    Token tok;

    if ((InputFile = fopen(argv[1], "r")) == NULL){
        printf("Error opening file");
        return 1;
    }

    while (scan(1, &tok)) {
        printf("Token %s", TOKEN_TAG_STRING[tok.token]);
        if (tok.token == T_INTLIT)
            printf(", value %d", tok.intValue);
        printf("\n");
    }

    return 0;
}
