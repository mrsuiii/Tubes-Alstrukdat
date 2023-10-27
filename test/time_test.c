#include <stdio.h>
#include <assert.h>
#include "_test_.h"
#include "../lib/ADT/time.h"
#include "../lib/greet.h"

int main(){
    test();

    TIME T;
    CreateTime(&T, 11, 2, 10);
    TulisTIME(T);
}