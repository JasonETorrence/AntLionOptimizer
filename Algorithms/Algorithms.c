//
// Algorithms written for SOFTWARE testing:
//
// Created by Jason Torrence on 3/29/2019.
// Edited by Jason Torrence on 4/11/2019.
//
// This is designed to run simply using a set of parameters, meaning that if
// the code here is appended to with an additional algorithm, the coder of that algorithm
// must simply add the prototype, matching the return type and parameters, add the algorithm
// to the switch statement in switchForAlgs(), add the ranges to data.txt, and
// increase the "Number of Algorithms" in data.txt by 1.
//
// Email: torrencej@cwu.edu
//

#include <stdio.h>
#include <stdlib.h>
#include "Algorithms.h"
#include "math.h"
#include "..\Utils\Utils.h"
#include "..\MT\mt19937ar.h"
#include "../DataContainer/DataContainer.h"

#define M_PI 3.1415926535

/**
 * TestMatrix: takes in the parameters and run the sent number for an algorithm.
 *
 * This takes in a dataContainer, which contains the matrix used for testing, and sends each individual row in that
 * matrix to the switch for the algorithms to get results.
 *
 * @param  struct params: contains the required parameters for running the algorithms and printing results
 * @param  int dimensions: used to decide how many values are being placed in the "columns" of the matrix
 * @param  int algNum: sent to the switch to decide which algorithm to run
 * @param  struct dataContainer * datacont: contains the matrix to be tested, and is returned containing its results.
 * @return struct dataContainer * datacont: pointer sent to the function, but now with the corresponding results.
 */
struct DataContainer * TestMatrix(int dimensions, int algNum, struct DataContainer * datacont, int size){
    double * results = (double *) calloc(size,  sizeof(double));
    if(!results){
        fprintf(stderr, "'Results', failed to allocate the necessary memory.");
        exit(-1);
    }
#pragma acc kernels
    for (int i = 0; i < size; i++) {
        double result = switchForAlgs(datacont->matrix[i], dimensions, algNum);
        results[i] = result;
    }

    free(datacont->resultsVector);
    datacont->resultsVector = results;

    return datacont;

}

/**
 * switchForAlgs: a switch for the algorithms
 *
 * This functions is what decides which algorithm to run the vector against.
 *
 * @param  double * vector: sent to the algorithm determined by algNum and is tested
 * @param  int size: sent to the algorithm to decide how many values are in the vector
 * @param  int algNum: sent to the switch to decide which algorithm to run
 * @return double result: the result of the tested vector
 */

double switchForAlgs(double * vector, int size, int algNum){

    double result = initValue;
    switch(algNum) {
        case 0:
            result = Schwefels(vector, size);
            break;
        case 1:
            result = DeJongsFirst(vector, size);
            break;
        case 2:
            result = Rosenbrock(vector, size);
            break;
        case 3:
            result = Rastagrin(vector, size);
            break;
        case 4:
            result = Griewangk(vector, size);
            break;
        case 5:
            result = SineEnvelopeSineWave(vector, size);
            break;
        case 6:
            result = StretchedVSineWave(vector, size);
            break;
        case 7:
            result = AckleysOne(vector, size);
            break;
        case 8:
            result = AckleysTwo(vector, size);
            break;
        case 9:
            result = EggHolder(vector, size);
            break;
        case 10:
            result = Rana(vector, size);
            break;
        case 11:
            result = Pathological(vector, size);
            break;
        case 12:
            result = Michalewicz(vector, size);
            break;
        case 13:
            result = MastersCosineWave(vector, size);
            break;
        case 14:
            result = Quartic(vector, size);
            break;
        case 15:
            result = Levy(vector, size);
            break;
        case 16:
            result = Step(vector, size);
            break;
        case 17:
            result = Alpine(vector, size);
            break;
        default:
            printf("%d: case was attempted but not reached.\n", algNum);
    }

return result;
}

/**
 * Schwefels() is simply schefel's algorithm
 *
 * This uses a vector of data and sends it through Schwefel's algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of Schefel's algorithm.
 */
double Schwefels(double *values, int size){
    double  endVal = initValue;

    for(int i = 0; i < size; i++){
        endVal += values[i] * (sin(sqrt(fabs(values[i]))));
    }
    endVal = (418.9829 * size) - endVal;

    return endVal;

}

