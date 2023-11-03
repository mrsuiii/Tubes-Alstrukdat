#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "string.h"
#include "get_string.h"
#include "pcolor.h"

User* users[MAX_USER];
User* loggedUser;
int userCount;

int getEmptyId(){
    for(int i = 0; i < MAX_USER; ++i)
        if(users[i] == NULL)
            return i;
    return -1;
}

int isFull(){
    return getEmptyId() == -1;
}

UserId createUser(char* name, char* pass){
    int newId = getEmptyId();
    if(newId == -1) return -1;

    User* user = malloc(sizeof(User));
    if(!user) return -1;

    user->id = newId;
    string_copy(name, user->name, MAX_NAME);
    string_copy(pass, user->pass, MAX_PASS);
    string_copy("", user->bio, MAX_BIO);
    string_copy("", user->phone, MAX_PHONE);
    string_copy("", user->weton, MAX_WETON);
    users[newId] = user;

    string_copy("RRRRRRRRRRRRRRRRRRRRRRRRR", user->picturecolor,MAX_COLOR);
    string_copy("*************************", user->picture,MAX_PICTURE);
    return newId;
}

User* getUser(UserId id){
    return users[id];
}

User* getUserByName(char* name){
    for(int i = 0; i < MAX_USER; ++i){
        User* user = getUser(i);
        if(!user) continue;
        if(string_compare(name, user->name) == 0) return user;
    }
    return NULL;
}

void displayUserIO(UserId id){
    User* user = getUser(id);
    printf("| Nama: %s\n", user->name);
    printf("| Bio Akun: %s\n", user->bio);
    printf("| No HP: %s\n", user->phone);
    printf("| Weton: %s\n", user->weton);
}

boolean checkPhoneValid(char* phone){
    int i = 0;
    while (phone[i] != '\0'){
        if (phone[i] < '0' || phone[i] > '9'){
            return false;
        }
        i++;
    }

    return true;
}

boolean checkWetonValid(char* weton){
    int i = 0;
    char pahingValid[MAX_WETON] = "pahing", kliwonValid[MAX_WETON] = "kliwon";
    char wageValid[MAX_WETON] = "wage", ponValid[MAX_WETON] = "pon";
    char legiValid[MAX_WETON] = "legi";

    if (weton[0] == '\0'){
        return true;
    }

    while (weton[i] != '\0'){
        if (weton[i] < 'a'){
            weton[i] += 32;
        }
        i++;
    }

    if (
        string_compare(pahingValid,weton) == 0 ||
        string_compare(kliwonValid,weton) == 0 ||
        string_compare(wageValid,weton) == 0 ||
        string_compare(ponValid,weton) == 0 ||
        string_compare(legiValid,weton) == 0
    ){
        return true;
    } else {
        return false;
    }
}

UserId signUp(){
    if(loggedUser){
        printf("Anda telah login\n");
        return -1;
    }

    if(isFull()){
        printf("User telah penuh\n");
        return -1;
    }

    char tmpName[MAX_NAME];
    do{
        printf("Masukkan nama: \n");
        get_string(tmpName, MAX_NAME);
    } while(
        (getUserByName(tmpName) != NULL) && 
        (printf("Nama telah dipakai\n") || true)
    );

    char tmpPass[MAX_PASS];
    printf("Masukkan kata sandi: \n");
    get_string(tmpPass, MAX_PASS);

    return createUser(tmpName, tmpPass);
}

UserId signIn(){
    if(loggedUser){
        printf("Anda telah login\n");
        return -1;
    }

    char tmpName[MAX_NAME];
    printf("Masukkan nama: \n");
    get_string(tmpName, MAX_NAME);
    User* user = getUserByName(tmpName);

    if(!user){
        printf("User tidak ditemukan\n");
        return -1;
    }

    char tmpPass[MAX_PASS];
    printf("Masukkan pass: \n");
    get_string(tmpPass, MAX_PASS);

    if(string_compare(tmpPass, user->pass) != 0){
        printf("Password anda salah\n");
        return -1;
    }

    loggedUser = user;
    return user->id;
}

void signOut(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    loggedUser = NULL;
}

// TODO: Clear relation after delete
void deleteUser(UserId id){
    free(users[id]);
    users[id] = NULL;
}

