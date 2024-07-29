#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ROWS 4
#define COLS 8
#define ROW_WEIGHT 6
#define COL_WEIGHT 3

void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generateMatrix(int matrix[ROWS][COLS]) {
    int colWeights[COLS] = {0};
    int indices[COLS];
    
    // Initialize the indices array
    for (int i = 0; i < COLS; i++) {
        indices[i] = i;
    }

    srand(time(NULL));

    // Assign 1s to each row
    for (int i = 0; i < ROWS; i++) {
        // Shuffle the indices array
        shuffle(indices, COLS);
        // Set the first ROW_WEIGHT elements to 1
        for (int j = 0; j < ROW_WEIGHT; j++) {
            matrix[i][indices[j]] = 1;
            colWeights[indices[j]]++;
        }
    }

    // Check and fix column weights
	for (int j = 0; j < COLS; j++) {
    // Fix columns with too few 1s
    while (colWeights[j] < COL_WEIGHT) {
        int row;
        // Find a row to switch a 0 to 1
        do {
            row = rand() % ROWS;
        } while (matrix[row][j] == 1);
        // Find a column to switch a 1 to 0
        int switchCol;
        do {
            switchCol = rand() % COLS;
        } while (matrix[row][switchCol] == 0 || colWeights[switchCol] <= COL_WEIGHT);
        // Perform the switch
        matrix[row][j] = 1;
        matrix[row][switchCol] = 0;
        colWeights[j]++;
        colWeights[switchCol]--;
    }
    // Fix columns with too many 1s
		while (colWeights[j] > COL_WEIGHT) {
			int row;
			// Find a row to switch a 1 to 0
			do {
				row = rand() % ROWS;
			} while (matrix[row][j] == 0);
			// Find a column to switch a 0 to 1
			int switchCol;
			do {
				switchCol = rand() % COLS;
			} while (matrix[row][switchCol] == 1 || colWeights[switchCol] >= COL_WEIGHT);
			// Perform the switch
			matrix[row][j] = 0;
			matrix[row][switchCol] = 1;
			colWeights[j]--;
			colWeights[switchCol]++;
		}
	}
}

void rowEchelonForm(int matrix[ROWS][COLS]) {
    int i, j, k, a, b;
    float tem;
    float mat[80][80];    
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            mat[i][j] = (double)matrix[i][j];
        }
    }
    // Program Logic
    for(k = 0; k < ROWS; k++) {
        // Ensure the pivot element is not zero
        if(mat[k][k] == 0) {
            for(i = k + 1; i < ROWS; i++) {
                if(mat[i][k] != 0) {
                    // Swap rows k and i
                    for(j = 0; j < COLS; j++) {
                        float temp = mat[k][j];
                        mat[k][j] = mat[i][j];
                        mat[i][j] = temp;
                    }
                    break;
                }
            }
        }
        
        if(mat[k][k] != 1) {
            float temp = mat[k][k];
            if(temp == 0)
                continue; // Avoiding division by zero
            for(j = 0; j < COLS; j++) {
                mat[k][j] = (mat[k][j]) / temp;
            }
        }
        
        for(i = k + 1; i < ROWS; i++) {
            tem = mat[i][k];
            for(j = k; j < COLS; j++) {
                mat[i][j] = mat[i][j] - (mat[k][j] * tem);
            }
        }

        // Printing Each Step
        printf("\n**************************\n");
        if(k == ROWS - 1)
            printf("Row Echelon form is : \n\n");
        else
            printf("Step %d\n\n", k + 1);
        for(a = 0; a < ROWS; a++) {
            for(b = 0; b < COLS; b++) {
                if(mat[a][b] == -0)
                    mat[a][b] = 0; // Simply converting '-0' into '0'
                printf("%.1f\t", mat[a][b]);
            }
            printf("\n");
        }
    }
}

int main(){
	int matrix[ROWS][COLS] = {0};
	generateMatrix(matrix);
	// Print the matrix
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
	printf("****************************\n");
	rowEchelonForm(matrix);

	return 0;
}