//
// Created by Jason Torrence on 5/8/2019.
//

#include "../MT/mt19937ar.h"
#include "../Utils/Utils.h"
#include "../Params/Params.h"
#include "../DataContainer/DataContainer.h"
#include "../MatrGen/MatrGen.h"
#include "../Algorithms/Algorithms.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

double runALO(int algNum, Params * params, FILE * anMePtr, FILE * antLionMPtr, FILE * antRePtr, FILE * antLionRePtr);
void moveAnts(DataContainer * antInfo, DataContainer * ALInfo, Params * params, int algNum, int iteration, int elite);
double randomWalkAgainstAntLion(Params * params, int algNum, int iteration, double ant, double antLion, double ALFit,
        double bestFit, double worstFit);
int rouletteWheel(DataContainer * ALInfo, Params * params);
double calculateMovementFactor(int iteration, Params * params);
double makeSureAntIsInBounds(double antLocation, Params * params, int algNum);
int findEliteAntLion(DataContainer * antLions, Params * params);
int findWorstAntLion(DataContainer * antLions, Params * params);
void checkFitnessAndUpdateViaSort(DataContainer * ants, DataContainer * antLions, Params * params, int algNum);
void consumeAnt(DataContainer * ants, DataContainer * antLions, int antLocation, int antLionLocation, Params* params
    , int algNum);
void printMatricesToFile(DataContainer * ants, DataContainer * antLions, Params * params, FILE * antRePtr, FILE * antLionrePtr);

/**
 * ALO: initializes structs, opens the results file, starts a clock, and calls the function
 * using all that information, ends by closing the file and
 *
 * @return void
 */
void ALO(){

    Params * params = initParams();

    init_genrand(time(0));

    clock_t start, stop;
    start = clock();

    FILE *antMPtr;
    FILE *antLionMPtr;
    FILE *antRePtr;
    FILE *antLionRePtr;
    if((antMPtr = fopen("../Results/AntMatrices.csv", "a")) == NULL){
        fprintf(stderr, "Results.csv couldn't be made or opened.");
    }
    if((antLionMPtr = fopen("../Results/AntLionMatrices.csv", "a")) == NULL){
        fprintf(stderr, "Results.csv couldn't be made or opened.");
    }
    if((antMPtr = fopen("../Results/AntResults.csv", "a")) == NULL){
        fprintf(stderr, "Results.csv couldn't be made or opened.");
    }
    if((antLionMPtr = fopen("../Results/AntLionResults.csv", "a")) == NULL){
        fprintf(stderr, "Results.csv couldn't be made or opened.");
    }

#pragma acc kernels
    for(int i = 0; i < params->numOfAlgs; i++) {
        double bestResult = runALO(i, params, antMPtr, antLionMPtr, antRePtr, antLionRePtr);
        printf("Best result for algID %d: %lf\n", i+1, bestResult);
    }

    stop = clock();

    double finalTime = (double)(1000 * (stop - start)) / CLOCKS_PER_SEC;

    printf("Time it took to complete these tasks: %5.0lf ms\n", finalTime);
    fclose(antRePtr);
    fclose(antLionRePtr);
    destructParams(params);

}

/**
 * runALO: Creates the datacontainers and runs the functions in order for the number
 * of iterations suggested by params
 *
 * @param algNum the algorithm to run the matricies against
 * @param params numbers used by the algorithms
 * @param rePtr File for printing results and matrices to
 * @return the best result found after the provided number of iterations
 */
