//
// Created by Jason Torrence on 3/30/2019.
//
#ifndef MATRGEN_H
#define MATRGEN_H

double ** genMatrix(double upperBound, double lowerBound, int rows, int columns, int randSeed);

double * genRandLine(double upperBound, double lowerBound, int columns);

void freeMatr(double** matrix, int size);

#endif //MATRGEN_H


