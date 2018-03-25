//
// Created by Wojtek on 10.03.2018.
//

#include "dblocks.h"
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


char **createDynamicTableC(unsigned int tabSize, unsigned int blockSize){
    char **tab =  calloc(tabSize, sizeof(char*));

    for(int i=0; i<tabSize; i++){
        tab[i] = calloc(blockSize, sizeof(char));
    }

    genRandTabD(tab, tabSize, blockSize);

    return tab;
}

char **createDynamicTableM(unsigned int tabSize, unsigned int blockSize){
    char **tab =  malloc(tabSize * sizeof(char*));

    for(int i=0; i<tabSize; i++){
        tab[i] = malloc(blockSize* sizeof(char));
    }

    genRandTabD(tab, tabSize, blockSize);

    return tab;
}

void deleteDynamicTable(char **tab, int unsigned tabSize){

    if(tab == NULL){
        printf("Tablica zostala juz usunieta");
        return;
    }

    for(int i=0; i<tabSize; i++){
        free(tab[i]);
    }
    free(tab);
    tab = NULL;
    return;
}


char **addDynamicBlock(char **tab,unsigned int blockSize,unsigned int index,unsigned int tabSize){
    if(index > tabSize - 1){
        printf("Indeks poza tablica");
        return tab;
    }

    char **newTab =  calloc(tabSize + 1, sizeof(char*));
    srand((unsigned int)(time(NULL)));

    int i = 0;
    while(i<index){
        newTab[i] = tab[i];  //przypisanie blokow do nowej tablicy
        i++;
    }
    newTab[i] = calloc(blockSize, sizeof(char));  //wstawienie bloku w dobre miejsce
    char randomNr = (char)(rand() % 10);
    for(int j = 0; j < blockSize; j++)
        newTab[i][j] = randomNr;

    while(i < tabSize){
        newTab[i+1] = tab[i];  //przypisanie pozostalych blokow do nowej tablicy
        i++;
    }

    free(tab);

    return newTab;
}


char **deleteDynamicBlock(char **tab,unsigned int blockSize, unsigned int index, unsigned int tabSize){
    if(index > tabSize - 1){
        printf("Indeks poza tablica");
        return tab;
    }
    char **newTab =  calloc(tabSize - 1, sizeof(char*));
    int i = 0;
    while(i<index){
        newTab[i] = tab[i];  //przypisanie blokow do nowej tablicy
        i++;
    }

    free(tab[i]);  //usuniecie bloku o zadanym indeksie

    while(i < tabSize-1){
        newTab[i] = tab[i+1];  //przypisanie pozostalych blokow do nowej tablicy
        i++;
    }

    free(tab);

    return newTab;
}

// funkcja znajduje blok z suma o najblizszej do zadanej
char *closestSumD(char **tab, unsigned int blockSize, unsigned int tabSize, unsigned int sum){
    int index = -1;
    int tmp;
    int difference = INT_MAX;

    for(int i = 0; i < tabSize; i++){
        tmp = countSumD(tab[i], blockSize);
        if(abs(tmp - sum) < difference){
            difference = abs(tmp - sum);
            index = i;
        }
    }

    return tab[index];
}

// funkcja zlicza sume bloku
int countSumD(char *block, unsigned int blockSize){
    int s = 0;
    for(int i = 0; i < blockSize; i++){
        s += (int)block[i];
    }

    return s;
}

void genRandTabD(char **tab, unsigned int tabSize, unsigned int blockSize){
    srand((unsigned int)(time(NULL)));
    for(int i = 0; i < tabSize; i++)
        for(int j = 0; j < blockSize; j++){
            tab[i][j] = (char)(i*10 + j);
            //tab[i][j] = (char)(rand() % 127);  //granica rozmiaru signed char
        }

    return;
}

void printTab(char **tab, unsigned int tabSize, unsigned int blockSize){
    for(int i = 0; i < tabSize; i++) {
        for (int j = 0; j < blockSize; j++) {
            printf("%d, ", tab[i][j]);
        }
        printf("\n");
    }

    return;
}

void printBlock(char *block, unsigned int blockSize){
    printf("\n");
    for (int j = 0; j < blockSize; j++) {
        printf("%d, ", block[j]);
    }
    printf("\n");

    return;
}


