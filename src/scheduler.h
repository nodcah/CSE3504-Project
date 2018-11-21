#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "utils/matrix.h"

/* Takes a thread cost matrix c and sorts it using the FCFS scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by FCFS.
 */
TMatrix* fcfs(const TMatrix *c);

/* Takes a thread cost matrix c and sorts it using the LRJF scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by LRJF.
 */
TMatrix* lrjf(const TMatrix *c);

/* Takes a thread cost matrix c and sorts it using the heuristic scheduling algorithm.
 * c - (3, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c scheduled by heuristic comparison algorithm.
 */
TMatrix* heuristic(const TMatrix *c);

/* Takes a thread cost matrix c and calculates the cost of actually executing the program
 * c - (4, n) Matrix representing PLJ, LASU, and RJ costs. n is the number of threads.
 * Returns c with execution times in 4th row.
 */
TMatrix* calculateCost(const TMatrix *c);

#endif
