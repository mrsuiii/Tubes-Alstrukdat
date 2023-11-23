#include<stdio.h>
#include <stdlib.h>

#include "max_heap.h"

alamat createMaxHeap(int capacity){
    alamat maxHeap = (alamat)malloc(sizeof(MaxHeap));
    maxHeap->elements = (Tweet**)malloc(capacity*sizeof(Tweet*));
    maxHeap->size = 0;
    maxHeap->capacity = capacity;
    return maxHeap;
}
    
void insertTweet(alamat maxHeap,Tweet tweet){
    if(isFullTree)increaseCapacity(maxHeap){
        increaseCapacity(maxHeap);
    }
    maxHeap->elements[maxHeap->size] = (Tweet*)malloc(sizeof(Tweet));
    maxHeap->elements[maxHeap->size]->like = tweet.like;
    maxHeap->elements[maxHeap->size]->id = tweet.id;

    // Increment size
    maxHeap->size++;

    // Lakukan proses heapifyUp untuk memastikan properti heap terjaga
    heapifyUp(maxHeap, maxHeap->size - 1);
}
int isEmpty(alamat maxHeap){
    return maxHeap->size ==0;
}

Tweet* removeMax(alamat maxHeap) {
    if (isEmpty(maxHeap)) {
        // Heap kosong, tidak ada yang dihapus
        return NULL ;
    }
    // Simpan elemen maksimum untuk dikembalikan
    Tweet* maxElement = maxHeap->elements[0];
    // Pindahkan elemen terakhir ke posisi root
    maxHeap->elements[0] = maxHeap->elements[maxHeap->size - 1];
    // Kurangi ukuran heap
    maxHeap->size--;
    // Lakukan proses heapifyDown untuk memastikan properti heap terjaga
    heapifyDown(maxHeap, 0);

    return maxElement;
}

boolean isFullTree(alamat maxHeap){
    return maxHeap->size == maxHeap->capacity;
}
int getParentIndex(int index){
    return index/2;
}
int getLeftChildIndex(int index){
    return index*2+1;
}
int getRightChildIndex(int index){
    return (index+1)*2;
}
void swap(Tweet **a, Tweet **b){
    Tweet* temp =*a;
    *a =*b;
    *b = temp;
}
void destroyMaxHeap(alamat maxHeap){
    free(maxHeap->elements);
    free(maxHeap);
}

void heapifyDown(alamat maxHeap,int index){
    int largest=index;
    int left = getLeftChildIndex(index);
    int right = getRightChildIndex(index);
    if (left <= maxHeap->size && maxHeap->elements[left]->like > maxHeap->elements[largest]->like) {
        largest = left;
    }
    if(right <= maxHeap->size && maxHeap->elements[right]->like > maxHeap->elements[largest]->like) {
        largest = right;}
    if( largest!=index){
        swap(&maxHeap->elements[index], &maxHeap->elements[largest]);
        heapifyDown(maxHeap, largest);
    }
}

void heapifyUp(alamat maxHeap, int index){
    
    while(index >0 && maxHeap->elements[index]->like >=maxHeap->elements[getParentIndex(index)]->like){
        swap(&maxHeap->elements[index],&maxHeap->elements[getParentIndex(index)]);
        index = getParentIndex(index);
        if( index> 0 && maxHeap->elements[index]->like == maxHeap->elements[getParentIndex(index)]->like){
                if(maxHeap->elements[index]->id > maxHeap->elements[getParentIndex(index)]->id){
                    swap(&maxHeap->elements[index],&maxHeap->elements[getParentIndex(index)]);
                    index = getParentIndex(index);
                }
        }
    }
}
void increaseCapacity(alamat maxHeap){
    int newCapacity = maxHeap->capacity *2;
    maxHeap->elements =  (Tweet**)realloc(maxHeap->elements,newCapacity * sizeof(Tweet*));
    maxHeap->capacity = newCapacity;
    // if(maxHeap->elements == NULL){
    //     ex
    // }
}

void showFYB(alamat maxHeap){
    int cnt = 0;
    for (int i=0;i<tweets.nEff;i++){
        insertTweet(maxHeap,tweets.buffer[i]);
    }
    printf("Berikut %d kicauan dengan like tertinggi di FYB\n", 8);
    printf("\n");
    while(cnt<8&&cnt<tweets.nEff){
        Tweet* topTweet = removeMax(maxHeap);
        printf("Kicauan %d: ",cnt+1);
        printf(" | ");
        printf(" %s \n",topTweet->author);
        printf(" |  %s \n", topTweet->dateTime);
        printf(" |   plz FYB (For Your Burbir) ! \n");
        printf(" | Disukai:  %d",topTweet->like);
    }
    destroyMaxHeap(maxHeap);
}