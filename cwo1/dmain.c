#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <dlfcn.h>


/*
 * INSTRUKCJA ARGUMENTOW
 *
 * program rozm_tab rozm_bloku static/dynamic     [create] [malloc/calloc]    [search] [jakaSuma]
 *      [delete] [index] [ile]      [add] [index] [ile]     [deladdrep] [ile]
 */

void *handle;


void (*addStaticBlock)(unsigned int,unsigned int,unsigned int );
void (*deleteStaticBlock)(unsigned int , unsigned int , unsigned int );
int (*countSumS)(const char*, unsigned int);
char *(*closestSumS)(unsigned int , unsigned int , unsigned int );
void (*genRandTabS)(unsigned int , unsigned int );
void (*printTabS)(unsigned int , unsigned int );
void (*printBlockS)(char*, unsigned int );

char **(*createDynamicTableC)(unsigned int, unsigned int);
char **(*createDynamicTableM)(unsigned int, unsigned int);
void (*deleteDynamicTable)(char**, int unsigned);
char **(*addDynamicBlock)(char **, unsigned int ,unsigned int,unsigned int );
char **(*deleteDynamicBlock)(char**,unsigned int , unsigned int, unsigned int);
char *(*closestSumD)(char**, unsigned int, unsigned int, unsigned int);
int (*countSumD)(char*, unsigned int);
void (*genRandTabD)(char**, unsigned int, unsigned int);
void (*printTab)(char**, unsigned int, unsigned int);
void (*printBlock)(char*, unsigned int);