double runALO(int algNum, Params * params, FILE * antMPtr, FILE * antLionMPtr, FILE * antRePtr, FILE * antLionRePtr){

    DataContainer ants = initDataContainer(params->swarmSize);
    DataContainer antLions = initDataContainer(params->numOfAntLions);
    double upperBound = params->ranges[(algNum*2) + 1];
    double lowerBound = params->ranges[algNum*2];

    ants.matrix = genMatrix(upperBound, lowerBound, params->swarmSize, params->particleSize, (int)genrand_int32());
    antLions.matrix = genMatrix(upperBound, lowerBound, params->numOfAntLions, params->particleSize, (int)genrand_int32());
    TestMatrix(params->particleSize, algNum, &ants, params->swarmSize);
    TestMatrix(params->particleSize, algNum, &antLions, params->numOfAntLions);

    int elite = findEliteAntLion(&antLions, params);
    double eliteValue = antLions.resultsVector[elite];
    for(int m = 0; m < params->iterations; m++){
        printMatricesToFile(&ants, &antLions, params, antRePtr, antLionRePtr);
        moveAnts(&ants, &antLions, params, algNum, m, elite);
        TestMatrix(params->particleSize, algNum, &ants, params->swarmSize);
        checkFitnessAndUpdateViaSort(&ants, &antLions,  params, algNum);
        elite = findEliteAntLion(&antLions, params);
        eliteValue = antLions.resultsVector[elite];
        //printf("%lf\n", eliteValue);
    }

    printMatricesToFile(&ants, &antLions, params, antRePtr, antLionRePtr);

    destructDataContainer(&ants, params->swarmSize);
    destructDataContainer(&antLions, params->numOfAntLions);

    return eliteValue;
}

/**
 * moveAnts: moves the ants using the slide of a random antlion and the elite antlion.
 *
 * @param antInfo the ants to move
 * @param ALInfo the ant lions who slide and consume ants
 * @param params numbers used by the algorithms
 * @param algNum the algorithm to run the matrices against
 * @param iteration the number of times this was called: used to reduce slide in later iterations
 * @param elite the elite antlion
 */
void moveAnts(DataContainer * antInfo, DataContainer * ALInfo, Params * params, int algNum, int iteration, int elite){
#pragma acc kernels
    for(int i = 0; i < params->swarmSize; i++){
        //printf("Rouletting\n");
        int randomAntLion = rouletteWheel(ALInfo, params);
        int worstAntLionLoc = findWorstAntLion(ALInfo, params);
#pragma acc kernels
        for(int j = 0; j < params->particleSize; j++){
            //printf("Running against elite\n");
            double eliteWalk = randomWalkAgainstAntLion(params, algNum, iteration, antInfo->matrix[i][j],
                    ALInfo->matrix[elite][j], ALInfo->resultsVector[elite], ALInfo->resultsVector[elite],
                    ALInfo->resultsVector[worstAntLionLoc]);
            //printf("Running against random\n");
            double randWalk = randomWalkAgainstAntLion(params, algNum, iteration, antInfo->matrix[i][j],
                    ALInfo->matrix[randomAntLion][j], ALInfo->resultsVector[elite], ALInfo->resultsVector[elite],
                    ALInfo->resultsVector[worstAntLionLoc]);
            antInfo->matrix[i][j] = (eliteWalk + randWalk) / 2;
        }
    }
}

/**
 * RandomWalkAgainstAntlion: random walks an ant against a select antlion
 *
 * @param params numbers used by the algorithms
 * @param algNum the algorithm to run the matrices against
 * @param iteration the number of times this was called
 * @param ant the number associated with the select ant
 * @param antLion the number associated with the select antlion
 * @return the adjusted dimension for the ant
 */
double randomWalkAgainstAntLion(Params * params, int algNum, int iteration, double ant, double antLion, double ALFit,
        double bestFit, double worstFit){
    double stepSize = params->stepSize[algNum];
    double movementFactor = calculateMovementFactor(iteration, params);
    double fitnessFactor = 1 - ((ALFit - worstFit) / (bestFit - worstFit));

    double step = stepSize;
    int boolean = genrand_int31() % 2;
    if(boolean){
        step *= -1;
    }
    double adjustForSlide = ((antLion - ant)/movementFactor) * fitnessFactor * 4;
    ant += adjustForSlide + step;
    ant = makeSureAntIsInBounds(ant, params, algNum);

    return ant;
}

/**
 * rouletteWheel: Randomly selects an antlion based on it's fitness value.
 *
 * @param ALInfo the antlion dataconatiner
 * @param params numbers used by the algorithms
 * @return the randomly selected antlion
 */
