#include <stdio.h>
#include <stdlib.h>

// 計算特定行中1的數量
int count_ones_in_row(int* matrix, int row, int cols) {
    int count = 0;
    for (int j = 0; j < cols; j++) {
        if (matrix[row * cols + j] == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    const char* filename = "week3.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("無法打開文件\n");
        return 1;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    int* matrix = (int*)malloc(rows * cols * sizeof(int));
    if (matrix == NULL) {
        printf("內存分配失敗\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i * cols + j]);
        }
    }

    fclose(file);

    int check_node_4 = 3; // 第4個檢查節點，對應矩陣中的第4行（索引3）
    int check_node_6 = 5; // 第6個檢查節點，對應矩陣中的第6行（索引5）

    int count_4 = count_ones_in_row(matrix, check_node_4, cols);
    int count_6 = count_ones_in_row(matrix, check_node_6, cols);

    printf("第4個檢查節點連接的變數節點數量: %d\n", count_4);
    printf("第6個檢查節點連接的變數節點數量: %d\n", count_6);

    free(matrix);
    return 0;
}
