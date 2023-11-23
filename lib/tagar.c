#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "tweet.h"
#include "tagar.h"
#include "string.h"
HashMap hashmapHastag;

HashMap* createHastag(){
    HashMap* hashtag = (HashMap*)malloc(sizeof(HashMap));
    hashtag->size = CAPACITY;
    hashtag->tagar = (HashmapValue**)malloc(CAPACITY * sizeof(HashmapValue*));
    for (int i = 0; i < CAPACITY; i++){
        hashtag->tagar[i] = NULL;
    }
    return hashtag;
}

/* menerima tagar (tanpa pagar) dari kicauan dan mengembalikan nilai kuncinya*/
int hash(char* hastag){
    long long p = 31, m = 1e9 + 7;
    long long key = 0;
    long long power = 1;
    int n;
    n = string_length(&hastag);
    for (int i = 0; i < n; i++){
        key += (hastag[i] - 'a' + 1 * (power)) % m;
        power = (power * p) % m;
    }

    return key;
}

void insertHastag(char* hastag, TweetId id){
    int n = string_length(hastag);
    char hastagtemp[MAX_TAGAR];
    string_copy(hastag,hastagtemp,MAX_TAGAR);
    for (int i = 0; i < n; i++){
        if (hastagtemp[i] < 'a'){
            hastagtemp[i] += 32;
        }
    }
    int index = hash(hastagtemp);
    HashmapValue* hashmap = (HashmapValue*)malloc(sizeof(HashmapValue));

    if (hashmapHastag.tagar[index] == NULL){
        hashmapHastag.tagar[index] = hashmap; /*next == NULL (kalo ngga collide)*/
    } else { /* yah collide */
        Address m = hashmapHastag.tagar[index];
        while (m->next != NULL)
        {
            m = m->next;
        }
        m->id = id;
        string_copy(hastagtemp,m->key,MAX_TAGAR);
        m->next = NULL;
    }
    
    hashmapHastag.tagar[index] = hashmap;
}

void displayHastag(char* hastag){
    int n = string_length(hastag);
    char hastagtemp[MAX_TAGAR];
    string_copy(hastag,hastagtemp,MAX_TAGAR);
    for (int i = 0; i < n; i++){
        if (hastagtemp[i] < 'a'){
            hastagtemp[i] += 32;
        }
    }
    int index = hash(hastagtemp);

    if (string_compare(hashmapHastag.tagar[index]->key,hastagtemp) == 0){
        Address m = hashmapHastag.tagar[index];
        while (m->next != NULL){
            if (string_compare(m->key,hastagtemp) == 0){
                displayTweetIO(m->id);
            }
            m = m->next;
        }
        if (string_compare(m->key,hastagtemp) == 0){
            displayTweetIO(m->id);
        }
    } else {
        printf("Tidak ditemukan kicauan dengan tagar #%s",hastag);
    }
}