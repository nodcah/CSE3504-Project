#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"


int sort(TElement a, TElement b)
{
    return b < a;
}


int main(int argc, char **argv)
{
    printf("Check it out!\n");
    TMatrix *c = newMatrix(3, 3);
    for (unsigned int i = 0; i < c->nrow * c->ncol; i++)
        c->data[i/c->nrow][i%c->ncol] = i;
    printMatrix(c);
    printf("Sorting!\n");
    mergesort_row(c, 0, &sort);
    printMatrix(c);
    return 0;
}


TMatrix* fcfs(TMatrix *c)
{
    return NULL;
}


TMatrix* lrjf(TMatrix *c)
{
    return NULL;
}


TMatrix* heuristic(TMatrix *c)
{
    return NULL;
}
