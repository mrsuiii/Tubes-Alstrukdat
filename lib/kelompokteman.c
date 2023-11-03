#include"kelompokteman.h"
#include <stdio.h>

void friendGroup(DisjointSet* set,int currentUser ){
    printf("Terdapat %d orang dalam kelompok teman %c:\n",getUser(currentUser));
    for(int i = 0;i<userCount; i++){
        if(i == currentUser)continue;
        else{
            if(findSet(i,*set)==findSet(currentUser,*set)){
                printf("%c\n",getUser(i));
            }
        }
    }
}
boolean areFriend(int a,int b , DisjointSet set){
    return findSet(a,set) ==findSet(b,set);
}
