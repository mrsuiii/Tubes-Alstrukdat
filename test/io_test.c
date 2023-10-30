#include <stdio.h>
#include "_test_.h"

int main(){
    char in[] = "-1"; char* out;
    interceptStdIO(in, &out);

    int t;
    scanf("%d", &t);
    printf("Hello, world! (%d)", t);

    clearStdIO();

    printf("Result: %s", out);
}