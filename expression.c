#include "expression.h"
#include "astTree.h"
#include "defines.h"
#include "scan.h"
#include "vars.h"
#include <stdlib.h>

static ASTnode* firstNode(void) {
    ASTnode* n;

    if (Tok.token == T_INTLIT) {
        n = astMakeLeaf(T_INTLIT, Tok.intValue);
        scan(true, &Tok);
        return (n);
    } else {
        // The first node should be an T_INTLIT
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, Tok.token);
        exit(1);
    }
}

// Check that we have a binary operator and
// return its precedence.
static int opPrecedence(TokenTag tokenType) {
    int prec = 0;
    switch (tokenType) {
        case T_EOF:
            prec = 0;
            break;
        case T_PLUS:
        case T_MINUS:
            prec = 10;
            break;
        case T_STAR:
        case T_SLASH:
            prec = 20;
            break;
        case T_INTLIT:
            prec = 0;
            break;
        case T_MAX_TAGS:
        default:
            fprintf(stderr, "Syntax Error on line %d, Token %d\n", Line,
                    tokenType);
            exit(1);
            break;
    }

    if (prec == 0) {
        fprintf(stderr, "Syntax Error on line %d, Token %d\n", Line, tokenType);
        exit(1);
    }
    return (prec);
}

ASTnode* opExpr(int ptp) {
    ASTnode* left;
    ASTnode* right;
    TokenTag tokentype;

    // Get the first token. Should be an INTLIT
    left = firstNode();

    tokentype = Tok.token;
    // If token is EOF then it is End of file. So just return the one node
    if (tokentype == T_SEMI_COLON)
        return (left);

    while (opPrecedence(tokentype) > ptp) {
        scan(true, &Tok);

        right = opExpr(opPrecedence(tokentype));

        left = astMakeNode(tokentype, left, right, 0);

        tokentype = Tok.token;
        if (tokentype == T_SEMI_COLON)
            return (left);
    }

    return (left);
}

int interpretAST(ASTnode* n) {
    int leftval, rightval;

    // Get the left and right values
    if (n->left) {
        leftval = interpretAST(n->left);
    }

    if (n->right) {
        rightval = interpretAST(n->right);
    }
    // Debug: Print what we are about to do
    if (n->op == T_INTLIT) {
        printf("int %d\n", n->intValue);
    } else {
        printf("%d %s %d\n", leftval, TOKEN_TAG_STRING[n->op], rightval);
    }

    switch (n->op) {
        case T_PLUS:
            return (leftval + rightval);
        case T_MINUS:
            return (leftval - rightval);
        case T_STAR:
            return (leftval * rightval);
        case T_SLASH:
            return (leftval / rightval);
        case T_INTLIT:
            return (n->intValue);
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}
