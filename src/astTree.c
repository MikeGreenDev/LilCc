#include "astTree.h"
#include <stdio.h>
#include <stdlib.h>

// Make an ast node with 2 children (Can be NULL)
ASTnode* astMakeNode(int op, ASTnode* left,ASTnode* mid, ASTnode* right, int intvalue) {
    ASTnode* n;

    // Malloc a new ASTnode
    n = malloc(sizeof(ASTnode));

    if (n == NULL) {
        fprintf(stderr, "Unable to malloc in astMakeNode()\n");
        exit(1);
    }

    // Copy in the field values and return it
    n->op = op;
    n->left = left;
    n->mid = mid;
    n->right = right;
    n->value.intValue = intvalue;
    return (n);
}

// Free the nodes
void astFreeNode(ASTnode* n) {
    free(n);
}

// Make an AST leaf node (No children)
ASTnode* astMakeLeaf(int op, int intvalue) {
    return (astMakeNode(op, NULL, NULL, NULL, intvalue));
}

// Make a unary node (only one child)
ASTnode* astMakeUnary(int op, ASTnode* left, int intvalue) {
    return (astMakeNode(op, left, NULL, NULL, intvalue));
}
