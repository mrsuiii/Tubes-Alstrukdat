# include <stdlib.h>
#include <stdio.h>

#include "tweet.h"
#include "user.h"
#include "relation.h"
#include "get_string.h"
#include "reply.h"
#include "string.h"
#include "thread.h"
#include "ADT/datetime.h"

Tweets tweets; 

boolean isIdValid(TweetId id){
    return (id >= 1 && id <= tweets.nEff);
}

TweetId createTweet(char* content, UserId author){
    if (tweets.capacity == 0 ){
        tweets.buffer = (Tweet*) malloc (sizeof(Tweet));
        tweets.capacity = 1; 
    } else if (tweets.capacity == tweets.nEff){
        tweets.buffer = (Tweet *) realloc (tweets.buffer, sizeof(Tweet) * (tweets.capacity * 2)) ;
        tweets.capacity = tweets.capacity * 2 ; 
    }

    if(!tweets.buffer) return -1; 
    tweets.nEff ++ ; 
    Tweet* tweet = getTweet(tweets.nEff) ; 
    tweet -> id =  tweets.nEff ; 
    string_copy(content, tweet->tweet, MAX_TWEET) ; 
    tweet -> like = 0 ; 
    tweet -> author =  author;   
    // tweet -> datetime =  DetikToTIME(0) ; 
    // tweet -> subreply = NULL ;  

    return tweet->id ; 
}

Tweet* getTweet(TweetId id){
    return &(tweets.buffer[id - 1]) ; 
}


// Pemrosesan IO //
void createTweetIO(){
    printf("Masukkan kicauan: \n"); 
    char content [MAX_TWEET] ; 
    get_string(content, MAX_TWEET) ; 

    TweetId newTweetId = createTweet(content, loggedUser->id);
    
    if (isAllBlank(content)){
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    } else {         
        printf("Selamat! kicauan telah diterbitkan!\n"); 
        displayTweetIO(newTweetId);
    }

}

void changeTweetIO(TweetId id) {
    if (!isIdValid(id)){
        printf("Tidak ditemukan kicauan dengan ID ==%d!\n",id);
    } else {
        Tweet* tweet = getTweet(id) ; 
        User* tweeter = getUser(tweet->author) ;  // tweeeter = pengicau
        if (loggedUser != tweeter){
            printf("Kicauan dengan ID = %d bukan milikmu!\n",id);
        } else {
            printf("Masukkan kicauan baru: \n");

            char newContent [MAX_TWEET] ; 
            get_string(newContent, MAX_TWEET);

            if (isAllBlank (newContent)){
                printf("Kicauan tidak boleh hanya berisi spasi!\n");
            }
            else {
                printf("Selamat! kicauan telah diterbitkan!\n");
                printf("Detil kicauan:\n");
                string_copy(newContent, tweet->tweet, MAX_TWEET) ;         
            }
        }
    }
}

void likeTweetIO(TweetId id){
    if (!isIdValid(id)){
        printf("Tidak ditemukan kicauan dengan ID ==%d;\n",id);
    } else {
        Tweet* tweet = getTweet(id) ; 
        User* tweeter = getUser(tweet->author) ;  // tweeeter = pengicau
        if (tweeter->type == 1  && !isFriend(loggedUser->id, tweeter->id)){
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
        } else {
            tweet->like ++ ; 
        }
    }
}

void displayTweetIO(TweetId id){
    Tweet* tweet = getTweet(id) ; 
    User* user = getUser(tweet->author);
    
    printf("| ID: %d\n", tweet-> id);
    printf("| %s\n", user-> name);
    // printf("| %s\n", tweet->datetime);
    printf("| %s\n", tweet -> tweet);
    printf("| Disukai: %d\n\n", tweet->like);
}

void displayAllTweetIO() {
    if (!loggedUser){
        printf("Anda belum login\n");
        return ; 
    }
    for(int i = tweets.nEff ; i >= 1; i ++){
        Tweet *tweet = getTweet(i) ; 
        
        if(
            !isFriend(loggedUser->id, tweet->author) &&
            tweet->author != loggedUser->id
        ) continue;
        displayTweetIO(i); 
    }
}
