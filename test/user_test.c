#include "_test_.h"
#include "../lib/user.h"
#include "../lib/ADT/boolean.h"
#include "../lib/routine.h"

int main(){
    DEFINE_TEST("Daftar Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        SUB_TEST(
            char in[] = "Yati;Aku suka Waluh Kukus;"; char* out;

            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah DAFTAR. Gagal, masukan nama. ");
        ,err);   

        SUB_TEST(
            char in[] = "Yatu;Aku suka Waluh Kukus;"; char* out;

            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "berhasil terdaftar");
            prependError(err, "Perintah DAFTAR. Gagal, masukan kata sandi. ");
        ,err);

        SUB_TEST(
            char in[] = "Yati;;;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();            
            clearStdIO();

            assert_string_include(err, out, "Nama telah dipakai");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai. ");
        ,err);        

        SUB_TEST(
            char in[] = "Yati; Yate;password;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai, dilanjutkan nama baru. ");
        ,err);        

         SUB_TEST(
            char in[] = "Yati; Yato;;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "berhasil terdaftar");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai, dilanjutkan nama baru. ");
        ,err);        
        
        cleanup();
    , err);
    
    DEFINE_TEST("Masuk Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        createUser("Tuan Bri", "TuanHakJahad");

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "User tidak ditemukan");
            prependError(err, "Perintah MASUK. Gagal, user tidak ditemukan. ");
        ,err);

        createUser("Tuan Bri", "TuanHakJahad");

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah MASUK. Gagal, meminta nama user baru. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Periksa kembali kata sandi");
            prependError(err, "Perintah MASUK. Gagal, kata sandi salah. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();
            
            assert_string_include(err, out, "Periksa kembali kata sandi");
            prependError(err, "Perintah MASUK. Gagal, kata sandi salah. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Anda telah berhasil masuk");
            prependError(err, "Perintah MASUK. Gagal, pengguna tidak login. ");
        ,err);

        UserId id2 = createUser("temp","");
        loggedUser = getUser(id2);

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Anda sudah masuk");
            prependError(err, "Perintah MASUK. Gagal, pengguna sudah login. ");
        ,err);   

      cleanup();
    , err);

    DEFINE_TEST("Keluar Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signOut();
            clearStdIO();

            assert_string_include(err, out, "Anda belum login");
            prependError(err, "Perintah KELUAR. Gagal, pengguna belum login. ");
        ,err);

        UserId id = createUser("temp","");
        loggedUser = getUser(id);

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signOut();
            clearStdIO();

            assert_string_include(err, out, "Anda berhasil logout");
            prependError(err, "Perintah KELUAR. Gagal, pengguna belum keluar. ");
        ,err);

      cleanup();
    , err);

    DEFINE_TEST("Tutup Program", 
        setup();
        char err[MAX_ERROR] = "\0";

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            // quit program
            clearStdIO();

            assert_string_include(err, out, "keluar dari program");
            prependError(err, "Perintah TUTUP_PROGRAM. Gagal, program tidak berhenti. ");
        ,err);

      cleanup();
    , err);
}