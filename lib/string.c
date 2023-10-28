#include "string.h"

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
    else if(a[ia] == '\0') return 1;
    else return -1;
}
