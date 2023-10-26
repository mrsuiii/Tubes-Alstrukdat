#include <stdio.h>
#include <assert.h>
#include "test.h"
#include "../time.h"

int main(){
    TIME T;
    test();
    CreateTime(&T, 11, 2, 10);
    TulisTIME(T);
}