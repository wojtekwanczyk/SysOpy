//
// Created by Wojtek on 10.03.2018.
//

#include <limits.h>
#include <stdlib.h>
#include <time.h>


int countSumS(char *block, unsigned int blockSize){
    int s = 0;
    for(int i = 0; i < blockSize; i++){
        s += (int)block[i];
    }

    return s;
}


char *closestSumS(char **tab, unsigned int blockSize, unsigned int tabSize, unsigned int sum){
    int index = -1;
    int tmp;
    int difference = INT_MAX;

    for(int i = 0; i < tabSize; i++){
        tmp = countSumS(tab[i], blockSize);
        if(abs(tmp - sum) < difference){
            difference = abs(tmp - sum);
            index = i;
        }
    }

    return tab[index];
}



void genRandTabS(char **tab, unsigned int tabSize, unsigned int blockSize){
    srand((unsigned int)(time(NULL)));
    for(int i = 0; i < tabSize; i++)
        for(int j = 0; j < blockSize; j++){
            tab[i][j] = (char)(i*10 + j);
            //tab[i][j] = (char)(rand() % 127);  //granica rozmiaru signed char
        }
}
