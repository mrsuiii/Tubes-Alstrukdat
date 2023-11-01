#include "_test_.h"
#include "../lib/draft.h"
#include "../lib/user.h"
#include "../lib/ADT/boolean.h"
#include "../lib/routine.h"

int main(){
    DEFINE_TEST("Create Draft - SIMPAN",
        setup();
        char in[] = "ini Draft;SIMPAN;"; char* out;
        UserId id = createUser("ciko", "");
        loggedUser = getUser(id);

        interceptStdIO(in, &out);
        createDraftIO();
        clearStdIO();
    
        char err[MAX_ERROR];
        boolean res = string_include(out, "berhasil disimpan");
        if(!res){
            string_copy("Draft tidak berhasil dibuat", err, MAX_ERROR);
        } else{
            res = string_include(in, getDraft(id)->content);
            if(!res){
                string_copy("Draft tidak ditemukan", err, MAX_ERROR);
            }
        }
        cleanup();
   , res, "");
   
    DEFINE_TEST("Create Draft - HAPUS",
        setup();
        char in[] = "ini Draft;HAPUS;"; char* out;
        UserId id = createUser("ciko", "");
        loggedUser = getUser(id);

        interceptStdIO(in, &out);
        createDraftIO();
        clearStdIO();

        char err[MAX_ERROR];
        boolean res = string_include(out, "berhasil dihapus");
        printf("%s",out);
        if(!res){
            string_copy("Draft tidak berhasil dihapus", err, MAX_ERROR);
        } else{
            res = getDraft(id) == NULL;
            if(!res){
                string_copy("Draft ditemukan", err, MAX_ERROR);
            }
        }
        cleanup();
   , res, "");
   
    DEFINE_TEST("Create Draft - TERBIT",
        setup();
        char in[] = "ini Draft;TERBIT;"; char* out;
        UserId id = createUser("ciko", "");
        loggedUser = getUser(id);

        interceptStdIO(in, &out);
        createDraftIO();
        clearStdIO();

        char err[MAX_ERROR];
        boolean res = string_include(out, "kicauan telah diterbitkan");
        printf("%s",out);
        if(!res){
            string_copy("Draft tidak berhasil diterbitkan", err, MAX_ERROR);
        } else{
            res = getDraft(id) == NULL;
            if(!res){
                string_copy("Draft ditemukan", err, MAX_ERROR);
            }
        }
        cleanup();
   , res, "");
   
}