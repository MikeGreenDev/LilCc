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
ASTnode* setVariable(int idx) {
    if (Tok.token != T_EQUALS) {
        fprintf(stderr, "Equals not found after variable when trying to set "
                        "the variable.\n");
        exit(1);
    }

    ASTnode* right = astMakeLeaf(T_LVIDENT, idx);

    scan(true, &Tok);
    ASTnode* left = opExpr(0);
    ASTnode* n = astMakeNode(T_ASSIGN, left, NULL, right, 0);

    if (Tok.token == T_SEMI_COLON) {
        scan(true, &Tok);
    }

    return n;
}

ASTnode* whileStatement(void) {
    ASTnode *condAST, *blockAST;
    match(T_WHILE_LOOP, "while");
    lparen();

    condAST = opExpr(0);
    rparen();

    blockAST = parseStatements();

    return astMakeNode(T_WHILE_LOOP, condAST, NULL, blockAST, 0);
}

ASTnode* ifStatement(void) {
    ASTnode *condAST, *trueAST, *falseAST = NULL;

    match(T_IF, "if");
    lparen();

    condAST = opExpr(0);
    rparen();

    trueAST = parseStatements();

    if (Tok.token == T_ELSE) {
        scan(true, &Tok);
        falseAST = parseStatements();
    }

    return astMakeNode(T_IF, condAST, trueAST, falseAST, 0);
}

ASTnode* parseStatements(void) {
    ASTnode* tree;
    ASTnode* left = NULL;

    lbrace();

    while (1) {
        switch (Tok.token) {
            case T_PRINT: {
                scan(true, &Tok);
                ASTnode* n = opExpr(0);
                tree = astMakeUnary(T_PRINT, n, 0);
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
                tree = setVariable(idx);
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
                tree = NULL;
                if (Tok.token == T_EQUALS) {
                    tree = setVariable(idx);
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
            case T_IF: {
                tree = ifStatement();
                break;
            }
            case T_WHILE_LOOP: {
                tree = whileStatement();
                break;
            }
            case T_RBRACE: {
                rbrace();
                return left;
            }
            default:
                errPrintToken("Statement not found",
                              TOKEN_TAG_STRING[Tok.token]);
                break;
        }

        if (tree) {
            if (left == NULL) {
                left = tree;
            } else {
                left = astMakeNode(T_GLUE, left, NULL, tree, 0);
            }
        }
    }
}
