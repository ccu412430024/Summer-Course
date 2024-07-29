#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swapRows(int **matrix, int row1, int row2, int cols) {
    for (int i = 0; i < cols; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void gaussianElimination(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        // 找主元
        if (matrix[i][i] == 0) {
            for (int j = i + 1; j < rows; j++) {
                if (matrix[j][i] != 0) {
                    swapRows(matrix, i, j, cols);
                    break;
                }
            }
        }

        // 如果主元仍然為0，則跳過這一行
        if (matrix[i][i] == 0) continue;

        for (int j = i + 1; j < rows; j++) {
            if (matrix[j][i] == 0) continue;
            int factor = matrix[j][i];
            for (int k = 0; k < cols; k++) {
                matrix[j][k] = (matrix[j][k] - factor * matrix[i][k]) % 2;
            }
        }
    }
}

int isFullRank(int **matrix, int rows, int cols) {
    int rank = 0;
    for (int i = 0; i < rows; i++) {
        int nonZero = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                nonZero = 1;
                break;
            }
        }
        if (nonZero) {
            rank++;
        }
    }
    return rank == rows;
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows = 4;
    int cols = 8;

    // 生成同位檢測矩陣H
    int **H = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        H[i] = (int *)malloc(cols * sizeof(int));
    }

    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            H[i][j] = rand() % 2;
        }
    }

    printf("原始矩陣 H:\n");
    printMatrix(H, rows, cols);

    // 使用高斯消去法簡化矩陣
    gaussianElimination(H, rows, cols);

    printf("\n簡化後的矩陣 H:\n");
    printMatrix(H, rows, cols);

    // 檢查是否為Full Rank
    if (isFullRank(H, rows, cols)) {
        printf("\n矩陣 H 是 Full Rank\n");
    } else {
        printf("\n矩陣 H 不是 Full Rank\n");
    }

    for (int i = 0; i < rows; i++) {
        free(H[i]);
    }
    free(H);

    return 0;
}
