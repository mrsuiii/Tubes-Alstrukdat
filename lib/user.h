#ifndef USER_H
#define USER_H

#include "ADT/boolean.h"

#define MAX_USER 20

/* Maximum string length */
#define MAX_NAME 30
#define MAX_PASS 15
#define MAX_BIO 135
#define MAX_PHONE 10
#define MAX_WETON 10

/* Account type */
#define PUBLIC_USER 0
#define PRIVATE_USER 1

typedef int UserId;
typedef boolean UserType;

typedef struct{
    UserId id; /* id is equal it's index in `extern users` variable */
    char name[MAX_NAME];
    char pass[MAX_PASS];
    char bio[MAX_BIO];
    char phone[MAX_PHONE];
    char weton[MAX_WETON];
    UserType type; /* Account type */
} User;

#define USERNAME(x) (x).username
#define PASSWORD(x) (x).password
#define BIO(x) (x).bio
#define PHONE(x) (x).phone
#define TYPE(x) (x).type

/* All user pointer saved here, initialized in setup function */
extern User* users[MAX_USER];
extern User* loggedUser;
extern int userCount;

/* Create new user, and return it's id */
UserId createUser();

/* Delete user by id */
void deleteUser(UserId id);

/* Get user by id */
User* getUser(UserId id);

/* Return true if user already full */
boolean isUserFull();

void displayUser(UserId id);

UserId signUp();
UserId signIn();
void signOut();

#endif