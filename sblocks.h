//
// Created by Wojtek on 10.03.2018.
//

#ifndef ZAD1_SBLOCKS_H
#define ZAD1_SBLOCKS_H


char *closestSumS(char **tab, unsigned int blockSize, unsigned int tabSize, unsigned int sum);
int countSumS(char *block, unsigned int blockSize);
void genRandTabS(char **tab, unsigned int tabSize, unsigned int blockSize);


int blockTab[1000][100];

#endif //ZAD1_SBLOCKS_H
