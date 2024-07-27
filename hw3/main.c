#include <stdio.h>
#include <stdlib.h>

// �p��S�w�椤1���ƶq
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
        printf("�L�k���}���\n");
        return 1;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    int* matrix = (int*)malloc(rows * cols * sizeof(int));
    if (matrix == NULL) {
        printf("���s���t����\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i * cols + j]);
        }
    }

    fclose(file);

    int check_node_4 = 3; // ��4���ˬd�`�I�A�����x�}������4��]����3�^
    int check_node_6 = 5; // ��6���ˬd�`�I�A�����x�}������6��]����5�^

    int count_4 = count_ones_in_row(matrix, check_node_4, cols);
    int count_6 = count_ones_in_row(matrix, check_node_6, cols);

    printf("��4���ˬd�`�I�s�����ܼƸ`�I�ƶq: %d\n", count_4);
    printf("��6���ˬd�`�I�s�����ܼƸ`�I�ƶq: %d\n", count_6);

    free(matrix);
    return 0;
}
