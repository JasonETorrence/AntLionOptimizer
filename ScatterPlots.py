# Made by Jason Torrence on 10/18/2019
#
# DO NOT DELETE ANY COMMENT LINES OR COMMENTS
#
# Designed for use on optimization results files containing the matrices for a
# specific algorithm. The first two dimensions are placed on a scatter plot to
# get an 'idea' as to what it happening over time to each vector.
#
# ============================================================================
# THINGS THAT ARE REQUIRED TO MAKE THIS WORK CORRECTLY:
# ============================================================================
#
# 1. The results file path, location to save, and other values are set
#       correctly, and the results are saved as a CSV.
# 2. The matrix in the results file is set up EXACTLY AS FOLLOWS:
#       a. All matrices are printed such that each line is a single vector
#       b. There is no line separation between matrices (if the matrix is
#           made up of 500 vectors, the first matrix takes up lines 1-500,
#           the second matrix is on lines 501-1000, the third is on 1001-1500
#           and so on.)
#
# ============================================================================
# ============================================================================

import csv
import matplotlib.pyplot as plt

# ============================================================================
# CHANGE THE FOLLOWING TO MATCH YOUR FILE NAMES AND SIZES
# ============================================================================
populationSize = 500
iterations = 200
results_file = 'C:/Users/sarge/Desktop/AntLionOptimizer/Results/AntResults.csv'
location_to_save_plots = 'C:\Users\sarge\Desktop\plots//'
plot_titles = 'Optimization'
# ============================================================================
# ============================================================================

# ============================================================================
# SCRIPT
# ============================================================================

# All of this can be adjusted to pull in multiple files or print to multiple
# locations if need be

csv_file = open(results_file, mode='r')
csv_reader = csv.reader(csv_file)
listOfValues = list(csv_reader)
x = [0]
y = [0]


black = (0,0,0)

matrix_count = 0

for i in range(iterations):

    line_count = 0
    for m in range(populationSize):

        if line_count == populationSize - 1:
            del x[0:1]
            del y[0:1]
            xFloat = [float(j) for j in x]
            yFloat = [float(j) for j in y]
            matrix_count += 1
            line_count = 0
            plt.scatter(xFloat, yFloat, c=(0, 0, 0), edgecolors='none', alpha=0.4)
            plt.title(plot_titles)
            plt.xlabel('x')
            plt.ylabel('y')
            x = [0]
            y = [0]
            break
        Line = listOfValues[line_count + (populationSize * matrix_count)]
        line_count += 1
        x.append(Line[0])
        y.append(Line[1])
    saveLocation = location_to_save_plots + 'Plot' + str(matrix_count) + '.png'
    plt.savefig(saveLocation)
    plt.clf()