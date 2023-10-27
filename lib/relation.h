#ifndef RELATION_H
#define RELATION_H

#include "ADT/matrix.h"
#include "ADT/liststatik.h"

extern Matrix relation;

void requestFriend(int idFrom, int idTo);
void acceptFriend(int idFrom, int idTo);
void declineFriend(int idFrom, int idTo);

/* Get user id(s) who requested to be a friend sorted by popularity (the amount of friend) */
ListStatik getRequest(int id);

/* Get user id(s) who is/are friend of a user */
ListStatik getFriend(int id);

#endif