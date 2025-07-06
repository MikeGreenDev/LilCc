#include "statements.h"
#include "astTree.h"
#include "casmTranslator.h"
#include "defines.h"
#include "expression.h"
#include "scan.h"
#include "symTable.h"
#include "translator.h"
#include "utils.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>

// Call this func on the equals sign
void setVariable(int idx) {
    if (Tok.token != T_EQUALS) {
        fprintf(stderr, "Equals not found after variable when trying to set "
                        "the variable.\n");
        exit(1);
    }

    ASTnode* right = astMakeLeaf(T_LVIDENT, idx);

    scan(true, &Tok);
    ASTnode* left = opExpr(0);
    ASTnode* n = astMakeNode(T_ASSIGN, left, right, 0);

    // The variables idx will be stored in the right node & the
    // expression it's assigned will be in the left
    transAST(n, -1);
    freeAllRegs();
    if (Tok.token == T_SEMI_COLON) {
        scan(true, &Tok);
    }
}

void parseStatements(void) {
    while (1) {
        switch (Tok.token) {
            case T_PRINT: {
                scan(true, &Tok);
                ASTnode* n = opExpr(0);
                int res = transAST(n, -1);
                asmPrintInt(res);
                freeAllRegs();
                if (Tok.token == T_SEMI_COLON) {
                    scan(true, &Tok);
                }
                break;
            }
            case T_IDENT: {
                int idx = findSymEntry(CurrentWord);
                char* ident = SymbolsGlobal[idx].name;
                if (findSymEntry(ident) == -1) {
                    fprintf(stderr,
                            "Could not find variable name on Line %d. Did you "
                            "declare it?\n",
                            Line);
                    exit(1);
                }

                scan(true, &Tok);
                setVariable(idx);
                break;
            }
            case T_INT: {
                scan(true, &Tok);
                if (Tok.token != T_IDENT) {
                    fprintf(stderr,
                            "Identifier not found after variable keyword.\n");
                    exit(1);
                }
                int idx = addSymEntry(CurrentWord);
                asmGenVar(CurrentWord);
                scan(true, &Tok);
                if (Tok.token == T_EQUALS) {
                    setVariable(idx);
                } else if (Tok.token == T_SEMI_COLON) {
                    scan(true, &Tok);
                } else {
                    fprintf(stderr,
                            "L: %d SemiColon not found after statement.\n",
                            Line);
                    exit(1);
                }
                break;
            }
            case T_EOF:
                return;
            case T_SEMI_COLON:
            case T_EQUALS:
            case T_PLUS:
            case T_MINUS:
            case T_STAR:
            case T_SLASH:
            case T_INTLIT:
            case T_MAX_TAGS:
            default:
                errPrintToken("Statement not found",
                              TOKEN_TAG_STRING[Tok.token]);
                break;
        }
    }
}
