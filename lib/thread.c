# include <stdlib.h>
#include <stdio.h>

#include "tweet.h"
#include "user.h"
#include "relation.h"
#include "get_string.h"
#include "reply.h"
#include "string.h"
#include "ADT/datetime.h"


Threads threads ; 

// return true if threadId is a valid ThreadId
boolean isMainThreadIdValid(ThreadId threadId){
    return !(threadId > threads.nEff || threadId < 1);
}

// return true if threadIdx is a valid idx for a valid mainThreadId
boolean isThreadIdxValid(ThreadId mainThreadId, int threadIdx){
    return !(threadIdx > (threads.buffer[mainThreadId])->threadCount || threadIdx < 1);
}

// return true if Tweet * pointing into a tweet that is also a thread 
boolean isThread(Tweet * tweetPointer){
    for (int i = 1; i <= threads.nEff; i++){
        if (threads.buffer[i] == tweetPointer) return true ; 
    }
    return false;
}

// create a new thread and return the pointer 
ThreadPointer newThread(char* content){
    ThreadPointer thread = (ThreadPointer) malloc (sizeof(ThreadPointer));
    string_copy(content, thread->content, MAX_THREADS);
    thread->nextThread = NULL ; 
    return thread ; 
}

// make a pointer into a thread and return the pointer into that tweet
Tweet * makeMainThread(Tweet * mainThread) {
    if (threads.capacity == 0 ){
        threads.buffer = (Tweet **) malloc (sizeof(Tweet *));
        threads.capacity = 1; 
    } else if (threads.capacity == threads.nEff){
        threads.buffer = (Tweet * *) realloc (threads.buffer, sizeof(Tweet *) * (threads.capacity * 2)) ;
        threads.capacity = threads.capacity * 2 ; 
    }

    if(!threads.buffer) return NULL; 
    threads.nEff ++ ; 
    threads.buffer[threads.nEff] = mainThread;;

    return threads.buffer[threads.nEff]; 
}

// reutrn the pointer of a thread with Id == mainThreadId
Tweet * getMainThread(ThreadId mainThreadId) {
    return (threads.buffer[mainThreadId]);
}

// return the pointer of thread with threadId == mainThread and threadIdx == threadIdx
ThreadPointer getThread(Tweet * mainThread, int threadIdx){
    ThreadPointer currThread = mainThread->firstThread;

    for(int i = 1 ; i < threadIdx ; i++){
        currThread = currThread->nextThread;
    }
    return currThread;
}

// I.S : mainThread is a valid Thread, threadIdx -1 is a valid thread IDx for that mainThread or threadIdx ==1
// F.S : insert new thread at mainThread with threadIdx and .content == content
void continueThreadAt(Tweet * mainThread, int threadIdx, char* content) {
    ThreadPointer new = newThread(content);
    
    if (threadIdx == 1){
        new->nextThread = mainThread->firstThread;
        mainThread->firstThread = new;
    } else {
        ThreadPointer prev = getThread(mainThread, threadIdx -1);

        new->nextThread = prev->nextThread;
        prev->nextThread = new ; 
        
    }   
    mainThread->threadCount += 1; 
}

// I.S : mainThread is a valid Thread, threadIdx is a valid thread 
// F.S : deletet the thread of mainThread at idx == threadIdx
void deleteThreadAt(Tweet * mainThread, int threadIdx){
    if (threadIdx == 1 ){
        printf("hehe;");
        ThreadPointer first = mainThread->firstThread;
        mainThread->firstThread = first->nextThread;
        free(first);
    } else {
        ThreadPointer prev = getThread(mainThread, threadIdx -1);
        ThreadPointer delete = prev->nextThread;
        prev->nextThread = delete->nextThread;
        free(delete);
        mainThread->threadCount --;
    }
}

// I.S : mainThreadId is a valid thread 
// F.S : display the tweet with ThreadId == mainThreadId 
void displayThreadSeqIO(ThreadId mainThreadId){
    printf("\n");
    if (!loggedUser){
        printf("Anda belum login\n");
        return ; 
    }

    if (mainThreadId > threads.nEff || mainThreadId < 1){
        printf("Utas tidak ditemukan!\n");
    } else {
        Tweet * mainThread = getMainThread(mainThreadId);
        User* user = getUser(mainThread->author);
        if(!isFriend(loggedUser->id, mainThread->author) && mainThread->author != loggedUser->id){
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        } else {
            ThreadPointer currThread = mainThread->firstThread;
            int count = 1 ; 
            displayTweetIO(mainThread->id);
            while (currThread != NULL){
                printf("   | INDEX: %d\n", count);
                printf("   | %s\n", user->name);
                // printf("| %s\n", tweet->datetime);
                printf("   | %s\n\n",  currThread -> content);
                currThread = currThread->nextThread;

                count ++;
            }
        }
    }
}

// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menginsert thread baru pada parameter yang diberikan
// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menginsert thread baru pada parameter yang diberikan
void continueThreadAtIO(ThreadId mainThreadId, int threadIdx) {
    printf("\n");
    if (!(isMainThreadIdValid(mainThreadId)) && mainThreadId != 1){
        printf("Utas tidak ditemukan!\n");
    } else if (!(isThreadIdxValid(mainThreadId, threadIdx-1)) && threadIdx!=1){
        printf("Index terlalu tinggi!\n");

    } else {
        Tweet * mainThread = getMainThread(mainThreadId);

        if (loggedUser->id != mainThread->author){
            printf("Anda tidak bisa menyambung kicauan dalam utas ini!\n");
        } else{
            printf("Masukkan kicauan: \n");
            char content[MAX_THREADS];
            get_string(content,MAX_THREADS);

            continueThreadAt(mainThread, threadIdx, content);
        }
    }
}

// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menghapus thread pada parameter yang diberikan
void deleteThreadAtIO(ThreadId mainThreadId, int threadIdx){
    printf("\n");
    if (!(isMainThreadIdValid(mainThreadId)) && mainThreadId != 1){
        printf("Utas tidak ditemukan!\n");
    } else if ((!isThreadIdxValid(mainThreadId, threadIdx-1) && threadIdx!=1)){
        printf("Index terlalu tinggi!\n");
    } else {
        printf("masuk");
        Tweet * mainThread = getMainThread(mainThreadId);
        deleteThreadAt(mainThread, threadIdx);
    }
}

// I.S bebas
// F.S menjadikan tweet dengan Id == tweetId menjadi sebuah thread 
void makeMainThreadIO(TweetId tweetId){
    printf("\n");
    if (isMainThreadIdValid(tweetId)){
        printf("Utas telah dibuat sebelumnya!\n");
    } else if (tweetId < 1 || tweetId > tweets.nEff){
        printf("Kicauan tidak ditemukan!\n");
    } else if (loggedUser->id != (tweets.buffer->author)){
        printf("Utas ini bukan milik Anda\n");
    } else{
        printf("Utas berhasil dibuat!\n");

        Tweet * mainThread =  getTweet(tweetId);
        makeMainThread(mainThread);
        ThreadId mainThreadId = threads.nEff;

        char input[6];
        do {
            continueThreadAtIO(mainThreadId, (mainThread->threadCount) + 1);
            printf("\n");
            printf("Apakah Anda ingin melanjutkan Utas ini? (YA/TIDAK) ");
            get_string(input, 6);
        } while(!string_compare(input, "YA")); //string_compare(a,b) == 0 <-> a = b
        printf("Utas selesai!\n");
    }
}



