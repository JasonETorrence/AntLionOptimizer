//
// Created by Jason Torrence on 3/29/2019.
//
// This is a struct simply designed to pull in information from a file (UserInput.txt) and store it.
//
// Originally designed to work with algorithms for the purpose of storing parameters.
//
// Email: torrencej@cwu.edu
//

#include "Params.h"
#include <stdio.h>
#include <stdlib.h>

struct Params params;

/**
 * initParams: generates a Params struct based on Data.txt and returns it
 *
 * This struct initializer opens UserInput/UserInput.txt and stores the values within it: sample size,
 * number of dimension, number of algorithms, number of iterations, step size for local search, the dimensions
 * used for vector sizes, and the ranges (bounds) of each algorithm.
 *
 * @return Params pointer
 */
 struct Params * initParams(){

    FILE *dPtr;

    int swarmSize;
    int numOfAntLions;
    int iterations;
    int particleSize;
    int numOfAlgs;
    double elitism;

    double * ranges;
    double * stepSize;

    //puts("Params: Opening Data.txt:");
    if((dPtr = fopen("../UserInput/UserInput.txt", "r")) == NULL){
        fprintf(stderr, "'UserInput.txt' couldn't be found.");
        exit(-1);
    }

    fscanf(dPtr, "%d", &swarmSize);
    fscanf(dPtr, "%d", &numOfAntLions);
    fscanf(dPtr, "%d", &iterations);
    fscanf(dPtr, "%d", &particleSize);
    fscanf(dPtr, "%d", &numOfAlgs);
    fscanf(dPtr, "%lf", &elitism);

    ranges = (double *) calloc (numOfAlgs * 2, sizeof(double));
    stepSize = (double *) calloc (numOfAlgs, sizeof(double));

    if(!ranges || !stepSize){
        fprintf(stderr, "Array of ranges in Params.c failed to allocate memory.");
        exit(-1);
    }

    for(int i = 0; i < numOfAlgs; i++){
        int iteration = i * 2;
        double placeHolder;
        fscanf(dPtr, "%lf", &placeHolder);
        ranges[iteration] = placeHolder;
        fscanf(dPtr, "%lf", &placeHolder);
        ranges[iteration + 1] = placeHolder;
        fscanf(dPtr, "%lf", &placeHolder);
        stepSize[i] = placeHolder;
    }

    fclose(dPtr);

    params.swarmSize = swarmSize;
    params.iterations = iterations;
    params.numOfAntLions = numOfAntLions;
    params.particleSize = particleSize;
    params.numOfAlgs = numOfAlgs;
    params.ranges = ranges;
    params.stepSize = stepSize;


    return &params;
}

void destructParams(Params * byeParams){
     free(byeParams->ranges);
     free(byeParams->stepSize);
 }
