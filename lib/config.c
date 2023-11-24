#include "config.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

static FILE* originalStdout;
static FILE* fileWriteIO;

void startWriteFile(char* path){
    originalStdout = stdout;
    fileWriteIO = fopen(path, "w+");
    stdout = fileWriteIO;
}

void finishWriteFile(){
    fclose(fileWriteIO);
    stdout = originalStdout;
}

static FILE* fileReadIO;

static boolean finished = false;
static char currentChar;
char charContainer[2] = " \0";
void readChar(){
    fscanf(fileReadIO, "%c", &currentChar);
    charContainer[0] = currentChar;
    if(feof(fileReadIO)) finished = true;
}

void startReadFile(char* path){
    finished = false;
    fileReadIO = fopen(path, "r");
    readChar();
}

void finishReadFile(){
    fclose(fileReadIO);
}

void ignore(char* chars){
    while(!finished && string_include(chars, charContainer)) readChar();
}

void readTill(char* buff, char* mark, int max){
    int size = 0;
    while(!finished && !string_include(mark, charContainer)){
        if(size < max - 1){
            buff[size] = currentChar;
            ++size;
        }
        readChar();
    }
    buff[size] = '\0';
}

int readInt(){
    int r = 0;
    boolean negated = false;

    if(currentChar == '-'){
        negated = true;
        readChar();
    };

    while(!finished && '0' <= currentChar && currentChar <= '9'){
        r = (r * 10) + (currentChar - '0');
        readChar();
    }

    if(negated) r *= -1;

    return r;
}

void nextWord(){
    while(!finished && (currentChar == '\n' || currentChar == ' ')) readChar();
}

void nextLine(){
    while(!finished && currentChar != '\n') readChar();
    readChar();
}


void readNext(char* str, char* mark, int max){
    int size = 0;

    char stringContainer[2];
    stringContainer[0] = currentChar;
    stringContainer[1] = '\0';

    while(
        fscanf(fileReadIO, "%c", &currentChar) &&
        !string_include(mark, stringContainer)
    ){
        if(feof(fileReadIO)) break;

        if(size < max - 1){
            str[size] = currentChar;
            stringContainer[0] = currentChar;
            ++size;
        }
    }

    str[size] = '\0';
}