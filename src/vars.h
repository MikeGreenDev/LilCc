#include "defines.h"
#ifndef extern_
 #define extern_ extern
#endif

#include <stdio.h>

extern_ int Line;
extern_ int SavedChar;
extern_ char CurrentWord[MAX_VAR_LENGTH + 1];
extern_ Token Tok;
extern_ FILE *InputFile;
extern_ FILE *OutFile;
extern_ SymTable SymbolsGlobal[MAX_SYMBOL_NUMBER];

