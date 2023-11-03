#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/relation.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Belum Login", 
        setup();

        char err[MAX_ERROR];
        char in[] = ""; char* out;

        SUB_TEST(
            interceptStdIO(in, &out);
            displayFriendIO();
            clearStdIO();
            cleanup();


            assert_string_include(err, out, "belum login");
            prependError(err, "Function displayFriendIO. ");
        , err)

        SUB_TEST(
            interceptStdIO(in, &out);
            requestFriendIO();
            clearStdIO();
            cleanup();

            assert_string_include(err, out, "belum login");
            prependError(err, "Function requestFriendIO. ");
        , err)
    , err)
}
