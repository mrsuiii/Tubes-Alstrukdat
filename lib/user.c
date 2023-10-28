#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "string.h"
#include "get_string.h"

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

void displayUser(UserId id){
    User* user = getUser(id);
    printf("| Nama: %s\n", user->name);
    printf("| Bio Akun: %s\n", user->bio);
    printf("| No HP: %s\n", user->phone);
    printf("| Weton: %s\n", user->weton);
}

UserId signUp(){
    if(loggedUser){
        printf("Anda telah login\n");
        return -1;
    }

    if(!isFull()){
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