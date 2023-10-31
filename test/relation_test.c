#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/relation.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Belum Login", 
        setup();

        char in[] = ""; char* out;
        interceptStdIO(in, &out);
        displayFriendIO();
        clearStdIO();

        cleanup();

        boolean res = string_include(out, "belum login");
    , res, "Tidak terdapat pesan yang sesuai")
}
