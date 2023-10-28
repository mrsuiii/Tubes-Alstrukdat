#ifndef RELATION_H
#define RELATION_H

#include "user.h"

char relation[MAX_USER][MAX_USER];
int relationCount[MAX_USER];

/* relation[a][b], mean requester and requestee refer too a */

#define IsNothing 0
#define IsRequester 1
#define IsRequestee 2
#define IsFriend 3

void requestFriend(UserId requester, UserId requestee);
void declineFriend(UserId a, UserId b);
void acceptFriend(UserId a, UserId b);
void removeFriend(UserId a, UserId b);

/* Get user id(s) who requested to be a friend sorted by popularity (the amount of friend) */
Users getRequest(int id);
UserId getTopRequest(int id);

/* Get user id(s) who is/are friend of a user */
Users getFriend(int id);

boolean isRequestee(UserId id);
boolean isFriend(UserId a, UserId b);

void displayFriendIO();
void removeFriendIO();
void requestFriendIO();
void cancelRequestFriendIO();
void displayRequestedFriendIO();
void acceptFriendIO();

#endif