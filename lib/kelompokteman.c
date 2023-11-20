#include"kelompokteman.h"
#include <stdio.h>

void friendGroup(DisjointSet set,int currentUser ){
    printf("Terdapat %d orang dalam kelompok teman %c:\n",set.kelompokTeman[(set.kelompokTeman[currentUser].parent)].rank+1,getUser(currentUser));
    for(int i = 0;i<userCount; i++){
        if(i == currentUser)continue;
        else{
            if(findSet(i,set)==findSet(currentUser,set)){
                printf("%c\n",getUser(i));
            }
        }
    }
}
boolean areFriend(int a,int b , DisjointSet set){
    return findSet(a,set) ==findSet(b,set);
}

void showFriendGroup(){
    DisjointSet setFriend;
    for(int i=0;i<userCount;i++){
        makeSet(i,&setFriend);
    }
    for(int i=0;i<userCount-1;i++){
        for(int j=i+1;j<userCount;j++){
            if(isFriend(i,j))unionSets(i,j,&setFriend);
        }
    }
    friendGroup(setFriend,loggedUser->id);
}