/**
 * DeJongsFirst() is simply deJong's First algorithm.
 *
 * This uses a vector of data and sends it through deJong's First algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of deJong's First algorithm.
 */
double DeJongsFirst(double *values, int size){

    double  endVal = initValue;

    for(int i = 0; i < size; i++){
        endVal += sqr(values[i]);
    }

    return endVal;

}

/**
 * Rosenbrock() is simply the Rosenbrock algorithm.
 *
 * This uses a vector of data and sends it through the Rosenbrock algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Rosenbrock algorithm.
 */
double Rosenbrock(double *values, int size){

    double endVal = initValue;

    for(int i = 0; i < size - 1; i++) {
        endVal += (100.0 * sqr(sqr(values[i]) - values[i + 1]) + sqr(1.0 - values[i]));
    }

    return endVal;

}

/**
 * Rastagrin() is simply the Rosenbrock algorithm.
 *
 * This uses a vector of data and sends it through the Rosenbrock algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Rosenbrock algorithm.
 */
double Rastagrin(double *values, int size) {

    double endVal = initValue;

    for (int i = 0; i < size; i++) {
        endVal += (sqr(values[i]) - (10.0 * (cos(2.0 * M_PI * values[i]))));
    }
    endVal = 10.0 * size * endVal;

    return endVal;
}

/**
 * Griewangk() is simply the Griewangk algorithm.
 *
 * This uses a vector of data and sends it through the Griewangk algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Griewangk algorithm.
 */
double Griewangk(double *values, int size) {

    double endVal;
    double sum = initValue;
    double product = 1.0;

    for (int i = 0; i < size; i++) {
        sum += (sqr(values[i])/4000.0);
        product *= (cos(values[i]/(sqrt(i + 1))));
    }
    endVal = 1.0 + sum - product;

    return endVal;

}

/**
 * SineEnvelopeSineWave() is simply the Sine Envelope Sine Wave algorithm.
 *
 * This uses a vector of data and sends it through the Sine Envelope Sine Wave algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Sine Envelope Sine Wave algorithm.
 */
double SineEnvelopeSineWave(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += 0.5 + ((sqr(sin(sqr(values[i]) + sqr(values[i + 1]) - 0.5)))
                                           / sqr(1.0  + (0.001 * (sqr(values[i]) + sqr(values[i + 1])))));
    }
    endVal *= -1;

    return endVal;

}

/**
 * StretchedVSineWave() is simply the Stretched V Sine Wave algorithm.
 *
 * This uses a vector of data and sends it through the Stretched V Sine Wave algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Stretched V Sine Wave algorithm.
 */
double StretchedVSineWave(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += ((pow((sqr(values[i]) + sqr(values[i + 1])), (1.0/3.0)))
                   * (sqr(sin(50.0 * (pow((sqr(values[i]) + sqr(values[i + 1])), (1.0/10.0)))))
                      + 1.0));
    }

    return endVal;
}

/**
 * AckleysOne() is simply the Ackley's One algorithm.
 *
 * This uses a vector of data and sends it through the Ackley's One algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Ackley's One algorithm.
 */
double AckleysOne(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += ((1.0 / exp(0.5)) * ((sqrt((sqr(values[i]) + sqr(values[i + 1])))) +
                                                       (3.0 * (cos(2.0 * values[i]) + sin(2.0 * values[i + 1])))));
    }
    return endVal;

}

/**
 * AckleysTwo() is simply the Ackley's Two algorithm.
 *
 * This uses a vector of data and sends it through the Ackley's Two algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Ackley's Two algorithm.
 */
double AckleysTwo(double *values, int size){

    double  endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += 20.0 + exp(1.0) - (20.0 / (exp(0.5 * (sqrt((sqr(values[i]) + sqr(values[i + 1])) / 2.0))))) -
                  exp(0.2 * (cos(2.0 * M_PI * values[i])) + cos(2.0 * M_PI * values[i + 1]));
    }

    return endVal;

}

/**
 * EggHolder() is simply the Egg Holder algorithm.
 *
 * This uses a vector of data and sends it through the Egg Holder algorithm.
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Egg Holder algorithm.
 */
