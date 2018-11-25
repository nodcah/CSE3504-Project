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
    m->maxtime = 0;
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
            printf("%u\t", m->data[i][j]);
        }
        printf("\n");
    }
}


TMatrix* copyMatrix(const TMatrix *m) {
    TMatrix* ret = newMatrix(m->nrow, m->ncol);
    for (unsigned int i = 0; i < m->nrow; i++) {
        for (unsigned int j = 0; j < m->ncol; j++) {
            ret->data[i][j] = m->data[i][j];
        }
    }
    return ret;
}


/* Merge matrices a and b into dst according to sort. */
TMatrix* merge(TMatrix *dst, TMatrix *a, TMatrix *b, unsigned int row, int (*sort)(TElement a, TElement b))
{
    // Sanity checks.
    if (dst == NULL) {
        return dst;
    } else if (a == NULL) {
        // Assign dst to b if compatible.
        if (dst->nrow == b->nrow && dst->ncol == b->ncol) {
            *dst = *b;
        }
        return dst;
    } else if (b == NULL) {
        // Assign dst to a if compatible.
        if (dst->nrow == a->nrow && dst->ncol == a->ncol) {
            *dst = *a;
        }
        return dst;
    } else if (dst->nrow != a->nrow || dst->nrow != b->nrow) {
        return dst;     // Unequal rows. Do nothing.
    } else if (dst->ncol != a->ncol + b->ncol) {
        return dst;     // Columns do not sum to be the number in dst. Do nothing.
    }

    unsigned int idx_a = 0;
    unsigned int idx_b = 0;
    for (unsigned int i = 0; i < dst->ncol; i++) {
        if (idx_a >= a->ncol) {
            // We've already inserted all of matrix a. Simply add matrix b.
            for (unsigned int r = 0; r < dst->nrow; r++)
                dst->data[r][i] = b->data[r][idx_b];
            idx_b++;
        } else if (idx_b >= b->ncol) {
            // We've already inserted all of matrix b. Simply add matrix a.
            for (unsigned int r = 0; r < dst->nrow; r++)
                dst->data[r][i] = a->data[r][idx_a];
            idx_a++;
        } else {
            if (sort(a->data[row][idx_a], b->data[row][idx_b])) {
                // Column in a comes before column in b.
                for (unsigned int r = 0; r < dst->nrow; r++)
                    dst->data[r][i] = a->data[r][idx_a];
                idx_a++;
            } else {
                // Column in b comes before column in a.
                for (unsigned int r = 0; r < dst->nrow; r++)
                    dst->data[r][i] = b->data[r][idx_b];
                idx_b++;
            }
        }
    }

    return dst;
}


TMatrix* mergesort_row(TMatrix *m, unsigned int row, int (*sort)(TElement a, TElement b))
{
    // Cannot sort a NULL Matrix, a matrix with 0 rows, an invalid row selection, or a matrix with 1 column or less.
    if (m == NULL || m->nrow == 0 || row >= m->nrow || m->ncol < 2)
        return m;

    unsigned int mid = m->ncol / 2;     // Find the midpoint.
    TMatrix *a = newMatrix(m->nrow, mid);
    TMatrix *b = newMatrix(m->nrow, m->ncol - mid);
    // Populate each of the submatrices.
    for (unsigned int i = 0; i < a->nrow; i++)
        for (unsigned int j = 0; j < a->ncol; j++)
            a->data[i][j] = m->data[i][j];
    for (unsigned int i = 0; i < b->nrow; i++)
        for (unsigned int j = 0; j < b->ncol; j++)
            b->data[i][j] = m->data[i][mid+j];
    // Recursively mergesort.
    mergesort_row(a, row, sort);
    mergesort_row(b, row, sort);
    merge(m, a, b, row, sort);

    freeMatrix(a);
    freeMatrix(b);
    return m;
}
