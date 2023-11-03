#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"
#include "relation.h"
#include "get_string.h"

void insertLastReplies(Replies* base, ReplyNodePointer value){
    if(*base == NULL){
        *base = value;
    } else {
        ReplyNodePointer curr = *base;
        while(curr->next != NULL) curr = curr->next;
        curr->next = value;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, Replies* base, ReplyPointer* result){
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

    if(result != NULL) *result = reply;

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

ReplyNodePointer getReplyNode(TweetId tweetId, ReplyId replyId){
    Tweet* tweet = getTweet(tweetId);
    if(!tweet) return NULL;
    return getReplyRecur(tweet->replies, replyId);
}

ReplyPointer getReply(TweetId tweetId, ReplyId replyId){
    ReplyNodePointer p = getReplyNode(tweetId, replyId);
    if(!p) return NULL;
    return &(p->reply);
}

Replies* getReplies(TweetId tweetId, ReplyId replyId){
    Tweet *tweet = getTweet(tweetId);
    if(replyId == -1) return &(tweet->replies);

    ReplyNodePointer parent = getReplyNode(tweetId, replyId);
    if(parent == NULL) return NULL;

    return &(parent->reply.replies);
}

void pt(int tab){
    for(int i = 0; i < tab; ++i) printf("\t");
}

void displaySingleReply(ReplyPointer reply, User* author, int t){
    pt(t); printf("| ID = %d\n", reply->id);
    pt(t); printf("| %s\n", author->name);
    // TODO: Date
    pt(t); printf("| date\n");
    pt(t); printf("| %s\n", reply->content);
}

void displaySinglePrivateReply(ReplyPointer reply, int t){
    pt(t); printf("| ID = %d\n", reply->id);
    pt(t); printf("| PRIVAT\n");
    pt(t); printf("| PRIVAT\n");
    pt(t); printf("| PRIVAT\n");
}

void displayReplyRecurIO(ReplyNodePointer start, int tab){
    ReplyNodePointer curr = start;
    while (curr != NULL){
        ReplyPointer reply = &(curr->reply);
        User* author = getUser(curr->reply.author);

        if(
            isFriend(author->id, loggedUser->id) ||
            loggedUser->id == author->id
        ){
            displaySingleReply(reply, author, tab);
        } else {
            displaySinglePrivateReply(reply, tab);
        }
        printf("\n");

        displayReplyRecurIO(reply->replies, tab + 1);
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

void createReplyIO(TweetId tweetId, ReplyId replyId){
    Tweet* tweet = getTweet(tweetId);
    if(!tweet){
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
        return;
    }

    Replies* replies = getReplies(tweetId, replyId);
    if(!replies){
        printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
        return;
    }

    if(
        !isFriend(tweet->author, loggedUser->id) &&
        loggedUser->id != tweet->author
    ){
        printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebu!\n");
        return;
    }

    char tmpReply[MAX_REPLY];
    printf("Masukkan balasan:\n");
    get_string(tmpReply, MAX_REPLY);

    ReplyPointer rp;
    ReplyId id = createReply(tmpReply, loggedUser->id, tweetId, replies, &rp);

    printf("Selamat! balasan telah diterbitkan!\nDetil balasan:\n");
    displaySingleReply(rp, loggedUser, 0);
}

void deleteReplyIO(TweetId tweetId, ReplyId replyId){
    Tweet* tweet = getTweet(tweetId);
    if(!tweet){
        printf("Kicauan tidak ditemukan\n");
        return;
    }

    ReplyNodePointer rp = getReplyNode(tweetId, replyId);
    if(!rp){
        printf("Balasan tidak ditemukan\n");
        return;
    }

    if(rp->reply.author != loggedUser->id){
        printf("Balasan bukan milik anda\n");
        return;
    }

    deleteReply(rp);
    printf("Balasan berhasil dihapus\n");
}

int maxLine = 1000;
int maxConfig = 1000000;

void repliesToConfig(Replies replies, int parent){
    ReplyNodePointer current = replies;
    while(current){
        Reply reply = current->reply;

        printf("%d %d\n%s\n%s\n", parent, reply.id, reply.content, getUser(reply.author)->name);

        repliesToConfig(reply.replies, reply.id);
        current = current->next;
    }
}

void replyToConfig(){
    TweetPointer tweet[tweets.nEff];
    int tweetCount = 0;
    for(int id = 1; id <= tweets.nEff; ++id){
        TweetPointer tp = getTweet(id);
        if(tp->replies != NULL){
            tweet[tweetCount] = tp;
            ++tweetCount;
        }
    }

    printf("%d\n", tweetCount);

    for(int i = 0; i < tweetCount; ++i){
        printf("%d\n", tweet[i]->id);
        repliesToConfig(tweet[i]->replies, -1);
    }
}