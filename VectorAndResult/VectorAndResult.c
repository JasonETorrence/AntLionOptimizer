//
// Created by torrencej on 4/12/2019.
//

#include "VectorAndResult.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * initVectorAndResult: creates and returns a VectorAndResult struct
 *
 * @param  double * vector: the vector to be placed in the struct
 * @param  double result: rhe result (Most of the time, it's the result of the vector)
 * @return struct VectorAndResult containing all the params
 */
struct VectorAndResult initVectorAndResult(double *vector, double result) {

    struct VectorAndResult Var;

    Var.vector = vector;
    Var.result = result;

    return Var;
}

/**
 * initEmptyVectorAndResult: creates and returns an empty VectorAndResult struct
 *
 * @param  int size: size of the vector that's to be contained in the struct
 * @return an empty VectorAndResult.
 */
struct VectorAndResult initEmptyVectorAndResult(int size) {

    struct VectorAndResult Var;

    Var.vector = (double *) calloc (size, sizeof(double));
    Var.result = 0.0;

    return Var;
}

/**
 * copyVectorAndResult: copies a VectorAndResult object and returns a new one
 *
 * @param  VectorAndResult x: the VectorAndResult struct to be copied
 * @return a copy of the argument VectorAndResult struct.
 */
struct VectorAndResult copyVectorAndResult(VectorAndResult x, int size) {
    struct VectorAndResult copy = initVectorAndResult((double *) calloc(size, sizeof(double)), x.result);
    for(int i = 0; i < size; i++){
        copy.vector[i] = x.vector[i];
    }
    copy.result = x.result;

    return copy;
}

