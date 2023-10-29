#ifndef REPLY_H
#define REPLY_H

#define MAX_REPLY 280

typedef int ReplyId;

#include "user.h"
#include "tweet.h"
// #include "ADT/datetime.h"
// #include "ADT/listdin.h"

typedef struct replynode* ReplyNodePointer;

typedef struct reply{
    ReplyId id;
    char content[MAX_REPLY];
    UserId author;
    // DATETIME datetime;
    ReplyNodePointer subreply;
} Reply;

typedef struct replynode{
    struct reply reply;
    ReplyNodePointer prev;
    ReplyNodePointer next;
} ReplyNode;

ReplyId createReply(char* content, UserId author, TweetId tweetId, ReplyNodePointer* target);
ReplyNodePointer* getStartTarget(TweetId tweetId, ReplyId replyId);
ReplyNodePointer* getReplyNode_DP(TweetId tweetId, ReplyId replyId);

void displayReplyIO(TweetId tweetId);

#endif