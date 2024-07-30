#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "nml.h"

//定義列數、行數以及列權重和行權重
#define ROWS 48
#define COLS 96
#define ROW_WEIGHT 6
#define COL_WEIGHT 3

//陣列洗牌函數
void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//生成行權重為3，列權重為6的矩陣
void generateMatrix(int matrix[ROWS][COLS]) {
    int colWeights[COLS] = {0}; //記錄每行權重
    int indices[COLS];  //索引陣列
    
    //初始化索引陣列
    for (int i = 0; i < COLS; i++) {
        indices[i] = i;
    }

    srand(time(NULL));  //隨機種子

    bool error; //是否有error(通常是某矩陣無論如何增減元素都無法符合行權重為3，列權重為6)
    do{
        error = 0;
        //初始化矩陣
        for (int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j ++)
            matrix[i][j] = 0;
        }
        memset(colWeights, 0, sizeof(colWeights));  //初始化行權重陣列
        // 給矩陣的每列分配1
        for (int i = 0; i < ROWS; i++) {
            // 將索引陣列打亂
            shuffle(indices, COLS);
            // 將索引對應的前6個元素設為1
            for (int j = 0; j < ROW_WEIGHT; j++) {
                matrix[i][indices[j]] = 1;
                colWeights[indices[j]]++;   //該行權重加1
            }
        }

        //檢查並修正每行的1的數量
        for (int j = 0; j < COLS; j++) {
        //修正1的數量少於3的行
            while (colWeights[j] < COL_WEIGHT) {
                int row;
                //找到一列來將0改為1
                do {
                    row = rand() % ROWS;
                } while (matrix[row][j] == 1);
                //找到一行來將1改為0
                int switchCol;
                int try = 0;
                do {
                    switchCol = rand() % COLS;
                    try++;
                    //嘗試次數太多則為error
                    if(try > 100){
                        error = 1;
                        break;
                    }
                } while (matrix[row][switchCol] == 0 || colWeights[switchCol] <= COL_WEIGHT);
                if(error == 1)  break;  //error則跳出
                //執行交換
                matrix[row][j] = 1; //將選中的0改為1
                matrix[row][switchCol] = 0; //將選中的1改為0
                //更新行權重
                colWeights[j]++;
                colWeights[switchCol]--;
            }
            //修正1的數量大於3的行
            while (colWeights[j] > COL_WEIGHT) {
                int row;
                //找到一列來將1改為0
                do {
                    row = rand() % ROWS;
                } while (matrix[row][j] == 0);
                //找到一行來將0改為1
                int switchCol;
                int try = 0;
                do {
                    switchCol = rand() % COLS;
                    try++;
                    //嘗試次數太多則為error
                    if(try > 100){
                        error = 1;
                        break;
                    }
                } while (matrix[row][switchCol] == 1 || colWeights[switchCol] >= COL_WEIGHT);
                if(error == 1)  break;  //error則跳出
                //執行交換
                matrix[row][j] = 0; //將選中的1改為0
                matrix[row][switchCol] = 1; //將選中的0改為1
                //更新行權重
                colWeights[j]--;
                colWeights[switchCol]++;
            }
            if(error == 1)  break;  //有error則跳出
        }

    }while(error);  //有error則重新生成矩陣
}

//將矩陣轉換為列階梯形矩陣
void rowEchelonForm(int matrix[ROWS][COLS]) {

    //將整數矩陣轉換為浮點數矩陣
    nml_mat *m1;
    m1 = nml_mat_new(ROWS, COLS);
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            nml_mat_set(m1, row, col, (double)matrix[row][col]);
        }
    }
    nml_mat *refm1 = nml_mat_ref(m1);   //高斯消去法產生列階梯形矩陣
    //將浮點數矩陣轉換為整數矩陣
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            matrix[row][col] = (int)nml_mat_get(refm1, row, col);
        }
    }
    //釋放浮點數矩陣
    nml_mat_free(m1);
    nml_mat_free(refm1);
}

int main(){
	int matrix[ROWS][COLS] = {0};   //初始化矩陣
    bool fullRank = 0;  //是否為full rank(否則重新生成)
    do{
        generateMatrix(matrix); //生成行權重為3，列權重為6的矩陣
        //輸出該矩陣
        printf("Original Form:\n");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        rowEchelonForm(matrix); //將矩陣轉換為列階梯形矩陣
        //計算矩陣的秩
        int rank = 0;
        for(int currentRow = 0; currentRow < ROWS; currentRow++){
            for(int currentCol = 0; currentCol < COLS; currentCol++){
                if(matrix[currentRow][currentCol] == 1){
                    rank++;
                    break;
                }
            }
        }
        //檢查是否為full rank
        if(rank == ROWS){
            fullRank = 1;
        }
    }while(fullRank == 0);  //不是full rank則重新生成
    
    //輸出結果(列階梯形矩陣)
    printf("Row Echelon Form:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
	return 0;
}