#ifndef REPLY_H
#define REPLY_H

#define MAX_REPLY 280

typedef int ReplyId;

#include "user.h"
#include "tweet.h"
// #include "ADT/datetime.h"
// #include "ADT/listdin.h"

typedef struct reply{
    ReplyId id;
    char content[MAX_REPLY];
    UserId author;
    // DATETIME datetime;
    struct subreply* subreply;
} Reply;

typedef struct subreply{
    struct subreply* next;
    struct reply reply;
} Subreply;

ReplyId createReply(char* content, UserId author, TweetId tweetId, ReplyId replyId);
Reply* getReply(TweetId tweetId, ReplyId replyId);
void deleteReply(TweetId tweetId, ReplyId replyId);

#endif