double EggHolder(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal -= (values[i] * sin(sqrt(fabs(values[i] - values[i + 1] - 47.0))) - (values[i + 1] + 47.0)
                    * sin(sqrt(fabs(values[i + 1] + 47.0 + (values[i]/2.0)))));
    }
    return endVal;
}

/**
 * Rana() is simply the Rana algorithm.
 *
 *  This uses a vector of data and sends it through the Rana algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Rana algorithm.
 */
double Rana(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += (values[i] * sin(sqrt(fabs(values[i + 1]  - values[i] + 1.0))) * cos(sqrt(fabs(values[i + 1]  + values[i] + 1.0)))
                   + (values[i + 1] + 1.0) * cos(sqrt(fabs(values[i + 1]  - values[i] + 1.0))) * sin(sqrt(fabs(values[i + 1]  + values[i] + 1.0))));

    }

    return endVal;
}

/**
 * Pathological() is simply the Pathological algorithm.
 *
 *  This uses a vector of data and sends it through the Pathological algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Pathological algorithm.
 */
double Pathological(double *values, int size){

    double  endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += 0.5 + ((sqr(sin(sqrt(100.0 * sqr(values[i]) + sqr(values[i + 1])))) - 0.5)
                                   / (1.0 + 0.001 * sqr(sqr(values[i]) - 2.0 * values[i] * values[i + 1] + sqr(values[i + 1]))));
    }

    return endVal;

}

/**
 * Michalewicz() is simply the Michalewicz algorithm.
 *
 *  This uses a vector of data and sends it through the Michalewicz algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Michalewicz algorithm.
 */
double Michalewicz(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size; i++) {
        endVal += sin(values[i]) * powf(sin((i + 1 * sqr(values[i])) / M_PI) , 20.0);
    }
    endVal *= -1;

    return endVal;

}

/**
 * MastersCosineWave() is simply the Masters Cosine Wave algorithm.
 *
 *  This uses a vector of data and sends it through the Masters Cosine Wave algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Masters Cosine Wave algorithm.
 */
double MastersCosineWave(double *values, int size){

    double endVal = initValue;
    //printVectorToStdOutput(values, size);

    for (int i = 0; i < size - 1; i++) {
        endVal += ((exp(-0.125 * (sqr(values[i]) + sqr(values[i + 1]) + 0.5 * (values[i + 1]) * values[i])))
                   * (cos(4.0 * sqrt(sqr(values[i]) + sqr(values[i + 1]) + 0.5 * values[i] * values[i + 1]))));

        //printf("%lf, ", endVal);
    }

    endVal *= -1;

    return endVal;
}

/**
 * Quartic() is simply the Quartic algorithm.
 *
 *  This uses a vector of data and sends it through the Quartic algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Quartic algorithm.
 */
double Quartic(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += (i + 1) * (pow(values[i], 4.0));
    }
    return endVal;

}

/**
 * Levy() is simply the Levy algorithm.
 *
 *  This uses a vector of data and sends it through the Levy algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Levy algorithm.
 */
double Levy(const double *values, int size){

    double endVal = initValue;

    for (int i = 1; i < size - 1; i++) {
        endVal += sqr((1 + (values[i] - 1)/2) - 1)
                  * (1 + 10 * sqr(sin(M_PI * (1 + (values[i] - 1)/2) + 1)))
                  + sqr((1 + (values[i] - 1)/2) + 1)
                    * (1 + sqr(sin(2 * M_PI * (1 + (values[i] - 1)/2))));
    }
    endVal += sqr(sin(M_PI * (1 + (values[0] - 1)/2)));
    return endVal;

}

/**
 * Step() is simply the Step algorithm.
 *
 *  This uses a vector of data and sends it through the Step algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Step algorithm.
 */
double Step(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += sqr(fabs(values[i]) + 0.5);
    }
    return endVal;

}

/**
 * Alpine() is simply the Alpine algorithm.
 *
 *  This uses a vector of data and sends it through the Alpine algorithm.
 *
 *
 * @param  double *values: a randomly generated vector or values
 * @param  int size: the number of values within double *values
 * @return double endVal: the result of the Alpine algorithm.
 */
double Alpine(double *values, int size){

    double endVal = initValue;

    for (int i = 0; i < size - 1; i++) {
        endVal += fabs(values[i] * sin(values[i]) + 0.1 * values[i]);
    }
    return endVal;

}

