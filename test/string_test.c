#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("String length", 
        int l = string_length("12345");
    , l == 5, "")

    DEFINE_TEST("String copy",
        char a[] = "abcdefgh";
        char b[10] = "\0";

        string_copy(a, b, 10);

        boolean res = string_compare(a, b) == 0;

        char err[MAX_ERROR];
        if(!res) snprintf(err, MAX_ERROR, "%s != %s", a, b);
    , res, err);

    DEFINE_TEST("String compare",
        int t; char err[MAX_ERROR];
        err[0] = '\0';

        t = string_compare("a", "b");
        if(!(*err) && t != -1){
            snprintf(err, MAX_ERROR, "Since a < b, expected -1. Instead got %d", t);
        }

        t = string_compare("b", "a");
        if(!(*err) && t != 1){
            snprintf(err, MAX_ERROR, "Since b < a, expected 1. Instead got %d", t);
        }

        t = string_compare("a", "aa");
        if(!(*err) && t != -1){
            snprintf(err, MAX_ERROR, "Since a < aa, expected -1. Instead got %d", t);
        }

        t = string_compare("aa", "a");
        if(!(*err) && t != 1){
            snprintf(err, MAX_ERROR, "Since aa < a, expected 1. Instead got %d", t);
        }

        t = string_compare("aaa", "aaa");
        if(!(*err) && t != 0){
            snprintf(err, MAX_ERROR, "Since aaa = aaa, expected 0. Instead got %d", t);
        }
    , !(*err), err)

    DEFINE_TEST("String include",
        boolean res = string_include("abcd", "bc");
    , res, "");
}