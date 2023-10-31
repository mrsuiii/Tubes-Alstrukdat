#ifndef TWEET_H
#define TWEET_H

#define MAX_TWEET 280

typedef int TweetId;

#include "user.h"
#include "reply.h"
#include "thread.h"

typedef struct tweet{
    TweetId id;
    char tweet[MAX_TWEET];
    int like;
    UserId author;
    //DATETIME datetime;
    ThreadPointer firstThread; // firstThread = kicauan sambungan pertama
    int threadCount;
    Replies replies;
    int replyCount;
} Tweet;

typedef struct{
    Tweet *buffer;
    int nEff; 
    int capacity ; 
}Tweets;

// #include "relation.h"
// #include "thread.h"
// #include "ADT/datetime.h"



extern Tweets tweets;

TweetId createTweet(char* content, UserId author);
Tweet* getTweet(TweetId id);

void createTweetIO();
void changeTweetIO(TweetId id) ; 
void likeTweetIO(TweetId id) ; 
void displayTweetIO(TweetId id) ; 
void displayAllTweetIO() ; 
#endif