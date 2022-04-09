#ifndef __CSV_H_
#define __CSV_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct {
    unsigned int nrow, ncol;
    char *** data; // 3D array ** to string
} CSVData;

void CSVprintData(CSVData csvData){
    int i, j;
    for (i=0; i < csvData.nrow; i++) {
        for (j=0; j < csvData.ncol-1; j++) {
            printf("%s\t ",csvData.data[i][j]);
        }
            printf("%s\n",csvData.data[i][j]);
    }
}


int CSVgetColumns(char * filename){
    FILE * stream = fopen(filename, "r");
    if (!stream) {
        fprintf(stderr,"%s:%d: %s failed\n", __FILE__,__LINE__,__func__);
        return -1;
    }
    char c;
    int nCols = 0;
    while( (c = fgetc(stream)) != '\n')
    {
        switch(c)
        {
            case ';':
                nCols++;
                break;
            default:
                break;
        }
    }
    nCols++;

    fclose(stream);
    return nCols;
}

int CSVread(char * filename,CSVData * csvData){

    FILE * stream = fopen(filename, "r");
    if (!stream) {
        fprintf(stderr,"%s:%d: %s failed\n", __FILE__,__LINE__,__func__);
        return 1;
    }
    rewind(stream); // begin in first line

    char str[128]; // 128 char should suffice
    unsigned int currentLine=1;
    unsigned int currentColumn=1;
    unsigned int vcpm=0; //value character marker

    char c;

    while( (c = fgetc(stream)) != EOF && currentLine <= csvData->nrow  ) {
        switch(c)
        {
            case ';':
                str[vcpm] = '\0'; /* finish character */
                /* add to array */
                strcpy(csvData->data[currentLine-1][currentColumn-1], str);

                vcpm = 0;
                currentColumn++;
                break;
            case '\n':
                str[vcpm] = '\0';

                strcpy(csvData->data[currentLine-1][currentColumn-1], str);

                currentLine++;
                vcpm = 0;
                currentColumn=1;
                break;
            default:
                str[vcpm] = c;
                vcpm++;
                break;
        }
    }

    return 0;
}
/* TODO(accacio) should return value */
void CSVallocateData(CSVData * data,unsigned int nchar){
    data->data = (char***) malloc(data->nrow*sizeof(char**));
    for (int i = 0; i < data->nrow; i++) {
        data->data[i] = (char**) malloc(data->ncol*sizeof(char*));
        for (int j = 0; j < data->ncol; j++) {
        data->data[i][j] = (char*) malloc(nchar);
        }
    }
}


#endif // __CSV_H_
