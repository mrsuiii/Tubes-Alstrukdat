#ifndef TEST
#define TEST

#include <stdio.h>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

#define DEFINE_TEST(_name, _test, _result, _error) {\
    _test;\
    if(_result){\
        printf("\x1B[32m✓ \x1B[0m%s\n", _name);\
    }else{\
        printf("\x1B[31m✗ \x1B[0m%s (%s)\n", _name, _error);\
    }\
}

void test();
void interceptStdIO(char* bufIn, char** bufOut);
void clearStdIO();

#endif