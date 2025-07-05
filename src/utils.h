#pragma once

#include "defines.h"
#include <stdlib.h>

#define errPrint(s)                                                            \
    fprintf(stderr, "Line: %d. %s\n", Line, s);                                \
    exit(1);

#define errPrintToken(s, ts)                                                   \
    fprintf(stderr, "Line: %d. %s. Token: %s\n", Line, s, ts);                 \
    exit(1);\
