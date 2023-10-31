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

UserId getTopRequest(int id){
    UserId top = -1;
    for(int i = 0; i < MAX_USER; ++i){
        if(relation[id][i] == IsRequestee){
            if(top == -1 || relationCount[i] > relationCount[top]){
                top = i;
            }
        }
    }
    return top;
}

Users getFriend(int id){
    Users u;
    getUsers(&u, id, IsFriend);
    sortByFriend(&u);
    return u;
}

boolean isRequestee(UserId id){
    for(int i = 0; i < MAX_USER; ++i){
        if(relation[id][i] == IsRequestee) return true;
    }
    return false;
}

boolean isFriend(UserId a, UserId b){
    return relation[a][b];
}

void displayFriendIO(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

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
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

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

    // TODO: Generalize prompt
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

void requestFriendIO(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    if(isRequestee(loggedUser->id)){
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n");
        return;
    }

    char tmpName[MAX_NAME];
    printf("Masukkan nama pengguna:\n");
    get_string(tmpName, MAX_NAME);
    User* user = getUserByName(tmpName);
    if(!user){
        printf("Pengguna bernama %s tidak ditemukan\n", tmpName);
        return;
    }

    if(isFriend(loggedUser->id, user->id)){
        printf("Anda sudah berteman\n");
        return;
    }

    requestFriend(loggedUser->id, user->id);
    printf("Permintaan pertemanan kepada %s telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n", tmpName);
};

void cancelRequestFriendIO(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    char tmpName[MAX_NAME];
    printf("Masukkan nama pengguna:\n");
    get_string(tmpName, MAX_NAME);
    User* user = getUserByName(tmpName);
    if(!user){
        printf("Pengguna bernama %s tidak ditemukan\n", tmpName);
        return;
    }

    if(relation[loggedUser->id][user->id] != IsRequester){
        printf("Anda belum mengirimkan permintaan pertemanan kepada %s\n", user->name);
        return;
    }

    declineFriend(loggedUser->id, user->id);
    printf("Permintaan pertemanan kepada %s telah dibatalkan\n", user->name);
}

void displayRequestedFriendIO(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    Users u = getRequest(loggedUser->id);
    if(u.size == 0){
        printf("Tidak ada permintaan pertemanan untuk Anda\n");
        return;
    }

    printf("Terdapat %d permintaan pertemanan untuk Anda\n\n", u.size);

    for(int i = u.size - 1; i >= 0; --i){
        printf("| %s\n", getUser(u.ids[i])->name);
        printf("| Jumlah teman: %d\n\n", relationCount[u.ids[i]]);
    }
}

void acceptFriendIO(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    UserId id = getTopRequest(loggedUser->id);
    if(id == -1){
        printf("Tidak ada permintaan pertemanan untuk Anda\n");
        return;
    }

    User* user = getUser(id);
    printf("Permintaan pertemanan teratas dari %s\n", user->name);
    printf("| %s\n", user->name);
    printf("| Jumlah teman: %d\n\n", relationCount[id]);

    int promptValue = -1;
    char tmpPrompt[10];
    do{
        printf("Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ");
        get_string(tmpPrompt, 10);

        if(string_compare("YA", tmpPrompt) == 0) promptValue = 1;
        else if(string_compare("TIDAK", tmpPrompt) == 0) promptValue = 0;
    } while(
        (promptValue == -1) &&
        (printf("Input tidak valid\n") || true)
    );

    if(promptValue){
        acceptFriend(loggedUser->id, user->id);
        printf("Permintaan pertemanan dari Bob telah disetujui. Selamat! Anda telah berteman dengan Bob.\n");
    } else {
        declineFriend(loggedUser->id, user->id);
        printf("Permintaan pertemanan dari Bob telah ditolak.\n");
    }
}