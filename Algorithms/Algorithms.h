//
// Algorithms written for hardware testing:
//
// Created by Jason Torrence on 3/29/2019.
// Edited by Jason Torrence on 4/11/2019.
//
// This is designed to run simply using a set of parameters, meaning that if
// the code here is appended to with an additional algorithm, the coder of that algorithm
// must simply add the prototype, matching the return type and parameters, add the algorithm
// to the switch statement in runAlgs(Struct Params, int), add the ranges to data.txt, and
// increase the "Number of Algorithms" in data.txt by 1.
//
// Email: torrencej@cwu.edu
//

#include "../Params/Params.h"
#include "../VectorAndResult/VectorAndResult.h"
#include "../DataContainer/DataContainer.h"

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

struct DataContainer * TestMatrix(int dimensions, int algNum, struct DataContainer * datacont, int size);
struct VectorAndResult testVector(double * vector, int size, int algNum);
void testVectorWithPointer(VectorAndResult * var, int algNum);
double switchForAlgs(double * vector, int size, int algNum);

double Schwefels(double *values, int size);
double DeJongsFirst(double *values, int size);
double Rosenbrock(double *values, int size);
double Rastagrin(double *values, int size);
double Griewangk(double *values, int size);
double SineEnvelopeSineWave(double *values, int size);
double StretchedVSineWave(double *values, int size);
double AckleysOne(double *values, int size);
double AckleysTwo(double *values, int size);
double EggHolder(double *values, int size);
double Rana(double *values, int size);
double Pathological(double *values, int size);
double Michalewicz(double *values, int size);
double MastersCosineWave(double *values, int size);
double Quartic(double *values, int size);
double Levy(const double *values, int size);
double Step(double *values, int size);
double Alpine(double *values, int size);

#endif //ALGORITHMS_H



