#ifndef USER_H
#define USER_H

#include "ADT/boolean.h"
#define MAX_USER 20

/* Maximum string length */
#define MAX_NAME 30
#define MAX_PASS 15
#define MAX_BIO 136
#define MAX_PHONE 100
#define MAX_WETON 100
#define MAX_COLOR 26
#define MAX_PICTURE 26
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
    char picturecolor[MAX_COLOR];
    char picture[MAX_PICTURE];
    UserType type; /* Account type */
} User;

#define USERNAME(x) (x).username
#define PASSWORD(x) (x).password
#define BIO(x) (x).bio
#define PHONE(x) (x).phone
#define TYPE(x) (x).type
#define PICTURECOLOR(x) (x).picturecolor
#define PICTURE(x) (x).picture

/* All user pointer saved here, initialized in setup function */
extern User* users[MAX_USER];
extern User* loggedUser;
extern int userCount;

/* Create new user, and return it's id */
UserId createUser(char* name, char* pass);

/* Delete user by id */
void deleteUser(UserId id);

/* Get user by id */
User* getUser(UserId id);
User* getUserByName(char* name);

void displayUserIO(UserId id);

UserId signUp();
UserId signIn();
void signOut();

void displayProfilIO(UserId id);
void gantiProfilIO();
void lihatProfilIO(char* name);
void aturJenisAkunIO();
void ubahFotoProfilIO();
#endif