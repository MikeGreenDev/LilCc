#pragma once

typedef struct {
    int token;
    int intValue;
} Token;

// Make sure T_MAX_TAGS is ALWAYS at the end. It's used as a sort of
// null pointer for loops
#define FOREACH_TAG(TAG)                                                       \
    TAG(T_PLUS)                                                                \
    TAG(T_MINUS)                                                               \
    TAG(T_STAR)                                                                \
    TAG(T_SLASH)                                                               \
    TAG(T_INTLIT)                                                              \
    TAG(T_MAX_TAGS)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum TokenTag { FOREACH_TAG(GENERATE_ENUM) } TokenTag;

static const char* TOKEN_TAG_STRING[] = {FOREACH_TAG(GENERATE_STRING)};
