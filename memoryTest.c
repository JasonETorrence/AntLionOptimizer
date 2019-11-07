#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillMatrix(double** matrix, int rows, int columns);
void fillMatrixRow(double* row, int size);
void printMatrix(double** matrix, int rows, int columns);

int main(){
	
	srand(time(0));
	
	int matrixRows = 16260;
	int matrixColumns = 16260;
	
	double ** matrix = (double**) calloc(matrixRows, sizeof(double*));
	if(!matrix){
		fprintf(stderr, "The program failed to allocate the necessary memory.");
		exit(-1);
	}
	
	for(int i = 0; i < matrixRows; i++){
		matrix[i] = (double*) calloc(matrixColumns, sizeof(double));
		if(!matrix[i]){
			fprintf(stderr, "The program failed to allocate the necessary memory.");
			exit(-1);
		}
	}
	
	fillMatrix(matrix, matrixRows, matrixColumns);
	//printMatrix(matrix, matrixRows, matrixColumns);
	
	for(int i = 0; i < matrixRows; i++){
		free(matrix[i]);
	}
	free(matrix);
	return 0;
	
}

void fillMatrix(double** matrix, int rows, int columns){
	for(int i = 0; i < rows; i++){
		fillMatrixRow(matrix[i], columns);
	}
}

void fillMatrixRow(double* row, int size){
	for(int i = 0; i < size; i++){
		row[i] = rand()/100;
	}
}

void printMatrix(double** matrix, int rows, int columns){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(j < columns-1){
				printf("%lf, ", matrix[i][j]);
			}else{
				printf("%lf", matrix[i][j]);
			}
		}	
		printf("\n");
	}
}