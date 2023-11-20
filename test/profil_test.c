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
        char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
        interceptStdIO(in, &out);
        gantiProfilIO();

        SUB_TEST(    
            assert_string_include(err, out, "Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, menampilkan profil. ");
        ,err);

        SUB_TEST(    
            assert_string_include(err, out, "Masukkan No HP");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah bio akun. ");
        ,err);

        SUB_TEST(    

            assert_string_include(err, out, "HP tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, No HP tidak valid. ");
        ,err);
        
        SUB_TEST(    
            assert_string_include(err, out, "Masukkan Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah No HP. ");
        ,err);
        
        SUB_TEST(    
            assert_string_include(err, out, "Weton anda tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, weton tidak valid. ");
        ,err);

        SUB_TEST(    
            assert_string_include(err, out, "berhasil diperbarui");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah weton. ");
        ,err);
        
        clearStdIO();
        
        cleanup();
    , err);
}