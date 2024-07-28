#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printResultCase1(int rows, int cols, int up , int down, int right, int middle, int left, int currentRow){
    int output[rows][cols];
    memset(output, 0, sizeof(output));
    output[up][left] = 1;
    output[up][middle] = 1;
    output[currentRow][left] = 1;
    output[currentRow][right] = 1;
    output[down][right] = 1;
    output[down][middle] = 1;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d", output[i][j]);
        }
        printf("\n");
    }
    printf("**********************\n");
}

int printResultCase2(int rows, int cols, int up , int down, int right, int middle, int left, int currentRow){
    int output[rows][cols];
    memset(output, 0, sizeof(output));
    output[down][left] = 1;
    output[down][middle] = 1;
    output[currentRow][left] = 1;
    output[currentRow][right] = 1;
    output[up][right] = 1;
    output[up][middle] = 1;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d", output[i][j]);
        }
        printf("\n");
    }
    printf("**********************\n");
}

int main(){
    FILE *file = fopen("week3.txt", "r");
    if (file == NULL) {
        printf("無法打開文件\n");
        exit(1);
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    int matrix[rows][cols];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    int numOfN6 = 0;

    for(int currentRow = 1; currentRow < rows - 1; currentRow++){
        for(int left = 0; left < cols - 2; left++){
            if(matrix[currentRow][left] == 0) continue;
            for(int right = left + 2; right < cols; right++){
                if(matrix[currentRow][right] == 0) continue;
                //左上右下
                for(int up = currentRow - 1; up >= 0; up--){
                    if(matrix[up][left] == 0) continue;
                    for(int down = currentRow + 1; down < rows; down++){
                        if(matrix[down][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){
                            if(matrix[up][middle] == matrix[down][middle] == 1){
                                numOfN6++;
                                printResultCase1(rows, cols, up , down, right, middle, left, currentRow);
                                //printf("%d %d %d %d %d %d\n", up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
                //左下右上
                for(int down = currentRow + 1; down < rows; down++){
                    if(matrix[down][left] == 0) continue;
                    for(int up = currentRow - 1; up >= 0; up--){
                        if(matrix[up][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){
                            if(matrix[down][middle] == matrix[up][middle] == 1){
                                numOfN6++;
                                printResultCase2(rows, cols, up , down, right, middle, left, currentRow);
                                //printf("%d %d %d %d %d %d\n", up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", numOfN6);

}


