#ifndef TWEET_H
#define TWEET_H

#include "user.h"
// #include "relation.h"
// #include "reply.h"
// #include "thread.h"
// #include "ADT/datetime.h"

#define MAX_TWEET 280

typedef int TweetId;

typedef struct{
    TweetId id;
    char tweet[MAX_TWEET];
    int like;
    UserId author;
    // DATETIME datetime;
    // Subreply* subreply;
} Tweet;

typedef struct{
    Tweet *buffer;
    int nEff; 
    int capacity ; 
}Tweets;

extern Tweets tweets;

TweetId createTweet(char* content, UserId author);
Tweet* getTweet(TweetId id);

void changeTweetIO(TweetId id) ; 
void likeTweetIO(TweetId id) ; 
void displayTweetIO(TweetId id) ; 
void displayAllTweetIO() ; 
#endif