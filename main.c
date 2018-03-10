#include <stdio.h>
#include <stdlib.h>
#include "dblocks.h"


unsigned int blockSize = 10;
unsigned int tabSize = 10;


int main() {


    char **tab = createDynamicTable(tabSize,blockSize);

    genRandTabD(tab, tabSize, blockSize);



    //tab = addDynamicBlock(tab, blockSize, 2, tabSize);
    //tabSize++;

    //tab = deleteDynamicBlock(tab, blockSize, 3, tabSize);
    //tabSize--;


    for(int i = 0;  i < tabSize ; i++){
        for(int j = 0; j < blockSize; j++){
            printf("%d, ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");


   /*
    char *p = closestSumD(tab,blockSize,tabSize,1000);

    for(int i=0; i< blockSize; i++){
        printf("%d, ", p[i]);
    }
*/

    deleteDynamicTable(tab, tabSize);

    return 0;
}


