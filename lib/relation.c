#include "relation.h"
#include "user.h"

char relation[MAX_USER][MAX_USER];
int relationCount[MAX_USER];

void requestFriend(UserId idFrom, UserId idTo){
    relation[idFrom][idTo] = IsRequester;
    relation[idTo][idFrom] = IsRequestee;
}

void declineFrined(UserId idFrom, UserId idTo){
    relation[idFrom][idTo] = IsNothing;
    relation[idTo][idFrom] = IsNothing;
}

void acceptFriend(UserId idFrom, UserId idTo){
    relation[idFrom][idTo] = IsFriend;
    relation[idTo][idFrom] = IsFriend;

    relationCount[idFrom] += 1;
    relationCount[idTo] += 1;
}

void removeFriend(UserId idFrom, UserId idTo){
    relation[idFrom][idTo] = IsNothing;
    relation[idTo][idFrom] = IsNothing;

    relationCount[idFrom] -= 1;
    relationCount[idTo] -= 1;
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

    return u;
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