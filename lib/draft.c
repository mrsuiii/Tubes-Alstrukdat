#include <stdlib.h>
#include <stdio.h>

#include "draft.h"

DraftAddress drafts[MAX_USER];

/* Create new empty Draft */
DraftAddress newDraft(){
    DraftAddress address  = malloc(sizeof(Draft));
    string_copy("", address->content, 1);
    address->next = NULL;
    return address;
}

/* Create a Draft */
void createDraft(UserId id, char* newcontent){
    DraftAddress n = newDraft(id);
    if(isDraftEmpty(id)){
        drafts[id] = newDraft();
        string_copy(newcontent, drafts[id]->content, MAX_TWEET);
    } else {
        string_copy(newcontent, n->content, MAX_TWEET);
        n->next = drafts[id];
        drafts[id] = n;
    }
    //drafts[id]->datetime = DetikToTIME(0);
}

/* Get last Draft */
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

/* Get amount of Draft of a user */
int draftLength(UserId id){
    DraftAddress curr = drafts[id];
    int i = 0;
    while(curr != NULL){
        curr = curr->next; 
        ++i;
    }
    return i;
}

/* Delete last Draft */
void deleteDraft(UserId id){
    DraftAddress p = getDraft(id);
    if(draftLength(id) == 1){
        drafts[id] = NULL;
    } else{
        drafts[id] = drafts[id]->next;
    }
    free(p);
}

/* Publish last Draft, IO for displayTweetIO */
void publishDraftIO(){
    UserId id = loggedUser->id;
    TweetId newTweetId = createTweet(getDraft(id)->content, id);
    deleteDraft(id);
    printf("\nSelamat! Draf kicauan telah diterbitkan!\n");
    printf("Detil balasan:\n");
    displayTweetIO(newTweetId);
}

/* Display last Draft */
void displayLastDraftIO(){
    UserId id = loggedUser->id;
    if(!isDraftEmpty(id)){
        printf("Ini draf terakhir anda:\n");
        printf("| <time made>"); /* print datetime */ printf("\n");
        printf("| %s\n", getDraft(id)->content);
    }
}

/* Display Draft and ask for command */
void displayDraftIO(){
    UserId id = loggedUser->id;
    DraftAddress draft = drafts[id];
    if(draft == NULL){
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
    } else{
        displayLastDraftIO(id);
        printf("\nApakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)\n");
        readDraftCommandIO();   
    }
}

/* Read Draft and ask for command */
void createDraftIO(){
    UserId id = loggedUser->id;
    char content[MAX_TWEET];
    do{
        printf("Masukkan draf:\n");
        get_string(content,MAX_TWEET);
        if (isAllBlank(content)){
            /* content kicauan tidak boleh kosong sehingga perlu dihandle*/
            printf("Draft tidak boleh hanya berisi spasi!\n");
        }
    } while(isAllBlank(content));
    createDraft(id,content);

    printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
    readDraftCommandIO();
}

/* Read commands for Draft (Hapus, Simpan, Ubah, Terbit) */
void readDraftCommandIO(){
    UserId id = loggedUser->id;
    char command[7]; 
    /* command yang mungkin: HAPUS; SIMPAN; UBAH; TERBIT; KEMBALI;*/ 
    get_string(command, 7);
    printf("ini isi command : %s\n",command);
    if(string_compare(command,"SIMPAN") == 0){
        printf("\nDraf telah berhasil disimpan!\n");
    } else if(string_compare(command, "TERBIT") == 0){
        publishDraftIO();
    }  else if(string_compare(command,"HAPUS") == 0){
        deleteDraft(id);
        printf("\nDraf telah berhasil dihapus!\n");
    }  else if(string_compare(command,"UBAH") == 0){
        deleteDraft(id);
        char content[MAX_TWEET];
        do{
            printf("Masukkan draf baru:\n");
            get_string(content,MAX_TWEET);
            if (isAllBlank(content)){
                /* content kicauan tidak boleh kosong sehingga perlu dihandle*/
                printf("Draft tidak boleh hanya berisi spasi!\n");
            }
        } while(isAllBlank(content));
        createDraft(id,content);
        printf("\nApakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
        readDraftCommandIO();
    } else/* command = kembali */ {
        printf("\n");
        if(string_compare(command,"KEMBALI") != 0){
            printf("Input \"%s\" tidak valid", command);
        }
        printf("\n");
    }
}

int MAX_CONFIG = 100000;

/* Convert Draft data to Config */
void draftToConfig(char* buffer){
    buffer[0] = '\0';
    char line[1000];

    int count = 0;
    for(int i = 0; i < MAX_USER; i++){
        count += draftLength(i);
    }

    snprintf(line, 1000, "%d\n", count);
    string_append(buffer, line, buffer, MAX_CONFIG);
    int id = 1;
    for(int i = 0; i < MAX_USER; i++){
        for(int j = 0; j < draftLength(i); j++){
            snprintf(line, 1000, "%d\n%s\n%s\n%s\n", id, getDraft(i)->content,getUser(i)->name, getDraft(i)->datetime);
            string_append(buffer, line, buffer, MAX_CONFIG);
            id ++;
        }
    }
}

/* Memberishkan draft */
void draftCleanUpRoutine(){
    for(int i = 0; i < MAX_USER; ++i){
        while(!isDraftEmpty(i)){
            deleteDraft(i);
        }
    }
}