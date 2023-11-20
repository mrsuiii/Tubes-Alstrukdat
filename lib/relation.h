#ifndef RELATION_H
#define RELATION_H

#include "user.h"

#define IsNothing 0
#define IsFriend 1

typedef struct requestqueue* RequestQueuePointer;
typedef struct requestqueue{
    int friendCount;
    UserId userId;
    RequestQueuePointer next;
} RequestQueue;

void requestFriend(UserId requester, UserId requestee);
void addFriend(UserId a, UserId b);
void removeFriend(UserId a, UserId b);
boolean isFriend(UserId a, UserId b);

void displayFriendIO();
void removeFriendIO();
void requestFriendIO();
void displayRequestedFriendIO();
void acceptFriendIO();

void relationCleanUpRoutine();

#endif