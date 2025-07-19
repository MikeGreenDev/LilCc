#include "scan.h"
#include "defines.h"
#include "utils.h"
#include "vars.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextChar();

int scanWholeWord(char c, int limit, char* outBuffer){
    int i = 0;

    while (isalpha(c) || isdigit(c) || c == '_'){
        if (i + 1 > limit){
            fprintf(stderr, "Reached maximum char length for variables");
            exit(1);
        }
        outBuffer[i++] = c;
        c = nextChar();
    }
    SavedChar = c;
    outBuffer[i] = '\0';
    return i;
}

int matchKeywords(char* c){
    switch (*c) {
        case 'e': {
                      if (!strcmp(c, "else")){
                          return T_ELSE;
                      }
                      break;
                  }
        case 'p': {
                    if (!strcmp(c, "print")){
                        return T_PRINT;
                    }
                    break;
                  }
        case 'i': {
                    if (!strcmp(c, "int")){
                        return T_INT;
                    } else if (!strcmp(c, "if")){
                        return T_IF;
                    }
                    break;
                  }
    }
    return 0;
}

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
        case ';':
            outToken->token = T_SEMI_COLON;
            break;
        case '=':
            c = nextChar();
            if (c == '='){
                outToken->token = T_EQ;
            }else{
                outToken->token = T_EQUALS;
                SavedChar = c;
            }
            break;
        case '!':
            c = nextChar();
            if (c == '='){
                outToken->token = T_NEQ;
            }else{
                errPrint("Unknown character after '!'");
            }
            break;
        case '<':
            c = nextChar();
            if (c == '='){
                outToken->token = T_LE;
            }else{
                outToken->token = T_LT;
                SavedChar = c;
            }
            break;
        case '>':
            c = nextChar();
            if (c == '='){
                outToken->token = T_GE;
            }else{
                outToken->token = T_GT;
                SavedChar = c;
            }
            break;
        case '(':
            outToken->token = T_LPAREN;
            break;
        case ')':
            outToken->token = T_RPAREN;
            break;
        case '{':
            outToken->token = T_LBRACE;
            break;
        case '}':
            outToken->token = T_RBRACE;
            break;
        default:
            if (isdigit(c)) {
                outToken->intValue = scanInt(c);
                outToken->token = T_INTLIT;
            } else if (isalpha(c)){
                scanWholeWord(c, MAX_VAR_LENGTH, CurrentWord);
                TokenTag t;
                if ((t = matchKeywords(CurrentWord))){
                    outToken->token = t;
                    break;
                }
                outToken->token = T_IDENT;
            } else {
                fprintf(stderr, "Syntax Error: Unknown token found on Line %d", Line);
                exit(1);
            }
            break;
    }

    return 1;
}