int rouletteWheel(DataContainer * ALInfo, Params * params){
    //printf("Rouletting:\n");
    double total = 0;
    double worstFitness = -FLT_MAX;
    double * resultsCopy = (double *) calloc(params->numOfAntLions, sizeof(double));
    if (!resultsCopy) {
        fprintf(stderr, "Program failed to allocate the necessary memory.");
        exit(-1);
    }
    for(int i = 0; i < params->numOfAntLions; i++){
        resultsCopy[i] = ALInfo->resultsVector[i] * -1;
        //printf("Antlion %d: %lf\n", i, ALInfo->resultsVector[i]);
        total +=  fabs(ALInfo->resultsVector[i]);
        if(ALInfo->resultsVector[i] > worstFitness){
            worstFitness = ALInfo->resultsVector[i];
            //printf("Worst Fitness update: %lf\n", worstFitness);
        }
    }
    if(worstFitness != fabs(worstFitness)){
        worstFitness = fabs(worstFitness);
    }
    total *= 2;
    //printf("%lf : %lf\n", total, worstFitness);
    double roulette = fmod(genrand_real1(), total);
    for(int i = 0; i < params->numOfAntLions; i++){
        resultsCopy[i] += worstFitness*2;
        //printf("roulette wheel at i: %lf\n", resultsCopy[i]);
        if(resultsCopy[i] != fabs(resultsCopy[i])){
            printf("Roulette contains a negative number.");
        }
    }
    int loc = 0;
    while(roulette > 0){
        if(loc >= params->numOfAntLions){
            loc = 0;
        }
        roulette -= resultsCopy[loc];
        loc++;
    }
    free(resultsCopy);
    return loc;
}

/**
 * calculateMovementFactor: creates a movement factor based on a number of iterations
 *
 * @param iteration the number of iterations that have passed
 * @param params numbers used by the algorithms
 * @return The movement factor for use by the algorithm
 */
double calculateMovementFactor(int iteration, Params * params){
    double movementFactor = 1;
    double percentCompletedIterations = (double)((double)iteration / params->iterations);
    if(percentCompletedIterations > 0.1){
        movementFactor = 2;
    }else if(percentCompletedIterations > 0.5){
        movementFactor = 3;
    }else if(percentCompletedIterations > 0.75){
        movementFactor = 4;
    }else if(percentCompletedIterations > 0.9){
        movementFactor = 5;
    }else if(percentCompletedIterations > 0.95){
        movementFactor = 6;
    }
    return pow(10, movementFactor);
}

/**
 * MakeSureAntIsInBounds: adjusts the ant in bounds if it is out of bounds
 *
 * @param antLocation the ant to adjust
 * @param params numbers used by the algorithms
 * @param algNum the algorithm associated with the used algorithm
 * @return
 */
double makeSureAntIsInBounds(double antLocation, Params * params, int algNum){
    if(antLocation > params->ranges[algNum * 2 + 1]){
        antLocation = params->ranges[algNum * 2 + 1];
    }else if(antLocation < params->ranges[algNum * 2]){
        antLocation = params->ranges[algNum * 2];
    }
    return antLocation;
}

/**
 * FindEliteAntLion: finds and returns the best fit antlions location in the datacontainer
 *
 * @param antLions the antlion datacontainer
 * @param params numbers used by the algorithms
 * @return the location of the elite antlion
 */
int findEliteAntLion(DataContainer * antLions, Params * params){
    int eliteLocation = 0;
    for(int i = 1; i < params->numOfAntLions; i++){
        if(antLions->resultsVector[eliteLocation] > antLions->resultsVector[i]){
            eliteLocation = i;
        }
    }
    return eliteLocation;
}

/**
 * FindWostAntLion
 *
 * @param antLions the antlion datacontainer
 * @param params params numbers used by the algorithms
 * @return the worst antlion's location
 */
int findWorstAntLion(DataContainer * antLions, Params * params){
    int worstLocation = 0;
    for(int i = 1; i < params->numOfAntLions; i++){
        if(antLions->resultsVector[worstLocation] < antLions->resultsVector[i]){
            worstLocation = i;
        }
    }
    return worstLocation;
}

