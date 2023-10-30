#include "_test_.h"
#include "../lib/greet.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Greet IO Lib",
        char in[] = ""; char* out;

        interceptStdIO(in, &out);
        greet("Bondowoso");
        clearStdIO();

        char expected[] = "Hello, Bondowoso!";
        boolean res = string_include(out, "Bondowoso");
    , res, "")
}