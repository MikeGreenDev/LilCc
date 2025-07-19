#include "defines.h"

ASTnode* astMakeNode(int op, ASTnode* left, ASTnode* mid, ASTnode* right,
                     int intvalue);
void astFreeNode(ASTnode* n);
ASTnode* astMakeLeaf(int op, int intvalue);
ASTnode* astMakeUnary(int op, ASTnode* left, int intvalue);
