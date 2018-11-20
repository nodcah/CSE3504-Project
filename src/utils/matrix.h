#ifndef __MATRIX_H__
#define __MATRIX_H__

#define TElement    double

// Define a Matrix structure for representing arbitrary size matrices.
typedef struct Matrix {
    unsigned int nrow;      // Number of columns.
    unsigned int ncol;      // Number of rows.
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

void printMatrix(const TMatrix *m);

#endif
