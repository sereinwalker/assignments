#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 第一题: 顺序查找和二分查找的比较 ---
void search_comparison() {
  int data[500];
  int key[10] = {9, 53, 368, 1064, 1753, 1, 271, 799, 1968, 1997};
  int i, j;

  printf("--- 第一题: 顺序查找和二分查找的比较 ---\n");

  // 初始化随机数生成器并生成数据
  srand(1);
  for (i = 0; i < 500; i++) {
    data[i] = rand() % 2000; // 值域 [0, 1999]
  }

  // 1. 顺序查找
  printf("\n1. 顺序查找 (在未排序数组中):\n");
  int seq_total_comps = 0, seq_found_count = 0;
  for (i = 0; i < 10; i++) {
    int comparisons = 0;
    int found = 0;
    for (j = 0; j < 500; j++) {
      comparisons++;
      if (data[j] == key[i]) {
        found = 1;
        break;
      }
    }
    printf("  - 查找 %-4d: %s, 比较次数: %d\n", key[i],
           found ? "存在" : "不存在", comparisons);
    if (found) {
      seq_total_comps += comparisons;
      seq_found_count++;
    }
  }
  if (seq_found_count > 0) {
    printf("  -> 顺序查找成功时的平均比较次数: %.2f\n",
           (float)seq_total_comps / seq_found_count);
  }

  // 2. 排序数组 (使用选择排序)
  printf("\n2. 使用选择法排序数组...\n");
  for (i = 0; i < 499; i++) {
    int min_idx = i;
    for (j = i + 1; j < 500; j++) {
      if (data[j] < data[min_idx]) {
        min_idx = j;
      }
    }
    int temp = data[min_idx];
    data[min_idx] = data[i];
    data[i] = temp;
  }
  printf("  排序完成.\n");

  // 3. 二分查找
  printf("\n3. 二分查找 (在已排序数组中):\n");
  int bin_total_comps = 0, bin_found_count = 0;
  for (i = 0; i < 10; i++) {
    int comparisons = 0;
    int found = 0;
    int low = 0, high = 499;
    while (low <= high) {
      comparisons++;
      int mid = low + (high - low) / 2;
      if (data[mid] == key[i]) {
        found = 1;
        break;
      } else if (data[mid] < key[i]) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    printf("  - 查找 %-4d: %s, 比较次数: %d\n", key[i],
           found ? "存在" : "不存在", comparisons);
    if (found) {
      bin_total_comps += comparisons;
      bin_found_count++;
    }
  }
  if (bin_found_count > 0) {
    printf("  -> 二分查找成功时的平均比较次数: %.2f\n",
           (float)bin_total_comps / bin_found_count);
  }
  printf("\n");
}

// --- 第二题: 连接数字串 ---
void concatenate_numbers() {
  int a, b;
  char str_a[20], str_b[20];
  char ab_str[40], ba_str[40];

  printf("--- 第二题: 连接数字串 ---\n");
  printf("请输入两个正整数 a 和 b: ");
  scanf("%d %d", &a, &b);

  // 将整数转换为字符串
  sprintf(str_a, "%d", a);
  sprintf(str_b, "%d", b);

  // 创建连接后的字符串 "ab"
  strcpy(ab_str, str_a);
  strcat(ab_str, str_b);

  // 创建连接后的字符串 "ba"
  strcpy(ba_str, str_b);
  strcat(ba_str, str_a);

  // 比较两个连接后的字符串，输出较大的那个
  // strcmp 返回值 > 0 表示第一个字符串更大
  if (strcmp(ab_str, ba_str) > 0) {
    printf("选择的较大数字串为: %s\n", ab_str);
  } else {
    printf("选择的较大数字串为: %s\n", ba_str);
  }
  printf("\n");
}

int main() {
  printf("《计算机程序设计》作业 07 - 查找与排序\n");
  search_comparison();
  concatenate_numbers();
  return 0;
}