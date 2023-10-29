#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"

void insertLastReplies(Replies* base, ReplyNodePointer value){
    if(*base == NULL){
        *base = value;
    } else {
        ReplyNodePointer curr = *base;
        while(curr->next != NULL) curr = curr->next;
        curr->next = value;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, Replies* base){
    ReplyNodePointer newSubreply = malloc(sizeof(ReplyNode));
    newSubreply->base = base;

    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newSubreply->reply);
    tweet->replyCount++;

    reply->id = tweet->replyCount;
    string_copy(content, (newSubreply->reply).content, MAX_REPLY);
    reply->author = author;
    // TODO: Datetime

    if(base == NULL) return -1;
    insertLastReplies(base, newSubreply);

    return reply->id;
}

ReplyNodePointer getReplyRecur(Replies start, ReplyId target){
    if(start == NULL) return NULL;

    ReplyNodePointer curr = start;
    while(curr != NULL){
        if(curr->reply.id == target) return curr;
        ReplyNodePointer r = getReplyRecur(curr->reply.replies, target);
        if(r) return r;
        curr = curr->next;
    }
    return NULL;
}

ReplyNodePointer getReply(TweetId tweetId, ReplyId replyId){
    return getReplyRecur(getTweet(tweetId)->replies, replyId);
}

Replies* getReplies(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    if(replyId == -1) return &(tweet->replies);

    ReplyNodePointer parent = getReply(tweetId, replyId);
    if(parent == NULL) return NULL;

    return &(parent->reply.replies);
}

void displayReplyRecurIO(Replies start, int tab){
    ReplyNodePointer curr = start;
    while (curr != NULL){
        Reply reply = curr->reply;
        printf("%d %s\n", tab, reply.content);
        displayReplyRecurIO(reply.replies, tab + 1);
        curr = curr->next;
    }
}

void displayReplyIO(TweetId tweetId){
    displayReplyRecurIO(getTweet(tweetId)->replies, 0);
}

void deleteReplyRecur(Replies start){
    ReplyNodePointer curr = start;
    while(curr != NULL){
        deleteReplyRecur(curr->reply.replies);

        ReplyNodePointer next = curr->next;
        free(curr);
        curr = next;
    }
}

void deleteReply(ReplyNodePointer target){
    deleteReplyRecur(target->reply.replies);

    ReplyNodePointer curr = *(target->base);
    if(curr == target){
        *(target->base) = target->next;
    } else {
        while(curr != NULL){
            if(curr->next == target) break;
            curr = curr->next;
        }
        curr->next = target->next;
    }

    free(target);
}