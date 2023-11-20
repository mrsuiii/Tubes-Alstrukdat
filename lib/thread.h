#ifndef THREAD_H
#define THREAD_H

#define MAX_THREADS 280


typedef int ThreadId ; 
typedef struct tweet* TweetPointer ;
typedef struct thread* ThreadPointer ;
#include "tweet.h"

// Thread adalah linked list berisi isi dari Threads itu dan alamat Threads selanjutnya
typedef struct thread{
    char content[MAX_THREADS];
    ThreadPointer nextThread ; 
}Thread;

// Threads adalah listdin berisi pointer ke Tweet karena tidak semua tweet adalah Thread
typedef struct{
    TweetPointer *buffer;
    int nEff; 
    int capacity ; 
}Threads;

boolean isMainThreadIdValid(ThreadId threadId);
boolean isThreadIdxValid(ThreadId mainThreadId, int threadIdx);
boolean isThread(TweetPointer tweet);
ThreadPointer newThread(char* content);
TweetPointer makeMainThread(TweetPointer mainThread ) ;
TweetPointer getMainThread(ThreadId mainThreadId);

ThreadPointer getThread(TweetPointer mainThread, int idx);
void continueThreadAt(TweetPointer mainThread, int threadIdx, char* content) ;
void deleteThreadAt(TweetPointer mainThread, int threadIdx);

void displayThreadSeqIO(ThreadId threadId);
void continueThreadAtIO(ThreadId mainThreadId, int threadIdx) ;
void deleteThreadAtIO(ThreadId mainThreadId, int threadIdx);
void makeMainThreadIO(TweetId tweetId);

void threadToConfig();
void configToThread();
#endif