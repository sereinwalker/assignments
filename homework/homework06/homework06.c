#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 辅助函数: 打印数组
void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// --- 第一题: 随机数排序 ---
void sort_random_numbers() {
  int data[20];
  int i;
  // 生成随机数
  srand(time(NULL));
  for (i = 0; i < 20; i++) {
    data[i] = rand() % 101; // 值域 [0 .. 100]
  }

  printf("--- 第一题: 随机数排序 ---\n");
  printf("原始随机数组: ");
  print_array(data, 20);

  // 冒泡排序
  int bubble_data[20];
  for (i = 0; i < 20; i++)
    bubble_data[i] = data[i]; // 复制数组
  for (i = 0; i < 19; i++) {
    for (int j = 0; j < 19 - i; j++) {
      if (bubble_data[j] > bubble_data[j + 1]) {
        int temp = bubble_data[j];
        bubble_data[j] = bubble_data[j + 1];
        bubble_data[j + 1] = temp;
      }
    }
  }
  printf("冒泡排序后: ");
  print_array(bubble_data, 20);

  // 插入排序
  int insertion_data[20];
  for (i = 0; i < 20; i++)
    insertion_data[i] = data[i]; // 复制数组
  for (i = 1; i < 20; i++) {
    int key = insertion_data[i];
    int j = i - 1;
    while (j >= 0 && insertion_data[j] > key) {
      insertion_data[j + 1] = insertion_data[j];
      j = j - 1;
    }
    insertion_data[j + 1] = key;
  }
  printf("插入排序后: ");
  print_array(insertion_data, 20);
  printf("\n");
}

// --- 第二题: 合并两个有序数组 ---
void merge_arrays() {
  int a[20] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  int b[10] = {1, 43, 72, 23, 9, 87, 54, 3, 55, 0};
  int num_elements_in_a = 10;

  printf("--- 第二题: 合并两个有序数组 ---\n");
  printf("原始数组 a: ");
  print_array(a, num_elements_in_a);
  printf("原始数组 b: ");
  print_array(b, 10);

  // 将b中的元素逐个插入到a中，并保持a的有序性
  for (int i = 0; i < 10; i++) {
    int key = b[i];
    int j = num_elements_in_a - 1;

    // 找到key在a中合适的插入位置
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j]; // 将元素后移
      j--;
    }
    a[j + 1] = key;      // 插入key
    num_elements_in_a++; // a中的元素数量增加
  }

  printf("合并并排序后的数组 a: ");
  print_array(a, 20);
  printf("\n");
}

// --- 第三题: 矩阵相乘 ---
void multiply_matrices() {
  int A[5][5] = {{1, 2, 3, 4, 5},
                 {6, 7, 8, 9, 10},
                 {11, 12, 13, 14, 15},
                 {16, 17, 18, 19, 20},
                 {21, 22, 23, 24, 25}};
  int B[5][3] = {{3, 0, 16}, {17, -6, 9}, {0, 23, -4}, {9, 7, 0}, {4, 13, 11}};
  int C[5][3] = {0}; // 初始化为0

  printf("--- 第三题: 矩阵相乘 ---\n");

  // C = A * B
  for (int i = 0; i < 5; i++) {     // C的行
    for (int j = 0; j < 3; j++) {   // C的列
      for (int k = 0; k < 5; k++) { // A的列 / B的行
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  printf("结果矩阵 C = A * B:\n");
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%-5d", C[i][j]); // 左对齐，宽度为5
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  printf("《计算机程序设计》作业 06 - 数组\n");
  sort_random_numbers();
  merge_arrays();
  multiply_matrices();
  return 0;
}