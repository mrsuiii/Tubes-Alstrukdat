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

UserId createUser(){
    int newId = getEmptyId();
    if(newId == -1) return -1;

    User* user = malloc(sizeof(User));
    if(!user) return -1;

    user->id = newId;
    string_copy("", user->username, 1);
    string_copy("", user->bio, 1);
    string_copy("", user->password, 1);
    string_copy("", user->phone, 1);
    string_copy("", user->weton, 1);

    users[newId] = user;
    return newId;
}

User* getUser(UserId id){
    return users[id];
}

void displayUser(UserId id){
    User* user = getUser(id);
    printf("| Nama: %s\n", user->username);
    printf("| Bio Akun: %s\n", user->bio);
    printf("| No HP: %s\n", user->phone);
    printf("| Weton: %s\n", user->weton);
}

boolean checkAvailability(char* username){
    for(int i = 0; i < MAX_USER; ++i){
        User* user = getUser(i);
        if(!user) continue;
        if(string_compare(username, user->username) == 0) return false;
    }
    return true;
}

UserId signUp(){
    UserId userId = createUser();
    if(userId == -1){
        printf("User telah penuh");
        return userId;
    }

    User* user = getUser(userId);

    do{
        printf("Masukkan nama: \n");
        get_string(user->username, MAX_USERNAME);
    } while(checkAvailability(user->username));

    printf("Masukkan kata sandi: \n");
    get_string(user->password, MAX_PASSWORD);

    return userId;
}

// TODO: Clear relation after delete
void deleteUser(UserId id){
    free(users[id]);
    users[id] = NULL;
}