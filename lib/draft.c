#include <stdlib.h>
#include <stdio.h>
#include "draft.h"
#include "string.h"

DraftAddress drafts[MAX_USER];

/* Create new draft */
DraftAddress newDraft(){
    DraftAddress address  = malloc(sizeof(Draft));
    string_copy("", address->text, 1);
    address->next = NULL;
    return address;
}

/* Create a draft */
void createDraft(UserId id, char* newText){
    DraftAddress n = newDraft(id);
    if(isDraftEmpty(id)){
        drafts[id] = newDraft();
        string_copy(newText, drafts[id]->text, MAX_TWEET);
    } else {
        string_copy(newText, n->text, MAX_TWEET);
        n->next = drafts[id];
        drafts[id] = n;
    }
}

/* Get Draft */
DraftAddress getDraft(UserId id){
    return drafts[id];
}


/* Check if Draft is Empty */
boolean isDraftEmpty(UserId id){
    if(drafts[id] == NULL){
        return true;
    } else{
        return false;
    }
}

/* Delete last draft */
void deleteDraft(UserId id){
    DraftAddress p = getDraft(id);
    drafts[id] = drafts[id]->next;
    free(p);
}

/* Publish last draft */
void publishDraft(UserId id);

/* Display last draft */
void displayDraftIO(UserId id){
    DraftAddress draft = drafts[id];
    if(draft == NULL){
        printf("Yah, Anda belum memiliki draf apapun!\n");
    } else{
        printf("Isi Draft :\n%s\n", draft->text);
    }
}

/* Get amount of draft of a user */
int draftLength(UserId id){
    DraftAddress curr = drafts[id];
    int i = 0;
    while(curr != NULL){
        curr = curr->next; 
        ++i;
    }
    return i;
}