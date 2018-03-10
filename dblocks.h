//
// Created by Wojtek on 10.03.2018.
//

#ifndef ZAD1_DBLOCKS_H
#define ZAD1_DBLOCKS_H

#endif //ZAD1_DBLOCKS_H


char **createDynamicTable(unsigned int tabSize, unsigned int blockSize);
void deleteDynamicTable(char **tab, int unsigned tabSize);
char **addDynamicBlock(char **tab,unsigned int blockSize,unsigned int index,unsigned int tabSize);
char **deleteDynamicBlock(char **tab,unsigned int blockSize, unsigned int index, unsigned int tabSize);
char *closestSum(char **tab, unsigned int blockSize, unsigned int tabSize, unsigned int sum);
int countSum(char *block, unsigned int blockSize);
void genRandTab(char **tab, unsigned int tabSize, unsigned int blockSize);