int main(int argc, char *argv[]) {



    handle = dlopen("./libblocks.so", RTLD_LAZY);

    if (!handle) {
        fprintf (stderr, "Error opening library: %s\n", dlerror());
        exit(1);
    }
    dlerror();


    addStaticBlock = dlsym(handle, "addStaticBlock");
    deleteStaticBlock = dlsym(handle, "deleteStaticBlock");
    countSumS = dlsym(handle, "countSumS");
    closestSumS = dlsym(handle, "closestSumS");
    genRandTabS = dlsym(handle, "genRandTabS");
    printTabS = dlsym(handle, "printTabS");
    printBlockS = dlsym(handle, "printBlockS");

    createDynamicTableC = dlsym(handle, "createDynamicTableC");
    createDynamicTableM = dlsym(handle, "createDynamicTableM");
    deleteDynamicTable = dlsym(handle, "deleteDynamicTable");
    addDynamicBlock = dlsym(handle, "addDynamicBlock");
    deleteDynamicBlock = dlsym(handle, "deleteDynamicBlock");
    closestSumD = dlsym(handle, "closestSumD");
    countSumD = dlsym(handle, "countSumD");
    genRandTabD = dlsym(handle, "genRandTabD");
    printTab = dlsym(handle, "printTab");
    printBlock = dlsym(handle, "printBlock");

    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error loading library components: %s\n", error);
        dlclose(handle);
        exit(1);
    }





    if(argc < 4){
        printf("Za malo operacji, podaj: rozmiar tablicy, rozmiar bloku, sposób alokacji, i max 3 operacje");
        return 0;
    }

    unsigned int tSize = (unsigned int)atoi(argv[1]);
    unsigned int bSize = (unsigned int)atoi(argv[2]);

    printf("Ile blokow: %d, Rozmiar bloku: %d, sposob alokacji: ", tSize,bSize);
    printf(argv[3]);
    printf(".\n");


    struct timeval s,e;
    struct rusage u1,u2;


    int nrArg = 4;
    int create = 0, search = 0, delete = 0, add = 0, delAddRep = 0;
    int mCreateType = 0, searchNr = 0, deleteNr = 0, deleteQty = 0, addNr = 0, addQty = 0;
    while(nrArg < argc){
        if(strcmp(argv[nrArg], "create") == 0){
            create = 1;
            if(strcmp(argv[nrArg+1], "malloc") == 0)
                mCreateType = 1;
            nrArg += 2;
            continue;
        }
        if(strcmp(argv[nrArg], "search") == 0){
            search = 1;
            searchNr = atoi(argv[nrArg + 1]);
            nrArg += 2;
            continue;
        }
        if(strcmp(argv[nrArg], "delete") == 0){
            delete = 1;
            deleteNr = atoi(argv[nrArg + 1]);
            deleteQty = atoi(argv[nrArg + 2]);
            nrArg += 3;
            continue;
        }
        if(strcmp(argv[nrArg], "add") == 0){
            add = 1;
            addNr = atoi(argv[nrArg + 1]);
            addQty = atoi(argv[nrArg + 2]);
            nrArg += 3;
            continue;
        }

        if(strcmp(argv[nrArg], "deladdrep") == 0){
            delAddRep = atoi(argv[nrArg + 1]);
            nrArg += 2;
            continue;
        }

        nrArg++;
    }

    if(strcmp(argv[3],"dynamic") == 0){
        if(mCreateType == 1)
            printf("Alokacja funkcja malloc.\n");
        else
            printf("Alokacja funkcja calloc.\n");
    }

    printf("Szukam sumy: %d, usuwam %d blokow z indeksu %d i dodaje %d blokow z indeksu %d. \n\n", searchNr, deleteQty, deleteNr, addQty, addNr);
    char **tab = NULL;



    if(strcmp(argv[3],"static") == 0){

        if(create != 1){
            printf("Table must be created. Ending program... ");
            return 0;
        }else{

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            genRandTabS(tSize,bSize);

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas alokacji statycznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika alokacji statycznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu alokacji statycznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(search != 0){

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            char *block = closestSumS(bSize, tSize, (unsigned int)searchNr);

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas szukania w tablicy statycznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika szukania w tablicy statycznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu szukania w tablicy statycznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));

            //printBlockS(block, bSize);
        }

        if(delete != 0){

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < deleteQty; i++){
                deleteStaticBlock(bSize, (unsigned int)deleteNr + i, tSize);
            }

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas usuwania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika usuwania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu usuwania bloku w tablicy statycznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(add != 0){

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < addQty; i++){
                addStaticBlock(bSize, (unsigned int)addNr + i, tSize);
            }


            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(delAddRep != 0){
            unsigned int id;
            srand((unsigned int)(time(NULL)));

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < delAddRep; i++){
                id = rand() % tSize;
                deleteStaticBlock(bSize, id, tSize);
                addStaticBlock(bSize, id, tSize);
            }

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas uswania/dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika uswania/dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu uswania/dodawania bloku w tablicy statycznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }
    }
    else if(strcmp(argv[3], "dynamic") == 0){

        if(create == 1){
            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            if(mCreateType == 0){
                tab = createDynamicTableC(tSize, bSize);
            } else{
                tab = createDynamicTableM(tSize, bSize);
            }
            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas alokacji dynamicznej w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika alokacji dynamicznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu alokacji dynamicznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));




        }
        else{
            printf("Array of blocks must be created. Ending program... ");
            return 0;
        }

        if(search != 0){
            printf("Szukam sumy..\n");
            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            closestSumD(tab, bSize, tSize, (unsigned int)searchNr);

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            //printBlock(block, bSize);

            printf("Rzeczywisty czas szukania bloku w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika alokacji dynamicznej w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu alokacji dynamicznej w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(delete != 0){

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < deleteQty; i++){
                tab = deleteDynamicBlock(tab, bSize, (unsigned int)deleteNr + i, tSize);
            }
            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas usuwania blokow w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika usuwania blokoww mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu usuwania blokow w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));

        }

        if(add != 0){

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < addQty; i++){
                tab = addDynamicBlock(tab, bSize, (unsigned int)addNr + i, tSize);
            }
            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas dodawania blokow w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika dodawania blokow w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu  dodawania blokow w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(delAddRep != 0){
            unsigned int id;
            srand((unsigned int)(time(NULL)));

            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            for(int i = 0; i < delAddRep; i++){
                id = rand() % tSize;
                tab = deleteDynamicBlock(tab, bSize, id, tSize);
                tab = addDynamicBlock(tab, bSize, id, tSize);
            }

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas naprzemiennego usuwania i dodawania blokow w mikrosekundach: %lu.\n",((e.tv_usec - s.tv_usec) ));
            printf("Czas uzytkownika naprzemiennego usuwania i dodawania blokow w mikrosekundach: %lu.\n",((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec ) ));
            printf("Czas systemu naprzemiennego usuwania i dodawania blokow w mikrosekundach: %lu.\n\n",((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec ) ));
        }

        if(create == 1) {
            getrusage(RUSAGE_SELF, &u1);
            gettimeofday(&s, NULL);

            deleteDynamicTable(tab, tSize);

            getrusage(RUSAGE_SELF, &u2);
            gettimeofday(&e, NULL);

            printf("Rzeczywisty czas usuwania blokow w mikrosekundach: %lu.\n", ((e.tv_usec - s.tv_usec)));
            printf("Czas uzytkownika usuwania blokow w mikrosekundach: %lu.\n",
                   ((u2.ru_utime.tv_usec - u1.ru_utime.tv_usec)));
            printf("Czas systemu usuwania blokow w mikrosekundach: %lu.\n\n",
                   ((u2.ru_stime.tv_usec - u1.ru_stime.tv_usec)));
        }

    }
    else{
        printf("Third argument must by 'static' or 'dynamic'");
    }



    return 0;
}
