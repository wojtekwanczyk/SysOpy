//
// Created by Wojtek on 10.03.2018.
//

#include <limits.h>
#include <stdlib.h>
#include <time.h>
//#include <printf.h>
#include <stdio.h>

char sTab[10000000];

void addStaticBlock(unsigned int blockSize,unsigned int index,unsigned int tabSize){
    if(index > tabSize - 1){
        printf("Indeks poza tablica");
        return;
    }

    srand((unsigned int)(time(NULL)));

    int id = blockSize * index;
    if(id > tabSize * blockSize)
        return;

    for(int i=0; i < blockSize; i++){
        sTab[blockSize * index + i] = (char)(rand() % 127);
    }

}


void deleteStaticBlock(unsigned int blockSize, unsigned int index, unsigned int tabSize){
    if(index > tabSize - 1){
        printf("Indeks poza tablica");
        return;
    }

    int id = blockSize * index;
    if(id > tabSize * blockSize)
        return;

    for(int i=0; i < blockSize; i++){
        sTab[blockSize * index + i] = 0;
    }
}


int countSumS(const char *block, unsigned int blockSize){
    int s = 0;
    for(int i = 0; i < blockSize; i++){
        s += (int)block[i];
    }

    return s;
}


char *closestSumS(unsigned int blockSize, unsigned int tabSize, unsigned int sum){
    int index = -1;
    int tmp;
    int difference = INT_MAX;

    for(int i = 0; i < tabSize; i++){
        tmp = countSumS(&sTab[i], blockSize);
        if(abs(tmp - sum) < difference){
            difference = abs(tmp - sum);
            index = i;
        }
    }

    return &sTab[index];
}



void genRandTabS(unsigned int tabSize, unsigned int blockSize){
    srand((unsigned int)(time(NULL)));
    for(int i = 0; i < tabSize * blockSize; i++)
        sTab[i] = (char)(rand() % 127);
    //tab[i][j] = (char)(rand() % 127);  //granica rozmiaru signed char}
}


void printTabS(unsigned int tabSize, unsigned int blockSize){
    for(int i = 0; i < tabSize; i++) {
        for (int j = 0; j < blockSize * tabSize; j++) {
            printf("%d, ", sTab[i]);
        }
        printf("\n");
    }

    return;
}

void printBlockS(char *block, unsigned int blockSize){
    printf("\n");
    for (int j = 0; j < blockSize; j++) {
        printf("%d, ", block[j]);
    }
    printf("\n");

    return;
}
