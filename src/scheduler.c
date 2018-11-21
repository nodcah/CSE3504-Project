<<<<<<< HEAD
/* scheduler.c
 * Main file for running the scheduling program for LRJF, FCFS or heuristically.
 * Input: Either filename of .dat matrix file or # of threads (between 1-200) for random values
 * Output: Prints out run time of using FCFS, LRJF, and the hueristic approach
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"



int main(int argc, char* argv[]) {
    TMatrix* m;  // Input matrix

    // Parse input
    int nThreads = 1;
    int er = sscanf(argv[1], "%d", &nThreads);

    // If filetype given, read matrix from file
    if(!er) {  
        FILE* mFile = fopen(argv[1], "r");
        // TODO
        fclose(mFile);
    }
    // Otherwise, make random matrix of values based on nThreads
    else{
        if (nThreads<1 || nThreads>200){
            sprintf(err, "Please choose a number between 1 and 200");   
            exit(2);
        }
        m = newMatrix(3, nThreads);  // 3 rows, nThreads columns
        for (int row = 0; row < m->nrow; row++){
            for (int col = 0; col < m->ncol; col++) {
                m->data[row][col] = (TElement)(rand()*100.0+1.0); // Random number 1 to 100
            }
        }
    }

    printf("Running tests on matrix: ");
    printMatrix(m);  

    TMatrix* m_fcfs = fcfs(m);
    TMatrix* m_lrjf = lrjf(m);
    TMatrix* m_heuristic = heuristic(m);

    TMatrix* m_fcfs_cost = caluclateCost(m_fcfs); printMatrix(m_fcfs_cost);
    TMatrix* m_lrjf_cost = calculateCost(m_lrjf); printMatrix(m_lrjf_cost);
    TMatrix* m_heuristic_cost = calculateCost(m_heuristic); printMatrix(m_heruistic_cost);

    printf("FCFS Total Time: %d\n", m_fcfs_cost[3][m_fcfs_cost->ncols-1]);
    printf("LRJF Total Time: %d\n", m_lrjf_cost[3][m_lrjf_cost->ncols-1]);
    printf("Heuristic Total Time: %d\n", m_heuristic_cost[3][m_heurstic_cost->ncols-1]);
}


/* Takes a thread cost matrix c and sorts it using the FCFS scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by FCFS.
 */
TMatrix* fcfs(TMatrix *c){
    
}

/* Takes a thread cost matrix c and sorts it using the LRJF scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by LRJF.
 */
TMatrix* lrjf(TMatrix *c){

}

/* Takes a thread cost matrix c and sorts it using the heuristic scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by heuristic comparison algorithm.
 */
TMatrix* heuristic(TMatrix *c){

}

/* Takes a thread cost matrix c and calculates the cost of actually executing the program
 * c - (4, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c with execution times in 4th row
 */
TMatrix* calculateCost(TMatrix *c){

}
