#ifndef USER_H
#define USER_H

#include "ADT/boolean.h"

#define MAX_USER 20

/* Maximum string length */
#define MAX_USERNAME 30
#define MAX_PASSWORD 15
#define MAX_BIO 135
#define MAX_PHONE 10
#define MAX_WETON 10

/* Account type */
#define PUBLIC_USER 0
#define PRIVATE_USER 1

typedef int UserID;
typedef boolean AccountType;

typedef struct{
    UserID id; /* id is equal it's index in `extern users` variable */
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char bio[MAX_BIO];
    char phone[MAX_PHONE];
    char weton[MAX_WETON];
    AccountType type; /* Account type */
} User;

#define USERNAME(x) (x).username
#define PASSWORD(x) (x).password
#define BIO(x) (x).bio
#define PHONE(x) (x).phone
#define TYPE(x) (x).type

/* All user pointer saved here */
extern User* users[MAX_USER];
extern User* loggedUser;

/* Create new user, and return it's id */
UserID CreateUser();

/* Delete user by id */
void DeleteUser(UserID id);

/* Get user by id */
User* getUser(UserID id);

/* Count the user (using loop and check for NULL pointer) */
int getUserCount();

#endif