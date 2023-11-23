#ifndef TAGAR_H
#define TAGAR_H

#include "user.h"
#include "tweet.h"

#define MAX_TAGAR 300
#define MARK -9999
#define CAPACITY 1e9 + 7

typedef struct HashmapValue* Address;
typedef struct HashmapValue{
    TweetId id;
    char key[MAX_TAGAR];
    Address next;
} HashmapValue;

typedef struct HashMap {
    int size;
    HashmapValue** tagar;
} HashMap;

extern HashMap hashmapHastag;

HashMap* createHastag();
int hash(char* hastag);
void insertHastag(char* key, TweetId id);
void displayHastag(char* hastag);
#endif