/**
 * checkFitnessAndUpdateViaSort: repalces antlions with better fit ants
 *
 * @param ants the ants datacontainer
 * @param antLions the antlions datacontainer
 * @param params numbers used by the algorithms
 * @param algNum the algorithm to run the matrices against
 */
void checkFitnessAndUpdateViaSort(DataContainer * ants, DataContainer * antLions, Params * params, int algNum){
    double *antFitnessCopy = (double *) calloc(params->swarmSize, sizeof(double));
    double *antLionsFitnessCopy = (double *) calloc(params->numOfAntLions, sizeof(double));
    int *antLocations = (int *) calloc(params->swarmSize, sizeof(int));
    int *antLionLocations = (int *) calloc(params->numOfAntLions, sizeof(int));

    if (!antFitnessCopy || !antLionLocations || !antLocations || !antLionsFitnessCopy) {
        fprintf(stderr, "Program failed to allocate the necessary memory.");
        exit(-1);
    }

    for (int i = 0; i < params->swarmSize; i++) {
        double placeholder = ants->resultsVector[i];
        antFitnessCopy[i] = placeholder;
        antLocations[i] = i;
        if(i < params->numOfAntLions){
            antLionsFitnessCopy[i] = antLions->resultsVector[i];
            antLionLocations[i] = i;
        }
    }

    sortDoublePointerAndPointerArray(antFitnessCopy, antLocations, params->swarmSize);
    sortDoublePointerAndPointerArray(antLionsFitnessCopy, antLionLocations, params->numOfAntLions);
    for (int i = 0; i < params->swarmSize; i++) {
        int antlion = params->numOfAntLions - 1;
        int cont = FALSE;
        while(antFitnessCopy[i] < antLionsFitnessCopy[antlion] && antlion > -1){
            cont = TRUE;
            antlion--;
        }
        antlion++;
        if(cont){
            consumeAnt(ants, antLions, antLocations[i], antlion, params, algNum);
        }else{
            i = params->swarmSize;
        }
    }
    //printf("Testing Matrix\n");
    TestMatrix(params->particleSize, algNum, ants, params->swarmSize);
    free(antFitnessCopy);
    free(antLionsFitnessCopy);
    free(antLionLocations);
    free(antLocations);
}

/**
 * consumeAnt: replaces an antlions values with an ants upon an ant being better than an antlion
 *
 * @param ants the ants datacontainer
 * @param antLions the antlions datacontainer
 * @param antLocation the ant to "consume"
 * @param antLionLocation the antlion to adjust
 * @param params numbers used by the algorithms
 * @param algNum the algorithm to run the matrices against
 */
void consumeAnt(DataContainer * ants, DataContainer * antLions, int antLocation, int antLionLocation, Params* params,
        int algNum){
#pragma acc kernels
    for(int i = 0; i < params->particleSize; i++){
        double placeholder = ants->matrix[antLocation][i];
        antLions->matrix[antLionLocation][i] = placeholder;
    }
    double placeholder = ants->resultsVector[antLocation];
    antLions->resultsVector[antLionLocation] = placeholder;

    free(ants->matrix[antLocation]);
    ants->matrix[antLocation] = genRandLine(params->ranges[algNum * 2 + 1], params->ranges[algNum*2],
            params->particleSize);

}

/**
 * printMatricesToFile: prints all important information to the results file
 *
 * @param ants the ants datacontainer
 * @param antLions the antlions datacontainer
 * @param params numbers used by the algorithms
 * @param rePtr the file to print to
 */
void printMatricesToFile(DataContainer * ants, DataContainer * antLions, Params * params, FILE * antRePtr, FILE * antLionrePtr){
    printMatrixToFile(ants->matrix, params->swarmSize, params->particleSize, antRePtr);
    //printLineToFile(antRePtr);
    //printLineToFile(antRePtr);
    //printVectorToFile(ants->resultsVector, params->swarmSize, rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
    printMatrixToFile(antLions->matrix, params->numOfAntLions, params->particleSize, antLionrePtr);
    //printLineToFile(antLionrePtr);
    //printLineToFile(antLionrePtr);
    //printVectorToFile(antLions->resultsVector, params->numOfAntLions, rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
    //printLineToFile(rePtr);
}
//End ALO.c