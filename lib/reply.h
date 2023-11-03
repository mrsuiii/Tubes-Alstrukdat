#ifndef REPLY_H
#define REPLY_H

#define MAX_REPLY 280

typedef int ReplyId;
typedef struct reply* ReplyPointer;
typedef struct replynode* ReplyNodePointer;
typedef ReplyNodePointer Replies;

#include "user.h"
#include "tweet.h"
// #include "ADT/datetime.h"
// #include "ADT/listdin.h"


typedef struct reply{
    ReplyId id;
    char content[MAX_REPLY];
    UserId author;
    // DATETIME datetime;
    ReplyNodePointer replies;
} Reply;

typedef struct replynode{
    struct reply reply;
    Replies* base;
    ReplyNodePointer next;
} ReplyNode;

ReplyPointer getReply(TweetId tweetId, ReplyId replyId);
ReplyNodePointer getReplyNode(TweetId tweetId, ReplyId replyId);
Replies* getReplies(TweetId tweetId, ReplyId replyId);

ReplyId createReply(char* content, UserId author, TweetId tweetId, Replies* base, ReplyPointer* result);
ReplyNodePointer* getReplies(TweetId tweetId, ReplyId replyId);
void deleteReply(ReplyNodePointer target);

void createReplyIO(TweetId tweetId, ReplyId replyId);
void displayReplyIO(TweetId tweetId);
void deleteReplyIO(TweetId tweetId, ReplyId replyId);

void replyToConfig(char* buffer);

#endif