/* scheduler.c
 * Main file for running the scheduling program for LRJF, FCFS or heuristically.
 * Input: Either filename of .dat matrix file or # of threads (between 1-200) for random values
 * Output: Prints out run time of using FCFS, LRJF, and the hueristic approach
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scheduler.h"

int main(int argc, char* argv[]) {
    TMatrix* m=NULL;  // Input matrix

    // Parse input
    if (argc!=2){
        printf("Usage: scheduler [numThreads|pathToMatrix]\n");
        exit(0);
    }
    int nThreads = 1;
    int isNum = sscanf(argv[1], "%d", &nThreads);  // isNum>0 if argument is number

    // If filetype given, read matrix from file
    if(!isNum) {  
        FILE* mFile = fopen(argv[1], "r");
        // TODO
        fprintf(stderr, "Please enter a number\n");
        exit(1);
        fclose(mFile);
    }
    // Otherwise, make random matrix of values based on nThreads
    else{
        if (nThreads<1 || nThreads>200){
            fprintf(stderr, "Please choose a number between 1 and 200\n");   
            exit(2);
        }
        srand(time(NULL));
        m = newMatrix(3, nThreads);  // 3 rows, nThreads columns
        for (int row = 0; row < m->nrow; row++){
            for (int col = 0; col < m->ncol; col++) {
                m->data[row][col] = (TElement)(rand()%100+1); // Random number 1 to 100
            }
        }
    }

    printf("Running tests on matrix: \n");
    printMatrix(m);  
    printf("===============================\n");

    TMatrix* m_fcfs = fcfs(m);
    TMatrix* m_lrjf = lrjf(m);
    //TMatrix* m_heuristic = heuristic(m);

    TMatrix* m_fcfs_cost = calculateCost(m_fcfs); printMatrix(m_fcfs_cost);
    TMatrix* m_lrjf_cost = calculateCost(m_lrjf); printMatrix(m_lrjf_cost);
    //TMatrix* m_heuristic_cost = calculateCost(m_heuristic); printMatrix(m_heruistic_cost);
    printf("===============================\n");

    printf("FCFS Total Time: %d\n", m_fcfs_cost->maxtime);
    printf("LRJF Total Time: %d\n", m_lrjf_cost->maxtime);
    //printf("Heuristic Total Time: %d\n", m_heuristic_cost->maxtime);
    printf("\n");

    return 0;
}

int sortinc(TElement a,TElement b){ return a<b; }
int sortdec(TElement a,TElement b){ return a>b; }

/* Takes a thread cost matrix c and sorts it using the FCFS scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by FCFS.
 */
TMatrix* fcfs(TMatrix *c){
    TMatrix* ret = copyMatrix(c);
    mergesort_row(ret, 0, &sortinc);  // sorts such that row 0 is in increasing order
    return ret;
}

/* Takes a thread cost matrix c and sorts it using the LRJF scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by LRJF.
 */
TMatrix* lrjf(TMatrix *c){
    TMatrix* ret = copyMatrix(c);
    mergesort_row(ret, 2, &sortdec);  // sorts such that row 2 is decreasing
    return ret;
}

/* Takes a thread cost matrix c and sorts it using the heuristic scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by heuristic comparison algorithm.
 */
TMatrix* heuristic(TMatrix *c){
    // TODO
    return NULL;
}

/* Takes a thread cost matrix c and calculates the cost of actually executing the program
 * c - (4, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c with execution times in 4th row
 */
TMatrix* calculateCost(TMatrix *c){
    TMatrix* ret = newMatrix(4, c->ncol);  // return matrix

    // Calculate run time cost in order of columns
    int startAt=c->data[0][0];  // keeps track of when thread leaves the LASU 
    for (int col=0; col<ret->ncol; col++){ 
        for (int row=0; row<3; row++){
            ret->data[row][col]=c->data[row][col];
        }
        startAt = ((max(startAt,c->data[0][col])) + c->data[1][col]);
        ret->data[3][col] = startAt+c->data[2][col];
        if (ret->data[3][col] > ret->maxtime) 
            ret->maxtime = ret->data[3][col];
    }
    return ret;
}