void displayProfilIO(UserId id){
    int i;
    User* user = getUser(id);
    for (i = 0; i < MAX_COLOR; i++){
        if ((i + 1) % 5 == 1 && i != 0){
            printf("\n");
        }
        // printf("%d",i);
        if (user->picturecolor[i] == 'R'){
            print_red(user->picture[i]);
        } else if (user->picturecolor[i] == 'G'){
            print_green(user->picture[i]);
        } else if (user->picturecolor[i] == 'B'){
            print_blue(user->picture[i]);
        }
    }
    printf("\n");
}
void gantiProfilIO(){
    char tmpBio[MAX_BIO], tmpPhone[MAX_PHONE],tmpWeton[MAX_WETON];
    User* user = getUser(loggedUser->id);

    displayUserIO(user->id);
    printf("Masukkan Bio Akun:\n");
    get_string(tmpBio,MAX_BIO);
    if (string_length(tmpBio) != 0){
        string_copy(tmpBio,user->bio,MAX_BIO);
    }

    do {    
        printf("Masukkan No HP:\n");
        get_string(tmpPhone,MAX_PHONE);

        if (string_length(tmpPhone) != 0){
            if (!checkPhoneValid(tmpPhone)){
                printf("No HP tidak valid. Masukkan lagi yuk!\n");
            } else {
                string_copy(tmpPhone,user->phone,MAX_PHONE);
            }
        }
    } while(!checkPhoneValid(tmpPhone));
    
    do {
        printf("Masukkan Weton:\n");
        get_string(tmpWeton,MAX_WETON);
        
        if (string_length(tmpWeton) != 0){
            if (!checkWetonValid(tmpWeton)){
                // printf("%s",tmpWeton);
                printf("Weton anda tidak valid.\n");
            } else {
                tmpWeton[0] -= 32;
                string_copy(tmpWeton,user->weton,MAX_WETON);
                tmpWeton[0] += 32;
            }
        }
    } while (!checkWetonValid(tmpWeton));

}

void lihatProfilIO(char* name){
    User* user = getUserByName(name);
    if (user->type == PUBLIC_USER){
        displayUserIO(user->id);
        printf("\n");
        printf("Foto profil akun %s\n",user->name);
        displayProfilIO(user->id);
    } else {
        printf("Wah, akun Tuan Prim diprivat nih. ");
        printf("Ikuti dulu yuk untuk bisa melihat profil Tuan Prim!\n");
    }

}

void aturJenisAkunIO(){
    char input[MAX_BIO];
    User* user = getUser(loggedUser->id);
    if (user->type == PUBLIC_USER){
        printf("Saat ini, akun Anda adalah akun Publik.\n"); 
        printf("Ingin mengubah ke akun Privat?\n");
        do {
            printf("(YA/TIDAK) ");
            get_string(input,MAX_BIO);
            if (string_compare(input,"YA") == 0){
                user->type = PRIVATE_USER;
                printf("Akun anda sudah diubah menjadi akun Privat.\n");
            } else if (string_compare(input,"TIDAK") != 0 && string_compare(input,"YA") != 0){
                printf("Input Salah!\n");
            }
        } while (string_compare(input,"YA") != 0 && string_compare(input,"TIDAK") != 0);
    } else if (user->type == PRIVATE_USER){
        printf("Saat ini, akun Anda adalah akun Private.\n"); 
        printf("Ingin mengubah ke akun Public?\n");
        do {
            printf("(YA/TIDAK) ");
            get_string(input,MAX_BIO);
            if (string_compare(input,"YA") == 0){
                user->type = PUBLIC_USER;
                printf("Akun anda sudah diubah menjadi akun Public.\n");
            } else if (string_compare(input,"TIDAK") != 0 && string_compare(input,"YA") != 0){
                printf("Input Salah!\n");
            }
        } while (string_compare(input,"YA") != 0 && string_compare(input,"TIDAK") != 0);
    }
}

void ubahFotoProfilIO(){
    char inputcolor[MAX_COLOR], inputpicture[MAX_PICTURE];
    User* user = getUser(loggedUser->id);
    printf("Foto profil Anda saat ini adalah\n");
    displayProfilIO(user->id);
    printf("\nMasukkan foto profil yang baru\n");
    get_string_foto_profil(inputcolor,inputpicture,MAX_PICTURE);

    string_copy(inputcolor,user->picturecolor,MAX_COLOR);
    string_copy(inputpicture,user->picture,MAX_PICTURE);

    printf("\nFoto profil anda sudah berhasil diganti!\n");
}