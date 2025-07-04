#include "scan.h"
#include "defines.h"
#include "vars.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int chrpos(char* s, int c) {
    char* p;

    p = strchr(s, c);
    return (p ? p - s : -1);
}

int nextChar() {
    int c;

    if (SavedChar) {
        // Use the SavedChar that we saved first
        c = SavedChar;
        SavedChar = 0;
    } else {
        c = fgetc(InputFile);

        // Increment the line number
        if (c == '\n') {
            Line++;
        }
    }

    return c;
}

int scanInt(char c) {
    int k, val = 0;

    // Convert each character into an int value
    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = nextChar();
    }

    SavedChar = c;
    return val;
}

int scan(char skipWhiteSpace, Token* outToken) {
    int c;

    c = nextChar();
    if (skipWhiteSpace) {
        while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
            c = nextChar();
        }
    }

    // Find the token based the char
    switch (c) {
        case EOF:
            outToken->token = T_EOF;
            return 0;
        case '+':
            outToken->token = T_PLUS;
            break;
        case '-':
            outToken->token = T_MINUS;
            break;
        case '*':
            outToken->token = T_STAR;
            break;
        case '/':
            outToken->token = T_SLASH;
            break;
        default:
            if (isdigit(c)) {
                outToken->intValue = scanInt(c);
                outToken->token = T_INTLIT;
            } else {
                printf("Syntax Error: Unknown token found on Line %d", Line);
            }
            break;
    }

    return 1;
}
