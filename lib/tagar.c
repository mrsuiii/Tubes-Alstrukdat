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
    int key = 0, p = 1, m = CAPACITY;
    for (int i = 0; i < string_length(hastag);i++){
        if (hastag[i] < 'a'){
            hastag[i] += 32;
        }
        key+= ((hastag[i] - 'a' + 1) * p) % m;
        printf("karakter: %c ; hash: %d ; key = %d\n",hastag[i],hastag[i] - 'a' + 1,key);
        p *= 31;
    }
    
    return key;
}

// void insertHastag(HashMap* map, char* hastag, TweetId id){
//     int index = hash(hastag);
//     HashmapValue* hashmap = (HashmapValue*)malloc(sizeof(HashmapValue));
//     hashmap->id = id;
//     string_copy(hastag,hashmap->key,MAX_TAGAR);
//     if (map->tagar[index] == NULL){
//         hashmap->next = map->tagar[index]; /*next == NULL (kalo ngga collide)*/
//     } else { /* yah collide*/
//         while (map->tagar[index]->next != NULL)
//         {
//             map->tagar[index] = map->tagar[index]->next;
//         }
//         map->tagar[index]->next = 
//     }
//     map->tagar[index] = hashmap;
// }

void displayHastag(HashMap* map, char* hastag){
    int index = hash(hastag);
    HashmapValue* hashmap = map->tagar[index];
    while (hashmap->next != NULL){
        if (string_compare(hashmap->key,hastag) == 0){
            displayTweet(hashmap->id);
        }
        hashmap = hashmap->next;
    }
}
// [x,x,x,x,x,x,x,x,...,10^7]
//      v
//      x2
// tweet
// hastag: #bluebir
// #bluebir -> key
// key mod m , m = 10^7
// 