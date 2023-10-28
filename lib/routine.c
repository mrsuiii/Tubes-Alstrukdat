#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "user.h"

void setup(){
    for(int i = 0; i < MAX_USER; ++i) users[i] = NULL;
    loggedUser = NULL;
    userCount = 0;
}

void cleanup(){
    for(int i = 0; i < MAX_USER; ++i) free(users[i]);
}