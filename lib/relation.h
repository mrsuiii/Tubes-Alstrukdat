#ifndef RELATION_H
#define RELATION_H

#include "user.h"

char relation[MAX_USER][MAX_USER];
int relationCount[MAX_USER];

/* idFrom -> idTo, requester and requestee refer too idFrom */

#define IsNothing 0
#define IsRequester 1
#define IsRequestee 2
#define IsFriend 3

void requestFriend(UserId idFrom, UserId idTo);
void declineFriend(UserId idFrom, UserId idTo);
void acceptFriend(UserId idFrom, UserId idTo);
void removeFriend(UserId idFrom, UserId idTo);

/* Get user id(s) who requested to be a friend sorted by popularity (the amount of friend) */
Users getRequest(int id);

/* Get user id(s) who is/are friend of a user */
Users getFriend(int id);

boolean isFriend(UserId a, UserId b);

#endif