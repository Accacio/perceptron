
#include "stdio.h"
#include "stdlib.h"
#include "matrix.h"




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
