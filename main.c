
#include "stdio.h"
#include "stdlib.h"
#include "matrix.h"

#include "neuron.h"
#include "csv.h"

#define Assert(value) if (!(value)){ int *p= 0; *p = 0;}


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

    Neuron neuron;

    Matrix r;
    NeuronInitialize(&neuron, 2);
    neuron.lr=0.1;
    double  newWeights[]= {19,2};
    double  dataInputs[]= {4, 9};
    double  dataOutput = -1;

    NeuronUpdateWeightsFromArray(&neuron,newWeights);


    for (int i = 0; i < myCsvData.nrow; i++) {
        printf("Train\n");
        double  dataInputs[]= {atof(myCsvData.data[i][0]),atof(myCsvData.data[i][1])};
        NeuronTrain(&neuron, dataInputs, atof(myCsvData.data[i][2]));
    }
    /* inutil(); */
    printf("\n");
    printf("Input (%f,%f) Output %f",dataInputs[0],dataInputs[1],NeuronPredictFromArray(&neuron,dataInputs));

    /* TODO(accacio) free csvData */
    NeuronDelete(&neuron);
    exit(EXIT_SUCCESS);
    return 0;
}
