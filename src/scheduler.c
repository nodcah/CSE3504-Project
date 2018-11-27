/* scheduler.c
 * Main file for running the scheduling program for LRJF or  FCFS.
 * Input: # of threads (between 1-200) for random values and optional conditions on the values
 * Output: Prints out run time of using FCFS and LRJF
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scheduler.h"

int main(int argc, char* argv[]) {
    TMatrix* m = NULL;  // Input matrix

    // Parse input
    if (argc<2 || argc>5){
        printf("Usage: scheduler numThreads [.|=] [.|=] [.|=]\n");
        exit(0);
    }
    int nThreads = 1;
    sscanf(argv[1], "%d", &nThreads);  // isNum>0 if argument is number
    int plj_eq = 0;  // if the Pre Lock Job times should be equal
    int lasu_eq = 0;  // if the Locked Access Shared Unit should be equal
    int rj_eq = 0;  // if the Remaining Job times should be equal

    // If there are conditions, note them
    if (argc==5){
        if(!strcmp(argv[2],"=")) plj_eq=1;
        if(!strcmp(argv[3],"=")) lasu_eq=1;
        if(!strcmp(argv[4],"=")) rj_eq=1;
    }

    // Otherwise, make random matrix of values based on nThreads
    if (nThreads<1 || nThreads>200){
        fprintf(stderr, "Please choose a number between 1 and 200\n");   
        exit(2);
    }
    srand(time(NULL));
    m = newMatrix(3, nThreads);  // 3 rows, nThreads columns
    TElement temp_plj = (rand()%100);
    TElement temp_lasu = (rand()%100);
    TElement temp_rj = (rand()%100);
    for (int row = 0; row < m->nrow; row++){
        for (int col = 0; col < m->ncol; col++) {
            m->data[row][col] = (TElement)(rand()%100);  // Random number 1 to 100
            if (plj_eq && row==0) m->data[row][col] = temp_plj;  // Same plj
            if (lasu_eq && row==1) m->data[row][col] = temp_lasu;  // Same lasu
            if (rj_eq && row==2) m->data[row][col] = temp_rj;  // Same rj
        }
    }

    printf("Running tests for %d threads and configuration %s %s %s\n", nThreads, 
            ((plj_eq)?"=":"."),((lasu_eq)?"=":"."), ((rj_eq)?"=":"."));
    //printMatrix(m);  
    //printf("==========================================\n");
    
    clock_t t0 = clock();
    TMatrix* m_fcfs = fcfs(m);
    clock_t t1 = clock();
    TMatrix* m_lrjf = lrjf(m);
    clock_t t2 = clock();

    TMatrix* m_fcfs_cost = calculateCost(m_fcfs); //printMatrix(m_fcfs_cost); printf("\n");
    TMatrix* m_lrjf_cost = calculateCost(m_lrjf); //printMatrix(m_lrjf_cost);printf("\n");
    //printf("==========================================\n");

    printf("FCFS Total Time: %d, Time to schedule the %d threads: %d us\n", m_fcfs_cost->maxtime, nThreads, (int)((double)(t1-t0)/CLOCKS_PER_SEC*1000000));
    printf("LRJF Total Time: %d, Time to schedule the %d threads: %d us\n", m_lrjf_cost->maxtime, nThreads, (int)((double)(t2-t1)/CLOCKS_PER_SEC*1000000));    
    printf("\n");

    return 0;
}


int sortinc(TElement a,TElement b) { return a<b; }
int sortdec(TElement a,TElement b) { return a>b; }


/* Takes a thread cost matrix c and sorts it using the FCFS scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by FCFS.
 */
TMatrix* fcfs(const TMatrix *c){
    TMatrix* ret = copyMatrix(c);
    mergesort_row(ret, 0, &sortinc);  // sorts such that row 0 is in increasing order
    return ret;
}


/* Takes a thread cost matrix c and sorts it using the LRJF scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by LRJF.
 */
TMatrix* lrjf(const TMatrix *c){
    TMatrix* ret = copyMatrix(c);
    mergesort_row(ret, 2, &sortdec);  // sorts such that row 2 is decreasing
    return ret;
}


/* Takes a thread cost matrix c and calculates the cost of actually executing the program
 * c - (4, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c with execution times in 4th row
 */
TMatrix* calculateCost(const TMatrix *c){
    TMatrix* ret = newMatrix(4, c->ncol);  // return matrix
    for (int row = 0; row < c->nrow; row++) {
        for (int col = 0; col < c->ncol; col++) {
            ret->data[row][col] = c->data[row][col];
        }
    }

    // Calculate run time cost in order of columns
    int startAt=0;  // keeps track of when thread leaves the LASU 
    for (int col=0; col<ret->ncol; col++){ 
        startAt = max(startAt, ret->data[0][col]) + ret->data[1][col];
        ret->data[3][col] = startAt + ret->data[2][col];
        if (ret->data[3][col] > ret->maxtime) 
            ret->maxtime = ret->data[3][col];
    }
    return ret;
}
