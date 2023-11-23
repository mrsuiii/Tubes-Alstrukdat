#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "user.h"
#include "relation.h"
#include "draft.h"
#include "tagar.h"

void setup(){

    /* User */
    for(int i = 0; i < MAX_USER; ++i) users[i] = NULL;
    loggedUser = NULL;
    userCount = 0;

    createHastag();

}

void cleanup(){
    userCleanupRoutine();
    relationCleanUpRoutine();
    draftCleanUpRoutine();
}