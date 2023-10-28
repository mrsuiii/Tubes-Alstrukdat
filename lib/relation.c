#include <stdio.h>
#include "string.h"
#include "get_string.h"
#include "relation.h"
#include "user.h"

char relation[MAX_USER][MAX_USER];
int relationCount[MAX_USER];

void requestFriend(UserId requester, UserId requestee){
    relation[requester][requestee] = IsRequester;
    relation[requestee][requester] = IsRequestee;
}

void declineFriend(UserId a, UserId b){
    relation[a][b] = IsNothing;
    relation[b][a] = IsNothing;
}

void acceptFriend(UserId a, UserId b){
    relation[a][b] = IsFriend;
    relation[b][a] = IsFriend;

    relationCount[a] += 1;
    relationCount[b] += 1;
}

void removeFriend(UserId a, UserId b){
    declineFriend(a, b);

    relationCount[a] -= 1;
    relationCount[b] -= 1;
}

/* Sort users by ascending order of friends count */
void sortByFriend(Users* users){
    int size = (*users).size;
    for(int i = 0; i < size; ++i){
        for(int j = i; j < size - 1; ++j){
            int a = relationCount[(users->ids)[j]];
            int b = relationCount[(users->ids)[j + 1]];
            if(a > b){
                int p = (users->ids)[j];
                int q = (users->ids)[j + 1];
                (users->ids)[j] = q;
                (users->ids)[j + 1] = p;
            }
        }
    }
}

void getUsers(Users* u, int id, int req){
    u->size = 0;

    for(int i = 0; i < MAX_USER; ++i){
        if(relation[id][i] == req){
            u->ids[u->size] = i;
            u->size += 1;
        }
    }
}

Users getRequest(int id){
    Users u;
    getUsers(&u, id, IsRequestee);
    sortByFriend(&u);
    return u;
}

Users getFriend(int id){
    Users u;
    getUsers(&u, id, IsFriend);
    sortByFriend(&u);
    return u;
}

boolean isFriend(UserId a, UserId b){
    return relation[a][b];
}

void displayFriendIO(){
    int count = relationCount[loggedUser->id];

    if(count == 0){
        printf("%s belum mempunya teman\n", loggedUser->name);
        return;
    }

    Users u = getFriend(loggedUser->id);
    printf("%s memiliki %d teman\n", loggedUser->name, count);
    printf("Dafter teman %s\n", loggedUser->name);
    for(int i = 0; i < count; ++i){
        printf("| %s\n", getUser(u.ids[i])->name);
    }
}

void removeFriendIO(){
    char tmpName[MAX_NAME];
    printf("Masukkan nama pengguna:\n");
    get_string(tmpName, MAX_NAME);
    User* friend = getUserByName(tmpName);
    if(!friend){
        printf("User %s tidak ditemukan\n", tmpName);
        return;
    }

    if(!isFriend(friend->id, loggedUser->id)){
        printf("%s bukan teman Anda\n", tmpName);
        return;
    }

    // TODO: Generalize make prompt
    int promptValue = -1;
    char tmpPrompt[10];
    do{
        printf("Apakah anda yakin ingin menghapus Bob dari daftar teman anda? (YA/TIDAK) ");
        get_string(tmpPrompt, 10);

        if(string_compare("YA", tmpPrompt) == 0) promptValue = 1;
        else if(string_compare("TIDAK", tmpPrompt) == 0) promptValue = 0;
    } while(
        (promptValue == -1) &&
        (printf("Input tidak valid\n") || true)
    );

    if(promptValue){
        removeFriend(friend->id, loggedUser->id);
        printf("%s berhasil dihapus dari daftar teman Anda\n", friend->name);
    } else {
        printf("Penghapusan teman dibatalkan\n");
    }
}