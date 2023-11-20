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

void startReadFile(char* path){
    fileReadIO = fopen(path, "r");
}

void finishReadFile(){
    fclose(fileReadIO);
}

void readNext(char* str, char mark, int max){
    int size = 0;

    char current;
    while(
        fscanf(fileReadIO, "%c", &current) &&
        current != mark
    ){
        if(size < max - 1){
            str[size] = current;
            ++size;
        }

        if(feof(fileReadIO)) break;
    }

    str[size] = '\0';
}