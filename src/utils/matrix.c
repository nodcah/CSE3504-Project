#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"


TMatrix* newMatrix(unsigned int nrow, unsigned int ncol)
{
    if (!nrow || !ncol)
        return NULL;

    // Allocate memory for the structure.
    TMatrix *m = malloc(sizeof(TMatrix));
    // Allocate memory for its elements.
    TElement **data = malloc(sizeof(TElement*) * nrow);
    TElement *elements = calloc(nrow * ncol, sizeof(TElement));

    // Assert that memory was allocated.
    if (m == NULL || data == NULL || elements == NULL) {
        free(elements);
        free(data);
        free(m);
        return NULL;
    }

    // Populate the array.
    for (unsigned int i = 0; i < nrow; i++) {
        data[i] = elements + i * ncol;
    }

    // Initialize the matrix and return it.
    m->nrow = nrow;
    m->ncol = ncol;
    m->data = data;
    return m;
}


void freeMatrix(TMatrix *m)
{
    if (m == NULL)
        return;

    free(m->data[0]);   // Free the element array.
    free(m->data);
    free(m);            // Free the structure itself.
}


TMatrix* addMatrices(const TMatrix *m, const TMatrix *n)
{
    // Assert that the matrices m and n are compatibile.
    if (m == NULL || n == NULL || m->nrow != n->nrow || m->ncol != n->ncol)
        return NULL;

    // Instantiate the result matrix and assert that it has been allocated.
    TMatrix *t = newMatrix(m->nrow, m->ncol);
    if (t == NULL)
        return t;

    // Sum matrices m and n elementwise.
    for (unsigned int i = 0; i < t->nrow; i++)
        for (unsigned int j = 0; j < t->ncol; j++)
            t->data[i][j] = m->data[i][j] + n->data[i][j];

    return t;
}


TMatrix* mulMatrices(const TMatrix *m, const TMatrix *n)
{
    // Assert that the matrices m and n are compatible.
    if (m == NULL || n == NULL || m->ncol != n->nrow)
        return NULL;

    // Instantiate the result matrix and assert that it has been allocated.
    TMatrix *t = newMatrix(m->nrow, n->ncol);
    if (t == NULL)
        return t;

    // Iterate over the result matrix and perform dot products to compute result.
    for (unsigned int i = 0; i < t->nrow; i++) {
        for (unsigned int j = 0; j < t->ncol; j++) {
            TElement sum = (TElement) 0;
            for (unsigned int k = 0; k < m->ncol; k++)
                sum += m->data[i][k] * n->data[k][j];
            t->data[i][j] = sum;
        }
    }

    return t;
}


TMatrix* transposeMatrix(const TMatrix *m)
{
    if (m == NULL)
        return NULL;

    // Instantiate the result matrix and assert that it has been allocated.
    TMatrix *t = newMatrix(m->ncol, m->nrow);
    if (t == NULL)
        return t;

    // Iterate over the given matrix and swap rows and columns.
    for (unsigned int i = 0; i < m->nrow; i++)
        for (unsigned int j = 0; i < m->ncol; j++)
            t->data[j][i] = m->data[i][j];

    return t;
}


void printMatrix(const TMatrix *m)
{
    for (unsigned int i = 0; i < m->nrow; i++) {
        for (unsigned int j = 0; j < m->ncol; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}
