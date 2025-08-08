#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- 第一题: 带有“岗哨”的顺序查找 ---
void task1_sentinel_search() {
  int a[21]; // a[0] 用作岗哨
  int k;
  printf("--- 第一题: 带有“岗哨”的顺序查找 ---\n");

  // 在 a[1] 到 a[20] 中生成20个随机数
  srand(time(NULL));
  printf("生成的随机数: ");
  for (int i = 1; i <= 20; i++) {
    a[i] = rand() % 101;
    printf("%d ", a[i]);
  }
  printf("\n");

  printf("请输入要查找的整数 k: ");
  scanf("%d", &k);

  // 设置岗哨
  a[0] = k;

  // 从末尾开始查找
  int i = 20;
  while (a[i] != k) {
    i--;
  }

  if (i == 0) {
    printf("输出: not found\n");
  } else {
    printf("输出: k 在数组中的位置是 %d\n", i);
  }
}

// 打印数组的辅助函数
void print_data(const char *title, int data[], int size) {
  printf("%s", title);
  for (int i = 0; i < size; i++) {
    printf("%d ", data[i]);
  }
  printf("\n");
}

// --- 第二题: 冒泡排序 ---
void task2_bubble_sort() {
  int data1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 9}; // 近乎有序的数组
  int data2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // 逆序数组
  int comparisons, moves, i, j, temp;

  printf("--- 第二题: 冒泡排序 ---\n");

  // 排序 data1
  comparisons = 0;
  moves = 0;
  print_data("原始 data1: ", data1, 10);
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9 - i; j++) {
      comparisons++;
      if (data1[j] > data1[j + 1]) {
        temp = data1[j];
        moves++;
        data1[j] = data1[j + 1];
        moves++;
        data1[j + 1] = temp;
        moves++;
      }
    }
  }
  print_data("排序后 data1: ", data1, 10);
  printf("data1 排序统计 - 比较次数: %d, 移动次数: %d\n", comparisons, moves);

  // 排序 data2
  comparisons = 0;
  moves = 0;
  print_data("原始 data2: ", data2, 10);
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9 - i; j++) {
      comparisons++;
      if (data2[j] > data2[j + 1]) {
        temp = data2[j];
        moves++;
        data2[j] = data2[j + 1];
        moves++;
        data2[j + 1] = temp;
        moves++;
      }
    }
  }
  print_data("排序后 data2: ", data2, 10);
  printf("data2 排序统计 - 比较次数: %d, 移动次数: %d\n", comparisons, moves);
}

// --- 第三题: 插入排序 ---
void task3_insertion_sort() {
  int data1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 9};
  int data2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int comparisons, moves, i, j, key;

  printf("--- 第三题: 插入排序 ---\n");

  // 排序 data1
  comparisons = 0;
  moves = 0;
  print_data("原始 data1: ", data1, 10);
  for (i = 1; i < 10; i++) {
    key = data1[i];
    moves++;
    j = i - 1;
    while (j >= 0 && (comparisons++, data1[j] > key)) {
      data1[j + 1] = data1[j];
      moves++;
      j--;
    }
    data1[j + 1] = key;
    moves++;
  }
  print_data("排序后 data1: ", data1, 10);
  printf("data1 排序统计 - 比较次数: %d, 移动次数: %d\n", comparisons, moves);

  // 排序 data2
  comparisons = 0;
  moves = 0;
  print_data("原始 data2: ", data2, 10);
  for (i = 1; i < 10; i++) {
    key = data2[i];
    moves++;
    j = i - 1;
    while (j >= 0 && (comparisons++, data2[j] > key)) {
      data2[j + 1] = data2[j];
      moves++;
      j--;
    }
    data2[j + 1] = key;
    moves++;
  }
  print_data("排序后 data2: ", data2, 10);
  printf("data2 排序统计 - 比较次数: %d, 移动次数: %d\n", comparisons, moves);
  printf("分析结论: 对于近乎有序的数组(data1), "
         "插入排序的效率远高于冒泡排序。对于逆序数组(data2), 两者比较次数相同, "
         "但插入排序的移动次数更少, 性能稍好。\n");
}

// --- 附加练习: debug方法 ---
void debug_exercise() {
  printf("--- 附加练习: debug方法 ---\n");

// --- 修复后的代码 ---
#define SIZE 5
  int t = 1, s = 0;
  float average = 0;
  int array[SIZE] = {1, 3, 2, 6, 5};

  // 计算
  // 错误1: 数组越界 (i <= SIZE), 应为 i < SIZE
  for (int i = 0; i < SIZE; i++) {
    t *= array[i];
    s += array[i];
  }

  // 计算平均值
  // 错误2: 整除导致精度丢失, 应进行浮点数除法
  average = (float)s / SIZE;

  printf("修复后代码运行结果:\n");
  printf("t = %d\n", t);
  printf("Average = %.2f\n", average);
}

int main() {
  printf("《上机实验 05》\n");
  task1_sentinel_search();
  task2_bubble_sort();
  task3_insertion_sort();
  debug_exercise();
  return 0;
}