#include <stdio.h>
#include <assert.h>
#include "test.h"
#include "../lib/ADT/time.h"
#include "../lib/greet.h"

int main(){
    TIME T;
    test();
    CreateTime(&T, 11, 2, 10);
    TulisTIME(T);
    printf("\n");
    greet("test");
}