
#include "stdio.h"
#include "stdlib.h"
#include "matrix.h"

#include "neuron.h"
#include "csv.h"


int main(int argc, char *argv[]) {
    CSVData myCsvData;
    myCsvData.ncol = CSVgetColumns(argv[1]);
    myCsvData.nrow = 5;

    CSVallocateData(&myCsvData,128);

    int success = CSVread(argv[1],&myCsvData);
    if (success!=0){
        printf("Exiting\n");
        exit(EXIT_FAILURE);
    }

    CSVprintData(myCsvData);

    return 0;

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

    /* TODO(accacio) free csvData */
    NeuronDelete(&neuron);
    exit(EXIT_SUCCESS);
}
