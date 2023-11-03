#ifndef TAGAR_H
#define TAGAR_H

#include "user.h"
#include "tweet.h"

#define MAX_TAGAR 300
#define MARK -9999
#define CAPACITY 10000000

typedef struct HashmapValue{
    TweetId id;
    char key[MAX_TAGAR];
    struct HashmapValue* next;
} HashmapValue;

typedef struct HashMap {
    int size;
    HashmapValue** tagar;
} HashMap;

extern HashMap hashmapHastag;

HashMap* createHastag();
int hash(char* hastag);
void insertHastag(HashMap* map, int key, TweetId id);
#endif