#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"

ReplyId createReply(char *content, UserId author, TweetId tweetId, ReplyId replyId){
    struct subreply* newReply = malloc(sizeof(Subreply));
    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newReply->reply);
    tweet->replyCount++;

    reply->id = tweet->replyCount;
    string_copy(content, (newReply->reply).content, MAX_REPLY);
    reply->author = author;
    // TODO: Datetime

    struct subreply** target;
    if(replyId == -1) target = &(tweet->subreply);
    else target = &(getReply(tweetId, replyId)->subreply);

    (*target) = newReply;
    // while((*target) && (*target)->next != NULL) (*target) = (*target)->next;

    return 0;
    printf("%p %p\n", target, &(tweet->subreply));
}

Reply* getReplyRecur(Subreply *start, ReplyId target){
    Subreply *curr = start;
    while (curr != NULL){
        Reply *r = getReplyRecur((curr->reply).subreply, target);
        if (r->id == target) return r;
        if (r) return r;
        curr = curr->next;
    }
}

Reply* getReply(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    return getReplyRecur(tweet->subreply, replyId);
}