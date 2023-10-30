#include <stdio.h>
#include "string.h"
# include "ADT/boolean.h"

void string_copy(char* from, char* to, int max){
    if(max == 0) return;

    int i = 0;
    for(; i < max - 1; ++i){
        if(from[i] == '\0') break;
        to[i] = from[i];
    }
    to[i] = '\0';
};

int string_compare(char* a, char* b){
    int ia = 0, ib = 0;
    while(a[ia] != '\0' && b[ib] != '\0'){
        if(a[ia] > b[ib]){
            return 1;
        } else if(a[ia] < b[ib]){
            return -1;
        }

        ia++; ib++;
    }

    if(a[ia] == '\0' && b[ib] == '\0') return 0;
    else if(a[ia] == '\0') return -1;
    else return 1;
}

int string_length(char* a){
    int i = 0;
    while (a[i] != '\0'){
        i++;
    }
    return i;
}

boolean isAllBlank(char* a){
    int i = 0 ; 
    while (a[i] != '\0'){
        if (a[i] != ' ') return false;
        i++;
    }
    return true ; 
}

boolean string_include(char* str, char* substr){
    int strLen = string_length(str);
    int substrLen = string_length(substr);

    for(int i = 0; i <= strLen - substrLen; ++i){
        int m = 0;
        for(int j = 0; j < substrLen; ++j){
            if(str[i + j] == substr[j]) ++m;
            else break;
        }

        if(m == substrLen) return true;
    }
    return false;
}