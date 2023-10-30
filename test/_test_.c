#include <stdio.h>
#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

void test(){
    printf("This is a test!\n");
}

static boolean intercepted;
static FILE* interceptor;
static FILE* feeder;
static FILE* originalStdOut;
static FILE* originalStdIn;
size_t len;

void interceptStdIO(char* bufIn, char** bufOut){
    if(intercepted) return;
    intercepted = true;

    interceptor = open_memstream(bufOut, &len);
    feeder = fmemopen(bufIn, string_length(bufIn), "r");

    originalStdIn = stdin;
    originalStdOut = stdout;

    stdin = feeder;
    stdout = interceptor;
}

void clearStdIO(){
    if(!intercepted) return;
    intercepted = false;

    fflush(interceptor);
    fclose(interceptor);
    fclose(feeder);

    stdin = originalStdIn;
    stdout = originalStdOut;
}