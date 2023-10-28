#include "get_string.h"
#include "ADT/boolean.h"
#include <stdio.h>

#define MARK ';'

char currentChar;

static FILE *pita;
static int retval;

void ADV(){
    retval = fscanf(pita, "%c", &currentChar);
}

void START(){
    pita = stdin;
    ADV();
}

void get_string(char* res, int size){
    START();

    /* Ignore carriage return */
    if(currentChar == '\n') ADV(); 

    int i = 0;
    while(currentChar != MARK && i + 1 < size){
        res[i] = currentChar;
        ++i;
        ADV();
    }

    res[i] = '\0';
};