#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 6

int random_bit() {
    return rand() % 2;
}

void init_matrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = random_bit();
        }
    }
}

void print_matrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int is_full_rank(int matrix[ROWS][COLS]) {
    int rank = 0;
    for (int row = 0; row < ROWS; row++) {
        if (matrix[row][rank] == 0) {
            for (int i = row + 1; i < ROWS; i++) {
                if (matrix[i][rank] == 1) {
                    for (int j = 0; j < COLS; j++) {
                        int temp = matrix[row][j];
                        matrix[row][j] = matrix[i][j];
                        matrix[i][j] = temp;
                    }
                    break;
                }
            }
        }
        if (matrix[row][rank] == 1) {
            for (int i = 0; i < ROWS; i++) {
                if (i != row && matrix[i][rank] == 1) {
                    for (int j = 0; j < COLS; j++) {
                        matrix[i][j] ^= matrix[row][j];
                    }
                }
            }
            rank++;
        }
    }
    return rank == ROWS;
}

int main() {
    srand(time(NULL));
    int matrix[ROWS][COLS];

    init_matrix(matrix);
    print_matrix(matrix);

    if (is_full_rank(matrix)) {
        printf("矩陣是Full Rank\n");
    } else {
        printf("矩陣不是Full Rank\n");
    }

    return 0;
}
