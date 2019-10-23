//
// Created by Jason Torrence on 4/12/2019.
//

#ifndef ALGORITHMS_VECTORANDRESULT_H
#define ALGORITHMS_VECTORANDRESULT_H

typedef struct VectorAndResult{
    double * vector;
    double result;
}VectorAndResult;

struct VectorAndResult initVectorAndResult(double *vector, double result);

struct VectorAndResult copyVectorAndResult(VectorAndResult x, int size);

#endif //VECTORANDRESULT_H
