# include <stdlib.h>
#include <stdio.h>

#include "tweet.h"
#include "user.h"
#include "relation.h"
#include "get_string.h"
#include "reply.h"
#include "string.h"
#include "thread.h"
#include "config.h"
#include "ADT/datetime.h"
#include "tagar.h"
Tweets tweets; 
HashMap* hashmapHastag;
boolean isIdValid(TweetId id){
    return (id >= 1 && id <= tweets.nEff);
}

Tweet* getTweet(TweetId id){
    return &(tweets.buffer[id - 1]) ; 
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
    string_copy(content, tweet->content, MAX_TWEET) ; 
    tweet -> like = 0 ; 
    tweet -> author =  author;   
    // tweet -> datetime =  DetikToTIME(0) ; 
    // tweet -> subreply = NULL ;  

    return tweet->id ; 
}

void editTweet(TweetId id, UserId author, char* newContent){
    Tweet* tweet = getTweet(id) ; 
    string_copy(newContent, tweet->content, MAX_TWEET) ; 
}

void likeTweet(TweetId id){
    Tweet* tweet = getTweet(id); 
    tweet->like ++ ; 
}

// Pemrosesan IO //
void createTweetIO(){
    printf("Masukkan kicauan: \n"); 
    char content [MAX_TWEET] ; 
    get_string(content, MAX_TWEET) ; 

    TweetId newTweetId = createTweet(content, loggedUser->id);
    
    printf("\nMasukkan tagar:\n");
    char hastag [MAX_TAGAR];
    get_string(hastag,MAX_TAGAR);
    HashMap* cobadulu = (HashMap*)malloc(sizeof(HashMap));
    createHastag(cobadulu);
    insertHastag(cobadulu,hastag,newTweetId);
    if (isAllBlank(content)){
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    } else {
        printf("Selamat! kicauan telah diterbitkan!\n"); 
        displayTweet(newTweetId);
    }
}

void editTweetIO(char* rawTweetId) {
    int id;

    if(!string_to_integer(rawTweetId, &id)){
        printf("\"%s\" bukan id yang valid\n", rawTweetId);

    }

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
                editTweet(id, loggedUser->id, newContent);
                displayTweet(id);
            }
        }
    }
}

void likeTweetIO(char* rawTweetId){
    int id;

    if(!string_to_integer(rawTweetId, &id)){
        printf("\"%s\" bukan id yang valid\n", rawTweetId);
        return;
    }

    if (!isIdValid(id)){
        printf("Tidak ditemukan kicauan dengan ID ==%d;\n",id);
    } else {
        Tweet* tweet = getTweet(id) ; 
        User* tweeter = getUser(tweet->author) ;  // tweeeter = pengicau
        if (tweeter->type == 1  && !isFriend(loggedUser->id, tweeter->id)){
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
        } else {
            likeTweet(id);
        }
    }
}

void displayTweet(TweetId id){
    Tweet* tweet = getTweet(id) ; 
    User* user = getUser(tweet->author);
    
    printf("| ID: %d\n", tweet-> id);
    printf("| %s\n", user-> name);
    // printf("| %s\n", tweet->datetime);
    printf("| %s\n", tweet -> content);
    printf("| Disukai: %d\n\n", tweet->like);
}

void displayAllTweetIO() {
    if (!loggedUser){
        printf("Anda belum login\n");
        return ; 
    }
    for(int i = tweets.nEff  ; i >= 1; i --){
        Tweet *tweet = getTweet(i) ; 
        
        if(
            !isFriend(loggedUser->id, tweet->author) &&
            tweet->author != loggedUser->id
        ) continue;
        displayTweet(i); 
    }
}

void tweetToConfig(){
    printf("%d\n", tweets.nEff); 
    int i ; 
    for (i = 1 ; i <= tweets.nEff; i ++){
        TweetPointer tweet = getTweet(i); 
        User* author = getUser(tweet->author);
        printf("%d\n", i );
        printf("%s\n", tweet->content);
        printf("%d\n", tweet->like);
        printf("%s\n", author ? author->name : "UNKNOWN_USER");
        printf("%s\n", "DATETIME");
    }
}

void configToTweet(){
    int count = readInt(); nextLine();

    Tweet tweets[100];
    for(int i = 0; i < count; ++i){
        int id = readInt(); nextLine();
        Tweet* tweet = &(tweets[id - 1]);

        readTill(tweet->content, "\n", MAX_TWEET); nextLine();

        int like = readInt(); nextLine();
        tweet->like = like;

        char author[MAX_NAME];
        readTill(author, "\n", MAX_NAME); nextLine();
        tweet->author = getUserIdByName(author);

        char datetime[100];
        readTill(datetime, "\n", 100); nextLine();
    }

    for(int i = 0; i < count; ++i){
        Tweet *src = &(tweets[i]);
        Tweet *dst = getTweet(createTweet(src->content, src->author));
        dst->like = src->like;
    }
}