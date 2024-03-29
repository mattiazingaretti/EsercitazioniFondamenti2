#include <stdio.h>
#include "bst.h"
#include <time.h>
#include <stdlib.h>

#define N 200
#define MAXCOORD 1000

double rnd(double top) {
    double r = 2*(double)rand() / RAND_MAX  - 1;
    return r*top;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));   // should only be called once

    bst *b = newBST();
    insert(b, 5, 0);
    insert(b, 2, 0);
    insert(b, 8, 0);
    insert(b, 1, 0);
    insert(b, 3, 0);
    insert(b, 6, 0);
    insert(b, 11, 0);
    insert(b, 1, 0);
    insert(b, 0, 5);
    insert(b, 0, 6);
    insert(b, 0, -5);
    insert(b, 0, 6);


    print(b);

       float radiusTest [11][2] = {
            {0, 0},
            {2, 2},
            {2, 6},
            {3, 0},
            {0, 3},
            {0, 4},
            {2, 4},
            {3, 5},
            {2, 3},
            {2, 7},
            {4, 3}
        };



    printf("\nRicerca nodi in corona: \n");
    for(int i = 0; i < 11; i++) {
        printf("corona: r1=%f, r2= %f: nodi=%d\n",radiusTest[i][0],radiusTest[i][1],corona(b,radiusTest[i][0],radiusTest[i][1]));
    }
    printf("max area = %g\n", maxCorona(b));

    bst *b1 = newBST();
    insert(b1, 1, 4);
    insert(b1, -6, 6);
    insert(b1, 3, 4);
    insert(b1, 5, 1);
    insert(b1, 6, -4);
    insert(b1, 4, 1);
    insert(b1, 2, 7);
    insert(b1, 2, 2);
    insert(b1, 8, 1);
    insert(b1, -1, 4);
    insert(b1, 6, 2);
    insert(b1, -8, 7);
    insert(b1, 1, -1);
    insert(b1, 8, -1);
    insert(b1, 8, -1);
    insert(b1, 0, 5);
    insert(b1, 2, 2);

    print(b1);

    printf("\nRicerca nodi in corona: \n");
    for(int i = 0; i < 11; i++) {
        printf("corona: r1=%f, r2= %f: nodi=%d\n",radiusTest[i][0],radiusTest[i][1],corona(b1,radiusTest[i][0],radiusTest[i][1]));
    }
    printf("max area = %g\n", maxCorona(b1));






    return 0;
}
