#ifndef REPLY_H
#define REPLY_H

#include "user.h"
#include "tweet.h"
#include "ADT/datetime.h"
#include "ADT/listdin.h"

#define MAX_REPLY 280

typedef int ReplyId;
extern ReplyId lastReplyID;

typedef struct{
    Reply reply;
    Subreply* next;
} Subreply;

typedef struct{
    ReplyId id;
    char reply[MAX_REPLY];
    UserID author;
    DATETIME datetime;
    Subreply* subreply;
} Reply;

ReplyId createReply(char* reply, TweetId tweetId, ReplyId ReplyId);
Reply* getReply(TweetId tweetId, ReplyId replyId);
void deleteReply(TweetId tweetId, ReplyId replyId);

#endif