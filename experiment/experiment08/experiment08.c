#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 第一题: "倒装句" ---
void reverse_string(char *start, char *end) {
  while (start < end) {
    char temp = *start;
    *start = *end;
    *end = temp;
    start++;
    end--;
  }
}

void task1_main() {
  char sentence[101];
  printf("--- 第一题: \"倒装句\" ---\n");
  printf("输入一句话: ");
  fgets(sentence, sizeof(sentence), stdin);
  sentence[strcspn(sentence, "\n")] = 0; // 移除换行符

  char *start = sentence, *end = sentence;

  // 1. 反转整个句子
  reverse_string(sentence, sentence + strlen(sentence) - 1);

  // 2. 将每个单词反转回来
  while (*end) {
    if (*end == ' ') {
      reverse_string(start, end - 1);
      start = end + 1;
    }
    end++;
  }
  // 反转最后一个单词
  reverse_string(start, end - 1);

  printf("输出样例: %s\n", sentence);
}

// --- 第二题: 求两个向量的内积 ---
// 函数原型: double inner_product(double *a, double *b, int n);
double inner_product(double *a, double *b, int n) {
  double product = 0.0;
  for (int i = 0; i < n; i++) {
    product += (*(a + i)) * (*(b + i));
  }
  return product;
}

void task2_main() {
  int n;
  double a[50], b[50];
  printf("--- 第二题: 求两个向量的内积 ---\n");
  printf("输入向量维数 n (<=50): ");
  scanf("%d", &n);

  printf("输入向量 a 的 %d 个元素:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
  }

  printf("输入向量 b 的 %d 个元素:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &b[i]);
  }

  double result = inner_product(a, b, n);
  printf("输出样例: %.6f\n", result);
}

// --- 第三题: 构建幻方 ---
// 函数原型: void generate_magic_square(int n, int (*magic_square)[n]);
void generate_magic_square(int n, int (*magic_square)[n]) {
  // 用0初始化矩阵
  memset(magic_square, 0, n * n * sizeof(int));

  // 数字1的起始位置
  int row = 0;
  int col = n / 2;

  for (int num = 1; num <= n * n; num++) {
    magic_square[row][col] = num;

    // 计算下一个位置（右上）
    int next_row = (row - 1 + n) % n;
    int next_col = (col + 1) % n;

    // 如果下一个位置已被填充，则向下移动
    if (magic_square[next_row][next_col] != 0) {
      row = (row + 1) % n;
    } else {
      row = next_row;
      col = next_col;
    }
  }
}

void task3_main() {
  int n;
  printf("--- 第三题: 构建幻方 ---\n");
  printf("输入幻方的阶数 n (奇数): ");
  scanf("%d", &n);

  if (n % 2 == 0) {
    printf("n必须是奇数。\n");
    return;
  }

  // 为 n x n 矩阵动态分配内存
  int (*magic_square)[n] = malloc(n * sizeof(*magic_square));
  if (magic_square == NULL) {
    printf("内存分配失败。\n");
    return;
  }

  // 生成幻方
  generate_magic_square(n, magic_square);

  // 打印结果
  printf("\n输出样例:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%-4d", magic_square[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  // 释放分配的内存
  free(magic_square);
}

int main() {
  printf("《上机实验 08》\n");
  task1_main();
  task2_main();
  task3_main();
  return 0;
}