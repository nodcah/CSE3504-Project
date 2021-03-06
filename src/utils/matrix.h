#ifndef __MATRIX_H__
#define __MATRIX_H__

#define TElement unsigned int 

#define max(a,b) (((a)>(b))?(a):(b))

// Define a Matrix structure for representing arbitrary size matrices.
typedef struct Matrix {
    unsigned int nrow;      // Number of columns.
    unsigned int ncol;      // Number of rows.
    unsigned int maxtime;   // Max finish time of any thread.
    TElement **data;        // 2D array of elements.
} TMatrix;

/* Creates a matrix and returns a pointer to it.
 * nrow - Number of rows.
 * ncol - Number of columns.
 * Will return NULL if it was unable to allocate memory.
 */
TMatrix* newMatrix(unsigned int nrow, unsigned int ncol);

/* Frees a previously allocated TMatrix. */
void freeMatrix(TMatrix *m);

/* Creates a matrix that is the sum of matrices m and n.
 * Will return NULL if it was unable to allocate memory for the new matrix or if the dimensions of m and n are incompatible.
 */
TMatrix* addMatrices(const TMatrix *m, const TMatrix *n);

/* Creates a matrix that is the product mn.
 * Will return NULL if it was unable to allocate memory for the new matrix or if the dimensions of m and n are incompatible.
 */
TMatrix* mulMatrices(const TMatrix *m, const TMatrix *n);

/* Creates the transpose of a matrix and returns it.
 * Returns NULL if the given matrix is NULL or if memory was unable to be allocated.
 */
TMatrix* transposeMatrix(const TMatrix *m);

/* Prints matrix m to stdout. */
void printMatrix(const TMatrix *m);

/*  Creates copy of matrix m 
 *  returns a newly-allocated matrix copy
 */
TMatrix* copyMatrix(const TMatrix *m);

/* Mergesorts matrix m through ordering rows by the sorting function sort.
 * m - Matrix to sort.
 * row - Row to sort matrix by.
 * sort - Boolean function to determine precedence. Should be of the form: int sort(TElement a, TElement b);
 */
TMatrix* mergesort_row(TMatrix *m, unsigned int row, int (*sort)(TElement a, TElement b));

#endif
