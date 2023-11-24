#ifndef MAX_HEAP_H
#define MAX_HEAP_H
#include "adt.h"


typedef  int Eltype;

typedef struct maxHeap 
{
    Tweet** elements;
    int size;
    int capacity;
}MaxHeap;
typedef struct maxHeap* alamat;


void heapifyUp(alamat maxHeap, int index);

alamat createMaxHeap(int capacity);

void heapifyDown(alamat maxHeap,int index);

void insertTweet(alamat maxHeap,Tweet tweet);

Tweet* removeMax(alamat maxHeap);

void destroyMaxHeap(alamat maxHeap);

void increaseCapacity(alamat maxHeap);
void showFYB();
#endif