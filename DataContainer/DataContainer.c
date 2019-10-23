//
// Created by Jason Torrence on 4/12/2019.
//

#include "DataContainer.h"

#include <stdlib.h>
//! Prototyping


/**
 * initDataContainer: creates a data container and returns a pointer to it
 *
 * @param  int sampleSize: used to describe the size of the results vector
 * @return struct * container
 */
struct DataContainer initDataContainer(int SampleSize){
    struct DataContainer container;
    container.matrix = NULL;
    container.resultsVector = (double*) calloc (SampleSize, sizeof(double));
    return container;
}

void destructDataContainer(DataContainer * data, int size){
    for(int i = 0; i < size; i++){
        free(data->matrix[i]);
    }
    free(data->matrix);
    free(data->resultsVector);
}
