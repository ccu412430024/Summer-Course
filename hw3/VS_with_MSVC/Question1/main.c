#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 10

//輸出左上右下8字型
void printResultCase1(int up , int down, int right, int middle, int left, int currentRow){
    int output[ROWS][COLS];
    memset(output, 0, sizeof(output));
    output[up][left] = 1;
    output[up][middle] = 1;
    output[currentRow][left] = 1;
    output[currentRow][right] = 1;
    output[down][right] = 1;
    output[down][middle] = 1;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%d", output[i][j]);
        }
        printf("\n");
    }
    printf("**********************\n");
}

//輸出左下右上8字型
void printResultCase2(int up , int down, int right, int middle, int left, int currentRow){
    int output[ROWS][COLS];
    memset(output, 0, sizeof(output));
    output[down][left] = 1;
    output[down][middle] = 1;
    output[currentRow][left] = 1;
    output[currentRow][right] = 1;
    output[up][right] = 1;
    output[up][middle] = 1;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
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
    fscanf_s(file, "%d %d", &rows, &cols);
    int matrix[ROWS][COLS];
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            fscanf_s(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);

    //計算N(4)
    int numOfN4 = 0;
    for(int up = 0; up < ROWS - 1; up++){
        for(int left = 0; left < COLS - 1; left++){    //先找左上點
            if(matrix[up][left] == 0) continue;
            for(int right = left + 1; right < COLS; right++){   //再找右上點
                if(matrix[up][right] == 0) continue;
                for(int down = up + 1; down < ROWS; down++){    //最後找左下、右下兩點
                    if(matrix[down][right] == 1 && matrix[down][left] == 1){
                        numOfN4++;
                    }
                }
            }
        }
    }

    //計算N(6)
    int numOfN6 = 0;
    //8字型
    for(int currentRow = 1; currentRow < ROWS - 1; currentRow++){
        for(int left = 0; left < COLS - 2; left++){    //先找中間水平線左邊的1
            if(matrix[currentRow][left] == 0) continue;
            for(int right = left + 2; right < COLS; right++){   //再找中間水平線右邊的1
                if(matrix[currentRow][right] == 0) continue;
                //左上右下8字型
                for(int up = currentRow - 1; up >= 0; up--){    //先找左上點
                    if(matrix[up][left] == 0) continue;
                    for(int down = currentRow + 1; down < ROWS; down++){    //再找右下點
                        if(matrix[down][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){   //最後找中間垂直線的上下兩點
                            if(matrix[up][middle] == 1 && matrix[down][middle] == 1){
                                numOfN6++;
                                //printResultCase1(up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
                //左下右上8字型
                for(int down = currentRow + 1; down < ROWS; down++){    //先找左下點
                    if(matrix[down][left] == 0) continue;
                    for(int up = currentRow - 1; up >= 0; up--){    //再找右上點
                        if(matrix[up][right] == 0) continue;
                        for(int middle = left + 1; middle < right; middle++){   //最後找中間垂直線的上下兩點
                            if(matrix[down][middle] == 1 && matrix[up][middle] == 1){
                                numOfN6++;
                                //printResultCase2(up , down, right, middle, left, currentRow);
                            }
                        }
                    }
                }
            }
        }
    }
    //L型
    for (int startRow = 0; startRow < ROWS; startRow++) {
        for (int startCol = 0; startCol < COLS; startCol++) {
            if (matrix[startRow][startCol] == 1) {
                //L型-1
                /*
                █
                █
                █
                █
                ████
                */
                //printf("L-1:\n");
                for (int down = startRow + 1; down < ROWS; down++) {
                    if (matrix[down][startCol] == 1) {
                        for (int right = startCol + 1; right < COLS; right++) {
                            if (matrix[down][right] == 1) {
                                for (int rightLineRow = down - 1; rightLineRow > startRow; rightLineRow--) {
                                    if (matrix[rightLineRow][right] == 1) {
                                        for (int upLineCol = startCol + 1; upLineCol < right; upLineCol++) {
                                            if (matrix[startRow][upLineCol] == 1) {
                                                if (matrix[rightLineRow][upLineCol] == 1) {
                                                    numOfN6++;
                                                    /*顯示圖形
                                                    int print[ROWS][COLS];
                                                    memset(print, 0, sizeof(print));
                                                    print[startRow][startCol] = 1;
                                                    print[down][startCol] = 1;
                                                    print[down][right] = 1;
                                                    print[rightLineRow][right] = 1;
                                                    print[startRow][upLineCol] = 1;
                                                    print[rightLineRow][upLineCol] = 1;
                                                    for (int i = 0; i < ROWS; i++) {
                                                        for (int j = 0; j < COLS; j++) {
                                                            printf("%d ", print[i][j]);
                                                        }
                                                        printf("\n");
                                                    }
                                                    printf("-------------------------\n");
                                                    */
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                //L型-2
                /*
                      █
                      █
                      █
                      █
                ████
                */
                //printf("L-2:\n");
                for (int down = startRow + 1; down < ROWS; down++) {
                    if (matrix[down][startCol] == 1) {
                        for (int left = startCol - 1; left >= 0; left--) {
                            if (matrix[down][left] == 1) {
                                for (int leftLineRow = down - 1; leftLineRow > startRow; leftLineRow--) {
                                    if (matrix[leftLineRow][left] == 1) {
                                        for (int upLineCol = startCol - 1; upLineCol > left; upLineCol--) {
                                            if (matrix[startRow][upLineCol] == 1) {
                                                if (matrix[leftLineRow][upLineCol] == 1) {
                                                    numOfN6++;
                                                    /*顯示圖形
                                                    int print[ROWS][COLS];
                                                    memset(print, 0, sizeof(print));
                                                    print[startRow][startCol] = 1;
                                                    print[down][startCol] = 1;
                                                    print[down][left] = 1;
                                                    print[leftLineRow][left] = 1;
                                                    print[startRow][upLineCol] = 1;
                                                    print[leftLineRow][upLineCol] = 1;
                                                    for (int i = 0; i < ROWS; i++) {
                                                        for (int j = 0; j < COLS; j++) {
                                                            printf("%d ", print[i][j]);
                                                        }
                                                        printf("\n");
                                                    }
                                                    printf("-------------------------\n");
                                                    */
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                //L型-3
                /*
                ████
                █
                █
                █
                █
                */
                //printf("L-3:\n");
                for (int up = startRow - 1; up >= 0; up--) {
                    if (matrix[up][startCol] == 1) {
                        for (int right = startCol + 1; right < COLS; right++) {
                            if (matrix[up][right] == 1) {
                                for (int rightLineRow = up + 1; rightLineRow < startRow; rightLineRow++) {
                                    if (matrix[rightLineRow][right] == 1) {
                                        for (int downLineCol = startCol + 1; downLineCol < right; downLineCol++) {
                                            if (matrix[startRow][downLineCol] == 1) {
                                                if (matrix[rightLineRow][downLineCol] == 1) {
                                                    numOfN6++;
                                                    /*顯示圖形
                                                    int print[ROWS][COLS];
                                                    memset(print, 0, sizeof(print));
                                                    print[startRow][startCol] = 1;
                                                    print[up][startCol] = 1;
                                                    print[up][right] = 1;
                                                    print[rightLineRow][right] = 1;
                                                    print[startRow][downLineCol] = 1;
                                                    print[rightLineRow][downLineCol] = 1;
                                                    for (int i = 0; i < ROWS; i++) {
                                                        for (int j = 0; j < COLS; j++) {
                                                            printf("%d ", print[i][j]);
                                                        }
                                                        printf("\n");
                                                    }
                                                    printf("-------------------------\n");
                                                    */
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                //L型-4
                /*
                ████
                      █
                      █
                      █
                      █
                */
                //printf("L-4:\n");
                for (int up = startRow - 1; up >= 0; up--) {
                    if (matrix[up][startCol] == 1) {
                        for (int left = startCol - 1; left >= 0; left--) {
                            if (matrix[up][left] == 1) {
                                for (int leftLineRow = up + 1; leftLineRow < startRow; leftLineRow++) {
                                    if (matrix[leftLineRow][left] == 1) {
                                        for (int downLineCol = startCol - 1; downLineCol > left; downLineCol--) {
                                            if (matrix[startRow][downLineCol] == 1) {
                                                if (matrix[leftLineRow][downLineCol] == 1) {
                                                    numOfN6++;
                                                    /*
                                                    int print[ROWS][COLS];
                                                    memset(print, 0, sizeof(print));
                                                    print[startRow][startCol] = 1;
                                                    print[up][startCol] = 1;
                                                    print[up][left] = 1;
                                                    print[leftLineRow][left] = 1;
                                                    print[startRow][downLineCol] = 1;
                                                    print[leftLineRow][downLineCol] = 1;
                                                    for (int i = 0; i < ROWS; i++) {
                                                        for (int j = 0; j < COLS; j++) {
                                                            printf("%d ", print[i][j]);
                                                        }
                                                        printf("\n");
                                                    }
                                                    printf("-------------------------\n");
                                                    */
                                                }
                                            }
                                        }
                                    }
                                }
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


