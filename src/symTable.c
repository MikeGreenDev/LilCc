#include "defines.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: For now we will just increment the idx and if we reach the end, we will error it out.
// We'll fix this later
static int SymSlotIdx = 0;

int findSymEntry(char* s){
    for(int i = 0; i < SymSlotIdx; i++){
        if (*s == *SymbolsGlobal[i].name && !strcmp(s, SymbolsGlobal[i].name)){
            return i;
        }
    }
    return -1;
}

static int getNewSymEntry(){
    if (SymSlotIdx + 1 >= MAX_SYMBOL_NUMBER){
        fprintf(stderr, "Maxed out the symbol table.\n");
        exit(1);
    }
    return SymSlotIdx++;
}

int addSymEntry(char* s){
    int x = findSymEntry(s);

    if (x != -1){
        return x;
    }

    x = getNewSymEntry();
    SymbolsGlobal[x].name = strdup(s);
    return x;
}
