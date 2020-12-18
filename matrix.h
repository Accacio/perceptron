#ifndef __MATRIX_H_
#define __MATRIX_H_

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int nrow, ncol;
    double ** data;
} Matrix;

void initializeMatrix(Matrix * m, int nrow, int ncol){
    double**data = malloc(nrow*sizeof(double*));
    for (int i = 0; i < nrow; i++) {
        data[i] = calloc(ncol, sizeof(double)); //contiguos
    }
    m->ncol = ncol;
    m->nrow = nrow;
    m->data = data;
}


void MatrixDelete(Matrix * m){
    for (int i = 0; i < m->nrow; i++) {
        free(m->data[i]);
    }
    free(m->data);
}

int MatrixMulti(Matrix a, Matrix b, Matrix * r){
    if (a.ncol!=b.nrow) {
        printf("Matrix dimensions mismatch\n");
        return -1;
    }
    if (r->ncol!=b.ncol || r->nrow!=a.nrow) {
        printf("Result Matrix dimensions mismatch");
        return -1;
    }

    /* Multiply */
    for (int c = 0; c < a.nrow; c++) {
        for (int d = 0; d < b.ncol; d++) {
            for (int k = 0; k < b.nrow; k++) {
                r->data[c][d] += a.data[c][k]*b.data[k][d];
            }
        }
    }
    return 0;
}

int  MatrixMultiTransposeTimesNormal(Matrix a, Matrix b, Matrix * r){
    if (a.nrow!=b.nrow) {
        printf("Matrix dimensions mismatch\n");
        return -1;
    }
    if (r->ncol!=b.ncol || r->nrow!=a.ncol) {
        printf("Result Matrix dimensions mismatch");
        return -1;
    }

    /* Multiply */
    for (int c = 0; c < a.ncol; c++) {
        for (int d = 0; d < b.ncol; d++) {
            for (int k = 0; k < b.nrow; k++) {
                r->data[c][d] += a.data[k][c]*b.data[k][d];
            }
        }
    }
    return 0;
}

void MatrixCopyFromArray(Matrix * m, double * input){
    for (int i = 0; i < m->nrow; i++) {
        for (int j=0; j < m->ncol; j++) {
            m->data[i][j] = *(input+i*m->ncol+j);
        }
    }
}

void printMatrix(Matrix a){
    for (int i = 0; i < a.nrow; i++) {
    for (int j = 0; j < a.ncol; j++) {
        printf("%f ", a.data[i][j]);
    }
    printf("\n");
    }
}


#endif // __MATRIX_H_
