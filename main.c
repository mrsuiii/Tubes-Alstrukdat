#include <stdio.h>
#include "lib/get_string.h"
#include "lib/config.h"
#include "lib/routine.h"
#include "lib/user.h"
#include "lib/relation.h"
#include "lib/tweet.h"
#include "lib/string.h"

int main(){
    setup();

    startReadFile("./config/pengguna.config");
    configToUser();
    configToRelation();

    startReadFile("./config/kicauan.config");
    configToTweet();

    while(true){
        printf(">");
        char command[100];
        get_word(command, 100);

        if(string_equal(command, "TUTUP_PROGRAM;")){
            break;
        } 
        
        else if(string_equal(command, "DAFTAR;")){
            signUp();
        } 
        else if(string_equal(command, "MASUK;")){
            signIn();
        } 
        else if(string_equal(command, "KELUAR;")){
            signOut();
        } 
        
        else {
            printf("Command \"%s\" tidak diketahui\n", command);
        }
    }

    cleanup();
}