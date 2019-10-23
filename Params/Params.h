//
// Created by Jason Torrence on 3/29/2019.
//
// This is a struct simply designed to pull in information from a file (Data.txt) and store it.
//
// Originally designed to work with algorithms for the purpose of storing parameters.
//
// Email: torrencej@cwu.edu
//

#ifndef PARAMS_H
#define PARAMS_H

typedef struct Params{

    int swarmSize;
    int numOfAntLions;
    int iterations;
    int particleSize;
    int numOfAlgs;
    double * ranges;
    double * stepSize;


}Params;

struct Params * initParams(void);

void destructParams(Params * byeParams);

#endif //PARAMS_H


