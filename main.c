#include <stdio.h>
#include "lib/greet.h"
#include "lib/get_string.h"

int main(){
    printf("Masukkan nama lengkap Anda: ");

    int maxName = 100;
    char name[maxName];
    get_string(name, maxName);

    greet(name);
}