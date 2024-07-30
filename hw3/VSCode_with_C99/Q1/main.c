#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//輸出左上右下8字型
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

//輸出左下右上8字型
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
        return(1);
    }

    //讀取矩陣
    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    int matrix[rows][cols];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);

    //計算N(4)
    int numOfN4 = 0;
    for(int up = 0; up < rows - 1; up++){
        for(int left = 0; left < cols - 1; left++){    //先找左上點
            if(matrix[up][left] == 0) continue;
            for(int right = left + 1; right < cols; right++){   //再找右上點
                if(matrix[up][right] == 0) continue;
                for(int down = up + 1; down < rows; down++){    //最後找左下、右下兩點
                    if(matrix[down][right] == 1 && matrix[down][left] == 1){
                        numOfN4++;
                    }
                }
            }
        }
    }

    //計算N(6)
    int numOfN6 = 0;
    for(int currentRow = 1; currentRow < rows - 1; currentRow++){
        for(int left = 0; left < cols - 2; left++){    //先找中間水平線左邊的1
            if(matrix[currentRow][left] == 0) continue;
            for(int right = left + 2; right < cols; right++){   //再找中間水平線右邊的1
                if(matrix[currentRow][right] == 0) continue;
                //左上右下8字型
                for(int up = currentRow - 1; up >= 0; up--){    //先找左上點
                    if(matrix[up][left] == 0) continue;
                    for(int down = currentRow + 1; down < rows; down++){    //再找右下點
                        if(matrix[down][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){   //最後找中間垂直線的上下兩點
                            if(matrix[up][middle] == 1 && matrix[down][middle] == 1){
                                numOfN6++;
                                //printResultCase1(rows, cols, up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
                //左下右上8字型
                for(int down = currentRow + 1; down < rows; down++){    //先找左下點
                    if(matrix[down][left] == 0) continue;
                    for(int up = currentRow - 1; up >= 0; up--){    //再找右上點
                        if(matrix[up][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){   //最後找中間垂直線的上下兩點
                            if(matrix[down][middle] == 1 && matrix[up][middle] == 1){
                                numOfN6++;
                                //printResultCase2(rows, cols, up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("N(4): %d\n", numOfN4);
    printf("N(6): %d\n", numOfN6);
    
    return 0;
}


