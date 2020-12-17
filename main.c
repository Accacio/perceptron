#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int nrow, ncol;
    double ** data;
} Matrix;

void initializeMatrix(Matrix * m, int nrow, int ncol){
    double**data = malloc(nrow*sizeof(double*));
    for (int i = 0; i < nrow; i++) {
        data[i] = calloc(ncol, sizeof(double));
    }
    m->ncol = ncol;
    m->nrow = nrow;
    m->data = data;
}


void MatrixDelete(Matrix * m){
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

typedef struct {
    Matrix w;
    Matrix u;
    double b;
    double y;
    double lr;
    int nw;
} Neuron ;

void NeuronInitialize(Neuron * neuron, int nInputs){
    initializeMatrix(&neuron->w, nInputs, 1);
    initializeMatrix(&neuron->u, nInputs, 1);
    neuron->b = 0;
    neuron->lr = 0.1;
}
void NeuronDelete(Neuron * neuron){
    MatrixDelete(&neuron->w);
    MatrixDelete(&neuron->u);
    neuron->b = 0;
}
double NeuronActivation(double in) {

    /* double out = in > 0 ? 1 : -1; // Step function */
    /* double out = in > 0 ? 1 : -1; // Step function */
    double out = in;
    return out;
}

/* double NeuronPredict(Neuron * neuron){ */
/*     Matrix r; */
/*     initializeMatrix(&r, neuron->w.ncol, neuron->u.ncol); */
/*     MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r); */
/*     neuron->y=NeuronActivation(**r.data + neuron->b); */
/*     MatrixDelete(&r); */
/*     return neuron->y; */
/* } */
double NeuronPredict(Neuron * neuron, Matrix input){
    Matrix r;
    neuron->u = input;
    initializeMatrix(&r, neuron->w.ncol, neuron->u.ncol);
    MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r);
    neuron->y=NeuronActivation(**r.data + neuron->b);
    MatrixDelete(&r);
    return neuron->y;
}

double NeuronPredictFromArray(Neuron * neuron, double * input){
    Matrix r;
    MatrixCopyFromArray(&(neuron->u), input);
    /* neuron->u = input; */
    initializeMatrix(&r, neuron->w.ncol, neuron->u.ncol);
    MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r);
    neuron->y=NeuronActivation(**r.data + neuron->b);
    MatrixDelete(&r);
    return neuron->y;
}

void NeuronUpdateWeightsFromArray(Neuron * neuron, double * input){
    MatrixCopyFromArray(&(neuron->w), input);
}


/* void NeuronTrain(Neuron * neuron, double * input, double target){ */
/*   neuron->u = ; */
/* } */

int main(int argc, char *argv[]) {

    Neuron neuron;

    Matrix r;
    NeuronInitialize(&neuron, 2);

    double  newWeights[]= {1.9,6};
    double  doubleInput[]= {1, 2};

    NeuronUpdateWeightsFromArray(&neuron,newWeights);
    NeuronPredictFromArray(&neuron,doubleInput);

    printf("u:\n");
    printMatrix(neuron.u);

    printf("w:\n");
    printMatrix(neuron.w);

    printf("   T  \n");
    printf("r=w u:\n");
    printf("%f\n",neuron.y);

    NeuronDelete(&neuron);
    return 0;
}
