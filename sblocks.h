//
// Created by Wojtek on 10.03.2018.
//

#ifndef ZAD1_SBLOCKS_H
#define ZAD1_SBLOCKS_H


void addStaticBlock(unsigned int blockSize,unsigned int index,unsigned int tabSize);
void deleteStaticBlock(unsigned int blockSize, unsigned int index, unsigned int tabSize);
int countSumS(const char *block, unsigned int blockSize);
char *closestSumS(unsigned int blockSize, unsigned int tabSize, unsigned int sum);
void genRandTabS(unsigned int tabSize, unsigned int blockSize);
void printTabS(unsigned int tabSize, unsigned int blockSize);
void printBlockS(char *block, unsigned int blockSize);



extern char sTab[10000000];

#endif //ZAD1_SBLOCKS_H
