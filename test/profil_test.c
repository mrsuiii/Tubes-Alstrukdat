#include "_test_.h"
#include "../lib/user.h"
#include "../lib/ADT/boolean.h"
#include "../lib/routine.h"

int main(){
    DEFINE_TEST("Ganti Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, menampilkan profil. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "Masukkan No HP");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah bio akun. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "HP tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, No HP tidak valid. ");
        ,err);
        
        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "Masukkan Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah No HP. ");
        ,err);
        
        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "Weton anda tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, weton tidak valid. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            gantiProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "berhasil diperbarui");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah weton dengan string kosong. ");
        ,err);
        
        cleanup();
    , err);

    DEFINE_TEST("Lihat Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id1 = createUser("TuanHak","");
        UserId id2 = createUser("TuanBri","");
        UserId id3 = createUser("TuanPrim","");
        loggedUser = getUser(id1);
        getUser(id2)->type = PUBLIC_USER;
        getUser(id3)->type = PRIVATE_USER;

        SUB_TEST(    
            char in[] = ""; char* out;
            interceptStdIO(in, &out);
            displayProfilIO(id2);
            clearStdIO();
        
            assert_string_include(err, out, "Nama");
            prependError(err, "Perintah LIHAT_PROFIL. Gagal, menampilkan profil public. ");
        ,err);

        SUB_TEST(    
            char in[] = ""; char* out;
            interceptStdIO(in, &out);
            displayProfilIO(id3);
            clearStdIO();
        
            assert_string_include(err, out, "diprivat nih");
            prependError(err, "Perintah LIHAT_PROFIL. Gagal, menampilkan profil privat. ");
        ,err);
        
        cleanup();
    , err);

    DEFINE_TEST("Lihat Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);
        getUser(id)->type = PUBLIC_USER;

        SUB_TEST(    
            char in[] = "TIDAK;"; char* out;
            interceptStdIO(in, &out);
            aturJenisAkunIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Publik");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, menampilkan jenis akun. ");
        ,err);

        SUB_TEST(    
            char in[] = "YA;"; char* out;
            interceptStdIO(in, &out);
            aturJenisAkunIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Privat");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, mengubah jenis akun. ");
        ,err);
        
        getUser(id)->type = PRIVATE_USER;

        SUB_TEST(    
            char in[] = "TIDAK;"; char* out;
            interceptStdIO(in, &out);
            aturJenisAkunIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Privat");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, menampilkan jenis akun. ");
        ,err);

        cleanup();
    , err);

    DEFINE_TEST("Ubah Foto Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);
        getUser(id)->type = PUBLIC_USER;

        SUB_TEST(    
            char in[] = "R * R * R * R * R *\nR * G @ B * G @ R *\nR * G @ G @ G @ R *\nR * G @ B * G @ R *\nR * R * R * R * R *;"; 
            char* out;
            interceptStdIO(in, &out);
            ubahFotoProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "Foto Profil");
            prependError(err, "Perintah UBAH_FOTO_PROFIL. Gagal, menampilkan foto saat ini. ");
        ,err);

        SUB_TEST(    
            char in[] = "YA;"; char* out;
            interceptStdIO(in, &out);
            ubahFotoProfilIO();
            clearStdIO();
        
            assert_string_include(err, out, "berhasil diganti");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, mengubah foto profil. ");
        ,err);
        
        getUser(id)->type = PRIVATE_USER;

        SUB_TEST(    
            char in[] = "TIDAK;"; char* out;
            interceptStdIO(in, &out);
            aturJenisAkunIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Privat");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, menampilkan jenis akun. ");
        ,err);

        cleanup();
    , err);
}