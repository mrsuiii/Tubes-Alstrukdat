#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"

void insertLastSubreply(ReplyNodePointer* target, ReplyNodePointer value){
    if(*target == NULL){
        *target = value;
        value->prev = NULL;
    } else {
        while((*target)->next != NULL) *target = (*target)->next;
        (*target)->next = value;
        value->prev = *target;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, ReplyNodePointer* startTarget){
    ReplyNodePointer newSubreply = malloc(sizeof(ReplyNode));
    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newSubreply->reply);
    tweet->replyCount++;

    reply->id = tweet->replyCount;
    string_copy(content, (newSubreply->reply).content, MAX_REPLY);
    reply->author = author;
    // TODO: Datetime

    if(startTarget == NULL) return -1;
    insertLastSubreply(startTarget, newSubreply);

    return reply->id;
}

ReplyNodePointer* getReplyNodeRecur(ReplyNodePointer* start, ReplyId target){
    if(*start == NULL) return NULL;
    if((*start)->reply.id == target) return start;

    ReplyNodePointer* curr = start;
    while(*curr != NULL){
        ReplyNodePointer* r = getReplyNodeRecur(&((*curr)->reply.subreply), target);
        if(r) return r;
        curr = &((*curr)->next);
    }
    return NULL;
}

ReplyNodePointer* getReplyNode_DP(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    return getReplyNodeRecur(&(tweet->subreply), replyId);
}

ReplyNodePointer* getStartTarget(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    if(replyId == -1) return &(tweet->subreply);

    ReplyNodePointer* parent = getReplyNode_DP(tweetId, replyId);
    if(parent == NULL) return NULL;

    return &((*parent)->reply.subreply);
}

void displayReplyRecurIO(ReplyNodePointer start, int tab){
    ReplyNodePointer curr = start;
    while (curr != NULL){
        Reply reply = curr->reply;
        printf("%d %s\n", tab, reply.content);
        displayReplyRecurIO(reply.subreply, tab + 1);
        curr = curr->next;
    }
}

void displayReplyIO(TweetId tweetId){
    displayReplyRecurIO(getTweet(tweetId)->subreply, 0);
}