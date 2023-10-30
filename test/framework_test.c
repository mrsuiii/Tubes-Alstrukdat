#include "_test_.h"
#include "../lib/get_string.h"
#include "../lib/string.h"
#include "../lib/ADT/boolean.h"

boolean isGreater(int a, int b){
    return a > b;
}

boolean isLess(int a, int b){
    return a > b;
}

void greet(){
    char* s;
    get_string(s, 100);
    printf("Halo, %s!", s);
}

int main(){
    DEFINE_TEST("isGreater Function",
        boolean res = isGreater(1, 2);
    , res == false, "Fungsi salah");

    DEFINE_TEST("isLess Function", 
        boolean res = isLess(1, 2);
    , res == true, "Fungsi salah");

    DEFINE_TEST("Greet IO",
        char in[] = "Bondowoso;"; char* out;

        interceptStdIO(in, &out);
        greet();
        clearStdIO();

        char expected[] = "Hello, Bondowoso!";
        boolean res = string_compare(expected, out) == 0;

        char err[1000];
        if(!res){
            snprintf(err, 1000, "Expected: \"%s\", Actual: \"%s\"", expected, out);
        }
    , res, err)
}