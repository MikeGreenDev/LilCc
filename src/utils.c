#include "utils.h"
#include "defines.h"
#include "scan.h"
#include "vars.h"

void match(TokenTag t, char* c){
    if (Tok.token == t){
        scan(true, &Tok);
    }else {
        errPrintToken("Failed to match tokens", TOKEN_TAG_STRING[Tok.token]);
    }
}
