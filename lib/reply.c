#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"

void insertReply(SubreplyPointer* target, SubreplyPointer value){
    if(*target == NULL){
        *target = value;
    } else {
        while((*target)->next != NULL) *target = (*target)->next;
        (*target)->next = value;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, ReplyId replyId){
    SubreplyPointer newSubreply = malloc(sizeof(Subreply));
    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newSubreply->reply);
    tweet->replyCount++;

    reply->id = tweet->replyCount;
    string_copy(content, (newSubreply->reply).content, MAX_REPLY);
    reply->author = author;
    // TODO: Datetime

    SubreplyPointer* target;
    if(replyId == -1) target = &(tweet->subreply);
    else target = &(getReply(tweetId, replyId)->subreply);

    insertReply(target, newSubreply);

    return reply->id;
}

Reply* getReplyRecur(SubreplyPointer start, ReplyId target){
    SubreplyPointer curr = start;
    while (curr != NULL){
        if(curr->reply.id == target) return &(curr->reply);

        Reply *r = getReplyRecur((curr->reply).subreply, target);
        if (r) return r;

        curr = curr->next;
    }
    return NULL;
}

Reply* getReply(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    return getReplyRecur(tweet->subreply, replyId);
}

void displayReplyRecurIO(SubreplyPointer start, int tab){
    SubreplyPointer curr = start;
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