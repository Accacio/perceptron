
#include "stdio.h"
#include "stdlib.h"
#include "matrix.h"

#include "neuron.h"



    }


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
