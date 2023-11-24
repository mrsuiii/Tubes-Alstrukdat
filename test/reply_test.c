#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/reply.h"
#include "../lib/relation.h"
#include "../lib/tweet.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Balas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        getUser(ida)->type = PUBLIC_USER;

        TweetId tId1 = createTweet("haloo ini ciko!",ida);

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, -1);
            clearStdIO();

            assert_string_include(err, out, "berhasil dibuat");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun publik. ");
        ,err); 

        getUser(ida)->type = PRIVATE_USER;
        
        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, -1);
            clearStdIO();

            assert_string_include(err, out, "akun privat");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun privat. ");
        ,err); 
        
        requestFriend(ida,idb);
        acceptFriend(ida,idb);

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, -1);
            clearStdIO();

            assert_string_include(err, out, "balasan telah diterbitkan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun publik. ");
        ,err); 

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, 100);
            clearStdIO();

            assert_string_include(err, out, "tidak terdapat balasan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, tidak terdapat balasan. ");
        ,err); 

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(100, -1);
            clearStdIO();

            assert_string_include(err, out, "tidak terdapat kicauan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, tidak terdapat kicauan. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Balasan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        loggedUser->type = PUBLIC_USER;

        TweetId tId1 = createTweet("haloo ini ciko1!",ida);
        TweetId tId2 = createTweet("haloo ini ciko2!",ida);

        // using the IO to make the reply
        SUB_TEST( 
            char in[] = "balasan ke 1 !;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, -1);
            clearStdIO();

            assert_string_include(err, out, "");
            prependError(err, "");
        ,err); 

        // using the IO to make the reply
        SUB_TEST(
            char in[] = "balasan ke 2 !;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, 1);
            clearStdIO();

            assert_string_include(err, out, "");
            prependError(err, "");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(tId1);
            clearStdIO();

            assert_string_include(err, out, "adadwad");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, menampilkan balasan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(tId1);
            clearStdIO();

            assert_string_include(err, out, "Belum terdapat balasan");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, tidak ada balasan. ");
        ,err); 

        getUser(ida)->type = PRIVATE_USER;

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(tId1);
            clearStdIO();

            assert_string_include(err, out, "akun privat");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, balasan kicauan akun privat. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(100);
            clearStdIO();

            assert_string_include(err, out, "Tidak terdapat balasan");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, tidak ada balasan dengan id. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Hapus Balasan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        loggedUser->type = PUBLIC_USER;

        TweetId tId1 = createTweet("haloo ini ciko1!",ida);

        // using the IO to make the reply
        SUB_TEST( 
            char in[] = "balasan ke 1 !;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, -1);
            clearStdIO();

            assert_string_include(err, out, "");
            prependError(err, "");
        ,err); 

        // using the IO to make the reply
        SUB_TEST(
            char in[] = "balasan ke 2 !;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(tId1, 1);
            clearStdIO();

            assert_string_include(err, out, "");
            prependError(err, "");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(tId1, 1);
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, menghapus balasan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(tId1, 10);
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, balasan tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(tId1, 10);
            clearStdIO();

            assert_string_include(err, out, "Jangan dihapus ya!");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, balasan bukan milik pengguna. ");
        ,err); 

        cleanup();
    , err);
}