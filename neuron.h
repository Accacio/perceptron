#ifndef __NEURON_H_
#define __NEURON_H_

#include "matrix.h"

typedef struct {
    Matrix w;
    Matrix u;
    double b;
    double y;
    double lr;
} Neuron ;

void NeuronInitialize(Neuron * neuron, int nInputs){
    MatrixInitialize(&neuron->w, nInputs, 1);
    MatrixInitialize(&neuron->u, nInputs, 1);
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
    double out = in > 0 ? 1 : -1; // Step function
    /* double out = in; */
    return out;
}

/* double NeuronPredict(Neuron * neuron){ */
/*     Matrix r; */
/*     MatrixInitialize(&r, neuron->w.ncol, neuron->u.ncol); */
/*     MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r); */
/*     neuron->y=NeuronActivation(**r.data + neuron->b); */
/*     MatrixDelete(&r); */
/*     return neuron->y; */
/* } */
double NeuronPredict(Neuron * neuron, Matrix input){
    Matrix r;
    neuron->u = input;
    MatrixInitialize(&r, neuron->w.ncol, neuron->u.ncol);
    MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r);
    neuron->y=NeuronActivation(**r.data + neuron->b);
    MatrixDelete(&r);
    return neuron->y;
}

double NeuronPredictFromArray(Neuron * neuron, double * input){
    Matrix r;
    MatrixCopyFromArray(&(neuron->u), input);
    /* neuron->u = input; */
    MatrixInitialize(&r, neuron->w.ncol, neuron->u.ncol);
    MatrixMultiTransposeTimesNormal(neuron->w, neuron->u, &r);
    neuron->y=NeuronActivation(**r.data + neuron->b);
    MatrixDelete(&r);
    return neuron->y;
}

void NeuronUpdateWeightsFromArray(Neuron * neuron, double * input){
    MatrixCopyFromArray(&(neuron->w), input);
}


void NeuronTrain(Neuron * neuron, double * input, double target){
    /* printf("target: %f\n", target); */
    double prediction = NeuronPredictFromArray(neuron, input);
    /* printf("prediction: %f\n", prediction); */
    double error = target-prediction;
    /* printf("error: %f\n", error); */
    for (int i =0; i < neuron->w.nrow; i++) {
        /* printf("i: %d\n", i); */
        /* printf("oldW: %f\n",neuron->w.data[i][0]); */
        neuron->w.data[i][0] += neuron->lr*error*input[i];
        /* printf("newW: %f\n",neuron->w.data[i][0]); */

    }
    neuron->b += neuron->lr*error;

    printf("weights:\n");
    printMatrix(neuron->w);
    printf("bias: %f\n", neuron->b);
    printf("error: %f\n", error);
    /* neuron->u = ; */
}


#endif // __NEURON_H_
