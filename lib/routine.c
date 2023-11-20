#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "user.h"
#include "relation.h"
#include "draft.h"

void setup(){
}

void cleanup(){
    relationCleanUpRoutine();
    draftCleanUpRoutine();
}