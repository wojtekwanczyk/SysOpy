//
// Created by Wojtek on 10.03.2018.
//

#ifndef ZAD1_DBLOCKS_H
#define ZAD1_DBLOCKS_H

char **createDynamicTableC(unsigned int tabSize, unsigned int blockSize);
char **createDynamicTableM(unsigned int tabSize, unsigned int blockSize);
void deleteDynamicTable(char **tab, int unsigned tabSize);
char **addDynamicBlock(char **tab,unsigned int blockSize,unsigned int index,unsigned int tabSize);
char **deleteDynamicBlock(char **tab,unsigned int blockSize, unsigned int index, unsigned int tabSize);
char *closestSumD(char **tab, unsigned int blockSize, unsigned int tabSize, unsigned int sum);
int countSumD(char *block, unsigned int blockSize);
void genRandTabD(char **tab, unsigned int tabSize, unsigned int blockSize);
void printTab(char **tab, unsigned int tabSize, unsigned int blockSize);
void printBlock(char *block, unsigned int blockSize);


#endif //ZAD1_DBLOCKS_H

