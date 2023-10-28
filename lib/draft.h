#ifndef DRAFT_H
#define DRAFT_H

#include "tweet.h"

#define DELETE_DRAFT 0
#define UPLOAD_DRAFT 1
#define SAVE_DRAFT 2
#define BACK_DRAFT 3

typedef struct Draft* DraftAddress;
typedef struct Draft{
    char text[MAX_TWEET];
    DraftAddress next;    
} Draft;

/* Create new draft */
DraftAddress newDraft();

/* Create a draft, if not empty then Insertfirst */
void createDraft(UserId id, char* newText);

/* Get First Draft */
DraftAddress getDraft(UserId id);

/* Check if Draft is Empty */
boolean isDraftEmpty(UserId id);

/* Delete last draft */
void deleteDraft(UserId id);

/* Publish last draft */
void publishDraft(UserId id);

/* Display last draft */
void displayDraftIO(UserId id);

/* Get amount of draft of a user */
int draftLength(UserId id);

#endif