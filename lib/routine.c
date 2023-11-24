#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "user.h"
#include "relation.h"
#include "draft.h"
#include "tagar.h"

void setup(){
    setupHastag(hashmapHastag); 
}

void cleanup(){
    userCleanupRoutine();
    relationCleanUpRoutine();
    draftCleanUpRoutine();
    hastagCleanupRoutine();
}