#include "get_string.h"
#include "ADT/boolean.h"
#include <stdio.h>

#define GET_STRING_MARK ';'

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
    while(currentChar != GET_STRING_MARK && i + 1 < size){
        res[i] = currentChar;
        ++i;
        ADV();
    }

    res[i] = '\0';
};

void get_string_foto_profil(char* color, char* picture, int size){
    START();

    /* Ignore carriage return */
    if (currentChar == '\n') ADV();

    int colori = 0, picturei = 0;
    while(currentChar != GET_STRING_MARK && colori + 1 <= size && picturei + 1 <= size){
        if (currentChar != ' ' && currentChar != '\n'){
            if (currentChar == 'R' || currentChar == 'G' || currentChar == 'B'){
                color[colori] = currentChar;
                colori++;
            } else{
                picture[picturei] = currentChar;
                picturei++;
            }
        }
        ADV();
    }

    color[colori] = '\0';
    picture[picturei] = '\0';
}