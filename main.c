#include <stdio.h>
#include "lib/routine.h"
#include "lib/user.h"
#include "lib/get_string.h"

int main(){
    setup();

    UserId id = signUp();

    displayUser(0);

    cleanup();
}