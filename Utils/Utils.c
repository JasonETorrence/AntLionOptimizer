//
// Created by Jason Torrence on 3/29/2019.
//
// Originally designed to work with algorithms for the purpose of simple utilities.
//

#include <stdlib.h>
#include <math.h>
#include "Utils.h"
#include "..\MT\mt19937ar.h"


/**
 * sqr: Squares the value sent to it and returns
 *
 * @param double num: the number to be squared
 * @return the argument number squared
 */
double sqr(double num){
    return (num * num);
}

/**
 * printResultToFile: pulls in a value and time and prints it to Results.csv
 *
 * @param double result: the result that needs to be printed to the file
 * @param int time: the time to be printed to the file
 * @return void
 */
void printResultToFile(double result, FILE *rePtr) {

   fprintf(rePtr, "%lf, ", result);

}

/**
 * printStringToFile: pulls in a value and time and prints it to Results.csv
 *
 * @param char * string: the string that needs to be printed to the file
 * @return void
 */
void printStringToFile(char * string, FILE *rePtr){

    fputs(string, rePtr);

}

/**
 * printExtraInformationToFile: prints the argument string and algorithm number to the results.csv file WITHOUT a line
 *
 * @param char * string: printed to the file
 * @param int algNum: the algorithm number to be printed to the file (+1).
 * @return void
 */
void printExtraInformationToResultsFile(char * string, int algNum, int strategyNum, FILE *rePtr){

    fprintf(rePtr, "\n");
    fputs(string, rePtr);
    fprintf(rePtr, "Algorithm Number: %d, Strategy Number: %d\n", algNum + 1, strategyNum + 1);

}
/**
 * printLineToFile
 *
 * simply prints a line to the results.csv file
 *
 * @return void
 */
void printLineToFile(FILE *rePtr){

    fprintf(rePtr, "\n");

}

/**
 * printHeaderToFile: prints a header to the results.csv file
 *
 * This assumes that the printing values are within the provided dimension, thus the header is used simply to
 * space out the tests.
 *
 * @param int dimension: used to describe the dimensionality of the test in the results.csv file
 * @return void
 */
void printHeaderToFile(int dimension, FILE *rePtr){

    fprintf(rePtr, "Searches: dimension %d: \n", dimension);

}


/**
 * printVectorToFile: prints a vector to the results.csv file
 *
 * @param double * vector: the vector to be printed to results.csv
 * @param int size: provides the number of elements in the vector
 * @return void
 */
void printVectorToFile(double * vector, int size, FILE *rePtr){

    for(int i = 0; i < size; i++) {
        if(i < size - 1) {
            fprintf(rePtr, "%lf, ",vector[i]);
        }else{
            fprintf(rePtr, "%lf",vector[i]);
        }
    }

}
/**
 * printVectorStdOuput: prints a vector to the standard output
 *
 * This is used in for debugging purposes, and is thus unused in the final version.
 *
 * @param double * vector: the vector to be printed
 * @param int size: provides the number of elements in the vector
 * @return void
 */
void printVectorToStdOutput(double * vector, int size){
    for(int i = 0; i < size; i++) {
        if(i < size - 1) {
            printf("%lf, ",vector[i]);
        }else{
            printf("%lf",vector[i]);
        }
    }
    puts("");
}

/**
 * distance: returns the distance between two doubles
 *
 * This is simply the distance formula using two doubles. Technically, you could find the distance between two objects
 * in 2d space as well using two of these and pythagorean's theorem.
 *
 * @param double X: one of the two values that we need to find the distance between
 * @param double Y: ditto
 * @return the distance between X and Y
 */
double distance(double X, double Y){
    return sqrt(sqr(X - Y));
}

void printMatrixToFile(double ** matrix, int length, int width, FILE * rePtr){
    for(int i = 0; i < length; i++){
        printVectorToFile(matrix[i], width, rePtr);
        printLineToFile(rePtr);
    }
}

/**
 * copyDouble Pointer: copies and returns a double pointer
 *
 * @param double * vector: the double pointer to be copied and returned
 * @param int size: describes the number of values in the double pointer
 * @return a copy of the double pointer.
 */
double * copyDoublePointer(double * vector, int size){
    double * returnedVector = (double *) calloc(size, sizeof(double));
    for(int i = 0; i < size; i++){
        returnedVector[i] = vector[i];
    }
    return returnedVector;
}

/**
 * shuffle: shuffles a vectors values
 *
 * @param int * vector: the int * pointer to be shuffled
 * @param int size: describes the number of values in the int pointer
 * @param int randSeed: a seed for random
 * @param int numOfShuffledVals: the number of values to be shuffled
 * @return void
 */
void shuffle(int * vector, int size, int randSeed, int numOfShuffledVals){
    init_genrand(randSeed);
    for(int i = 0; i < numOfShuffledVals; i++){
        int randVal = genrand_int31() % size;
        int placeholder = vector[i];
        vector[i] = vector[randVal];
        vector[randVal] = placeholder;
    }
}

/**
 * sortInPointer: sorts a vector of integer
 *
 * @param int * vector: the int * pointer to be sorted
 * @param int size: describes the number of values in the int pointer
 * @return void
 */
void sortIntPointer(int * vector, int size){
    for(int i = 0; i < size - 1; i++){
        for(int k = i+1; k < size; k++){
            if(vector[i] > vector[k]){
                int placeholder = vector[i];
                vector[i] = vector[k];
                vector[k] = placeholder;
            }
        }
    }
}

/**
 * sortDoublePointerAndPointerArray: sorts a vector of doubles and it's associated indices
 *
 * @param double * vector: the double pointer to be sorted
 * @param int * pointers: a vector of indices that will be matched to their movement
 * @param int size: describes the number of values in the int pointer
 * @return void
 */
void sortDoublePointerAndPointerArray(double * vector, int * pointers, int size){
    for(int i = 0; i < size - 1; i++){
        for(int k = i+1; k < size; k++){
            if(vector[k] < vector[i]){
                double placeholder = vector[i];
                int pointerPlaceholder = pointers[i];
                pointers[i] = pointers[k];
                pointers[k] = pointerPlaceholder;
                vector[i] = vector[k];
                vector[k] = placeholder;
            }
        }
    }
}

/**
 * makeShuffledIntPointer: creates a vector of consecutive numbers (0, 1, ..., N-1) that are shuffled and returned
 *
 * This is used for unique random numbers in a range from 0 to N-1.
 *
 * @param int size: the size of the returned vector
 * @param int numOfShuffledVals: the number of values to be shuffled
 * @param int randSeed: a seed for random
 * @return int * : containing the newly shuffled unique numbers
 */
int * makeShuffledIntPointer(int size, int numOfShuffledValues, int randSeed){

    init_genrand(randSeed);

    int * indices = (int *) calloc(size, sizeof(int));

    if(!indices){
        fprintf(stderr, "Shuffling failed to allocate the necessary memory.");
        exit(-1);
    }

    for(int i = 0; i < size; i++) {
        indices[i] = i;
    }

    shuffle(indices, size, genrand_int31(), numOfShuffledValues);
    return indices;
}