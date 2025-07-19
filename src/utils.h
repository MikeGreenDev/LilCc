#pragma once

#include "defines.h"
#include "stdlib.h"

#define errPrint(s)                                                            \
    fprintf(stderr, "Line: %d. %s\n", Line, s);                                \
    exit(1);

#define errPrintToken(s, ts)                                                   \
    fprintf(stderr, "Line: %d. %s. Token: %s\n", Line, s, ts);                 \
    exit(1);\

void match(TokenTag t, char* c);

#define semi() match(T_SEMI_COLON, ";");
#define lbrace() match(T_LBRACE, "{");
#define rbrace() match(T_RBRACE, "}");
#define lparen() match(T_LPAREN, "(");
#define rparen() match(T_RPAREN, ")");
