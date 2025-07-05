#pragma once

#define true 1
#define false 0

#define MAX_VAR_LENGTH 512
#define MAX_SYMBOL_NUMBER 1024

// Make sure T_MAX_TAGS is ALWAYS at the end. It's used as a sort of
// null pointer for loops
#define FOREACH_TAG(TAG)                                                       \
    TAG(T_EOF)                                                                 \
    TAG(T_PLUS)                                                                \
    TAG(T_MINUS)                                                               \
    TAG(T_STAR)                                                                \
    TAG(T_SLASH)                                                               \
    TAG(T_INTLIT)                                                              \
    TAG(T_EQUALS)                                                              \
    TAG(T_INT)                                                                 \
    TAG(T_SEMI_COLON)                                                          \
    TAG(T_PRINT)                                                               \
    TAG(T_IDENT)                                                               \
    TAG(T_LVIDENT)                                                             \
    TAG(T_ASSIGN)                                                              \
    TAG(T_MAX_TAGS)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum TokenTag { FOREACH_TAG(GENERATE_ENUM) } TokenTag;

static const char* TOKEN_TAG_STRING[] = {FOREACH_TAG(GENERATE_STRING)};

typedef struct {
    char* name;
} SymTable;

typedef struct {
    TokenTag token;
    int intValue;
} Token;

typedef struct ASTnode {
    int op;
    struct ASTnode* left;
    struct ASTnode* right;
    union value {
        int intValue;
        int id;
    } value;
} ASTnode;
