#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"

void insertLastSubreply(SubreplyPointer* target, SubreplyPointer value){
    if(*target == NULL){
        *target = value;
    } else {
        while((*target)->next != NULL) *target = (*target)->next;
        (*target)->next = value;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, SubreplyPointer* target){
    SubreplyPointer newSubreply = malloc(sizeof(Subreply));
    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newSubreply->reply);
    tweet->replyCount++;

    reply->id = tweet->replyCount;
    string_copy(content, (newSubreply->reply).content, MAX_REPLY);
    reply->author = author;
    // TODO: Datetime

    insertLastSubreply(target, newSubreply);
    return reply->id;
}

Reply* getSubreplyRecur(SubreplyPointer start, ReplyId target){
    SubreplyPointer curr = start;
    while (curr != NULL){
        if(curr->reply.id == target) return &(curr->reply);

        Reply *r = getSubreplyRecur((curr->reply).subreply, target);
        if (r) return r;

        curr = curr->next;
    }
    return NULL;
}

SubreplyPointer* getSubreply(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    if(replyId == -1) return &(tweet->subreply);
    return &(getSubreplyRecur(tweet->subreply, replyId)->subreply);
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