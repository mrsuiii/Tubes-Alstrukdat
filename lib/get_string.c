#include "get_string.h"
#include "ADT/charmachine.h"


void get_string(char* res, int size){
    START();

    int i = 0;
    while(!EOP && currentChar != '\n' && i + 1 < size){
        res[i] = currentChar;
        ++i;
        ADV();
    }

    res[i] = '\0';
};