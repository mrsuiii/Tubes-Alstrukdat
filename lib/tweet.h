#ifndef TWEET_H
#define TWEET_H

#include "user.h"
#include "reply.h"
#include "ADT/datetime.h"
#include "ADT/listdin.h"

#define MAX_TWEET 280

typedef int TweetId;
extern TweetId lastTweetID;

typedef struct{
    TweetId id;
    char tweet[MAX_TWEET];
    int like;
    UserId author;
    DATETIME datetime;
    Subreply* subreply;
    int replyCount;
} Tweet;

extern ListDin tweets;

TweetId createTweet(char* tweet);
Tweet* getTweet(TweetId id);
void deleteTweet(TweetId id);

#endif