
#include "stdio.h"
#include "stdlib.h"
#include "matrix.h"

#include "neuron.h"



    }


int main(int argc, char *argv[]) {

    Neuron neuron;

    Matrix r;
    NeuronInitialize(&neuron, 2);
    neuron.lr=0.1;
    double  newWeights[]= {19,2};
    double  dataInputs[]= {1, 2};
    double  dataOutput = -1;

    NeuronUpdateWeightsFromArray(&neuron,newWeights);

    for (int i = 0; i < 10; i++) {
        printf("Train\n");
        NeuronTrain(&neuron, dataInputs, dataOutput);
    }


    NeuronDelete(&neuron);
    exit(EXIT_SUCCESS);
}
