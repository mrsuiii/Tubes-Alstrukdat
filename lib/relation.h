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

static char relation[MAX_USER][MAX_USER];
static int relationCount[MAX_USER];
static RequestQueuePointer requestQueue[MAX_USER];

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
void relationToConfig();

#endif