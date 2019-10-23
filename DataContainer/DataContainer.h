//
// Created by Jason Torrence on 4/12/2019.
//

#ifndef MATRIXANDRETURNS_H
#define MATRIXANDRETURNS_H

typedef struct DataContainer{
    double ** matrix;
    double * resultsVector;
}DataContainer;

struct DataContainer initDataContainer(int sampleSize);

void destructDataContainer(DataContainer * data, int size);
#endif //MATRIXANDRETURNS_H
