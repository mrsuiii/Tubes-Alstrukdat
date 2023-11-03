#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/relation.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Daftar Teman", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayFriendIO();
            clearStdIO();

            assert_string_include(err, out, "belum mempunyai teman");
            prependError(err, "Perintah DAFTAR_TEMAN. Gagal tidak memiliki teman. ");
        ,err);

        requestFriend(ida,idb);
        acceptFriend(ida,idb); 
        
        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayFriendIO();
            clearStdIO();

            assert_string_include(err, out, "Daftar teman");
            prependError(err, "Perintah DAFTAR_TEMAN. Gagal menampilkan teman. ");
            
        ,err);

        cleanup();
    , err)


    DEFINE_TEST("Hapus Teman", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        
        SUB_TEST( 
            char in[] = "Afif;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "bukan teman Anda");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal menghapus teman. ");
        ,err)

        requestFriend(ida,idb);
        acceptFriend(ida,idb);

        SUB_TEST( 
            char in[] = "Afif;TIDAK;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "Penghapusan teman dibatalkan");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal pembatalan hapus. ");
        ,err)

        SUB_TEST( 
            char in[] = "Afif;YA;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal menghapuskan teman. ");
        ,err)

        cleanup();
    , err)

}

