#include <stdio.h>
#include "lib/get_string.h"
#include "lib/config.h"
#include "lib/routine.h"
#include "lib/user.h"
#include "lib/relation.h"
#include "lib/tweet.h"
#include "lib/string.h"
#include "lib/draft.h"
#include "lib/thread.h"

int main(){
    setup();

    startReadFile("./config/pengguna.config");
    configToUser();
    configToRelation();

    startReadFile("./config/kicauan.config");
    configToTweet();

    while(true){
        printf("> ");

        int argv = 0;
        char argc[4][100];
        currentChar = '\0';
        while(currentChar != GET_STRING_MARK){
            get_word(argc[argv], 100);
            argv += 1;
            if(argv >= 4) continue;
        }

        if(argv == 1 && string_equal(argc[0], "TUTUP_PROGRAM")){
            break;
        } 

        // User
        else if(argv == 1 && string_equal(argc[0], "DAFTAR")) signUp();
        else if(argv == 1 && string_equal(argc[0], "MASUK")) signIn();
        else if(argv == 1 && string_equal(argc[0], "KELUAR")) signOut();

        // Profile
        else if(argv == 1 && string_equal(argc[0], "GANTI PROFIL")) changeProfileIO();
        else if(argv == 2 && string_equal(argc[0], "LIHAT_PROFIL")) displayProfileIO(argc[1]);
        else if(argv == 1 && string_equal(argc[0], "ATUR_JENIS_AKUN")) changeAccountTypeIO();
        else if(argv == 1 && string_equal(argc[0], "UBAH_FOTO_PROFIIL")) changePhotoProfileIO();

        // Relation
        else if(argv == 1 && string_equal(argc[0], "TAMBAH_TEMAN")) requestFriendIO();
        else if(argv == 1 && string_equal(argc[0], "DAFTAR_TAMBAH_TEMAN")) displayRequestedFriendIO();
        else if(argv == 1 && string_equal(argc[0], "SETUJUI_PERTEMANAN")) acceptFriendIO();

        // Tweet
        else if(argv == 1 && string_equal(argc[0], "KICAU")) createTweetIO();
        else if(argv == 1 && string_equal(argc[0], "KICAUAN")) displayAllTweetIO();
        else if(argv == 2 && string_equal(argc[0], "SUKA_KICAUAN")) likeTweetIO(argc[1]);
        else if(argv == 2 && string_equal(argc[0], "UBAH_KICAUAN")) editTweetIO(argc[1]);

        // Reply
        else if(argv == 3 && string_equal(argc[0], "BALAS")) createReplyIO(argc[1], argc[2]);
        else if(argv == 2 && string_equal(argc[0], "BALASAN")) displayReplyIO(argc[1]);
        else if(argv == 3 && string_equal(argc[0], "HAPUS_BALASAN")) deleteReplyIO(argc[1], argc[2]);

        // Draft
        else if(argv == 1 && string_equal(argc[0], "BUAT_DRAF")) createDraftIO();
        else if(argv == 1 && string_equal(argc[0], "LIHAT_DRAF")) displayDraftIO();

        // Thread
        else if(argv == 2 && string_equal(argc[0], "UTAS")) makeMainThreadIO(argc[1]);
        else if(argv == 3 && string_equal(argc[0], "SAMBUNG_UTAS")) continueThreadAtIO(argc[1], argc[2]);
        else if(argv == 3 && string_equal(argc[0], "HAPUS_TAS")) deleteThreadAtIO(argc[1], argc[2]);
        else if(argv == 2 && string_equal(argc[0], "CETAK_UTAS")) displayThreadSeqIO(argc[1]);

        else {
            printf("Command \"%s\" dengan %d argumen tidak diketahui\n", argc[0], argv);
        }
        
    }

    cleanup();
}