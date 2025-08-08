#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 第一题: 判定合法的括号序列,用指针实现 ---
int valid_brackets(char *str) {
  int counter = 0;
  // 使用指针遍历字符串，直到遇到空字符 '\0'
  while (*str) {
    if (*str == '(') {
      counter++;
    } else if (*str == ')') {
      counter--;
    }
    // 如果计数器为负，说明出现了未匹配的右括号
    if (counter < 0) {
      return 0; // 非法
    }
    str++; // 指针移动到下一个字符
  }
  // 如果最终计数器为0，则合法
  return (counter == 0);
}

void task1_main() {
  char input_str[101];
  printf("--- 第一题: 判定合法的括号序列 (指针实现) ---\n");
  printf("输入带括号的字符串: ");
  fgets(input_str, sizeof(input_str), stdin);
  input_str[strcspn(input_str, "\n")] = 0; // 移除换行符

  if (valid_brackets(input_str)) {
    printf("输出: true\n");
  } else {
    printf("输出: false\n");
  }
}

// --- 第二题: 方阵四角元素定位 ---
// 辅助函数：交换两个整数的值
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void place_min_in_corners(int n, int *matrix) {
  if (n < 3)
    return;

  int total_elements = n * n;
  int *elements = (int *)malloc(total_elements * sizeof(int));
  if (elements == NULL) {
    printf("内存分配失败\n");
    return;
  }
  // 复制所有元素到一个一维数组
  for (int i = 0; i < total_elements; i++) {
    *(elements + i) = *(matrix + i);
  }

  // 对一维数组进行排序，找到最小的4个元素
  for (int i = 0; i < total_elements - 1; i++) {
    for (int j = i + 1; j < total_elements; j++) {
      if (*(elements + i) > *(elements + j)) {
        swap(elements + i, elements + j);
      }
    }
  }

  // 最小的4个元素
  int min1 = *(elements);
  int min2 = *(elements + 1);
  int min3 = *(elements + 2);
  int min4 = *(elements + 3);

  // 找到原始矩阵中这4个元素的位置，并与四角元素交换
  // 为简化逻辑，直接将这4个元素赋值给四角
  // 剩下的元素填回矩阵的其余位置
  *(matrix) = min1;               // 左上角: matrix[0][0]
  *(matrix + n - 1) = min2;       // 右上角: matrix[0][n-1]
  *(matrix + n * (n - 1)) = min3; // 左下角: matrix[n-1][0]
  *(matrix + n * n - 1) = min4;   // 右下角: matrix[n-1][n-1]

  int current_other_idx = 4;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // 如果不是角点
      if (!((i == 0 && j == 0) || (i == 0 && j == n - 1) ||
            (i == n - 1 && j == 0) || (i == n - 1 && j == n - 1))) {
        *(matrix + i * n + j) = *(elements + current_other_idx++);
      }
    }
  }

  free(elements);
}

void task2_main() {
  int n;
  printf("--- 第二题: 方阵四角元素定位 ---\n");
  printf("输入方阵大小 n (n>=3): ");
  scanf("%d", &n);

  if (n < 3) {
    printf("n必须大于等于3\n");
    // 清理输入缓冲区
    while (getchar() != '\n')
      ;
    return;
  }

  int *matrix = (int *)malloc(n * n * sizeof(int));
  if (matrix == NULL) {
    printf("内存分配失败\n");
    return;
  }

  printf("输入 %d 个整数作为方阵元素:\n", n * n);
  for (int i = 0; i < n * n; i++) {
    scanf("%d", matrix + i);
  }

  place_min_in_corners(n, matrix);

  printf("\n处理后的方阵:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%-4d", *(matrix + i * n + j));
    }
    printf("\n");
  }
  printf("\n");
  free(matrix);
  // 清理输入缓冲区，为下一个任务做准备
  while (getchar() != '\n')
    ;
}

// --- 第三题: 国家名排序 ---
// 比较函数，用于按长度排序
int compare_by_length(const void *a, const void *b) {
  char *str1 = *(char **)a;
  char *str2 = *(char **)b;
  return strlen(str1) - strlen(str2);
}
// 比较函数，用于按字母顺序排序
int compare_by_alphabet(const void *a, const void *b) {
  char *str1 = *(char **)a;
  char *str2 = *(char **)b;
  return strcmp(str1, str2);
}

void task3_main() {
  char countries[10][40];
  char *index_by_length[10];
  char *index_by_alphabet[10];

  printf("--- 第三题: 国家名排序 ---\n");
  printf("请输入10个国家的名称，每行一个:\n");
  for (int i = 0; i < 10; i++) {
    fgets(countries[i], 40, stdin);
    countries[i][strcspn(countries[i], "\n")] = 0; // 移除换行符
    index_by_length[i] = countries[i];
    index_by_alphabet[i] = countries[i];
  }

  // 按长度排序
  qsort(index_by_length, 10, sizeof(char *), compare_by_length);
  printf("\n--- 按名称长度排序 ---\n");
  for (int i = 0; i < 10; i++) {
    printf("%s\n", index_by_length[i]);
  }

  // 按字母顺序排序
  qsort(index_by_alphabet, 10, sizeof(char *), compare_by_alphabet);
  printf("\n--- 按字母顺序 (ASCII) 排序 ---\n");
  for (int i = 0; i < 10; i++) {
    printf("%s\n", index_by_alphabet[i]);
  }
  printf("\n");
}

// --- 第四题: 选做 (通用定积分函数) ---
// 定义一个函数指针类型
typedef double (*MathFunc)(double);

// 通用定积分函数
double integrate(MathFunc f, double a, double b, int n) {
  double step = (b - a) / n;
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    double x = a + i * step;
    sum += f(x) * step; // 矩形面积
  }
  return sum;
}

void task4_main() {
  printf("--- 第四题: 选做 (通用定积分函数) ---\n");
  int n = 10000; // 划分的矩形数量，越多越精确

  // 1. 计算 sin(x) 在 [0, 1] 上的定积分
  double res1 = integrate(sin, 0.0, 1.0, n);
  printf("∫sin(x)dx [0, 1] ≈ %f\n",
         res1); // 理论值: -cos(1) - (-cos(0)) = 1 - cos(1) ≈ 0.4597

  // 2. 计算 cos(x) 在 [-1, 1] 上的定积分
  double res2 = integrate(cos, -1.0, 1.0, n);
  printf("∫cos(x)dx [-1, 1] ≈ %f\n",
         res2); // 理论值: sin(1) - sin(-1) = 2*sin(1) ≈ 1.6829

  // 3. 计算 e^x 在 [0, 2] 上的定积分
  double res3 = integrate(exp, 0.0, 2.0, n);
  printf("∫e^x dx [0, 2] ≈ %f\n",
         res3); // 理论值: e^2 - e^0 ≈ 7.389 - 1 = 6.389
}

int main() {
  task1_main();
  task2_main();
  task3_main();
  task4_main();
  return 0;
}