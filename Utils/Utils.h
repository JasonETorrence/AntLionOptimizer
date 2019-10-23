//
// Created by Jason Torrence on 3/29/2019.
//
// Originally designed to work with algorithms for the purpose of simple utilities.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

double sqr(double num);

void printResultToFile(double result, FILE *rePtr);
void printStringToFile(char * string, FILE *rePtr);
void printVectorToFile(double * vector, int size, FILE *rePtr);
void printVectorToStdOutput(double * vector, int size);
void printMatrixToFile(double ** matrix, int length, int width, FILE * rePtr);
double distance(double X, double Y);
double * copyDoublePointer(double * vector, int size);
void printExtraInformationToResultsFile(char * string, int algNum, int strategyNum, FILE *rePtr);
void printLineToFile(FILE *rePtr);
void printHeaderToFile(int dimension, FILE *rePtr);
void shuffle(int * vector, int size, int randSeed, int numOfShuffledVals);
void sortDoublePointer(double * vector, int size);
void sortIntPointer(int * vector, int size);
void sortDoublePointerAndPointerArray(double * vector, int * pointers, int size);
int * makeShuffledIntPointer(int size, int numOfShuffledValues, int randSeed);

#define initValue 0.0

#endif //UTILS_H