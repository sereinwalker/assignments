#include <math.h> // 用于 pow 函数
#include <stdio.h>
#include <stdlib.h> // 用于 atof 函数
#include <string.h>

// --- 第一题: 带参数的宏 ---
// 注意: __func__ 是 C99 标准特性。
#define swap(A, B, TYPE)                                                       \
  do {                                                                         \
    TYPE temp = A;                                                             \
    A = B;                                                                     \
    B = temp;                                                                  \
    printf("宏在第 %d 行, 函数 %s 中被调用。\n", __LINE__, __func__);          \
  } while (0)

void task1_main() {
  printf("--- 第一题: 带参数的宏 ---\n");

  int int_a, int_b;
  float float_a, float_b;
  char char_a, char_b;

  printf("输入两个整数: ");
  scanf("%d %d", &int_a, &int_b);
  printf("交换前: a=%d, b=%d\n", int_a, int_b);
  swap(int_a, int_b, int);
  printf("交换后: a=%d, b=%d\n", int_a, int_b);

  printf("输入两个浮点数: ");
  scanf("%f %f", &float_a, &float_b);
  printf("交换前: a=%.2f, b=%.2f\n", float_a, float_b);
  swap(float_a, float_b, float);
  printf("交换后: a=%.2f, b=%.2f\n", float_a, float_b);

  // 读取字符前清除输入缓冲区
  while (getchar() != '\n')
    ;
  printf("输入两个字符: ");
  scanf("%c %c", &char_a, &char_b);
  printf("交换前: a='%c', b='%c'\n", char_a, char_b);
  swap(char_a, char_b, char);
  printf("交换后: a='%c', b='%c'\n", char_a, char_b);
}

// --- 第二题: 循环右移字符串 (指针实现) ---
// 辅助函数：使用指针反转字符串的一部分
void reverse(char *start, char *end) {
  while (start < end) {
    char temp = *start;
    *start = *end;
    *end = temp;
    start++;
    end--;
  }
}

// 右移主函数
void shift_right(char *str, int n) {
  int len = strlen(str);
  if (len == 0)
    return;
  n = n % len; // 有效处理大的 n 值

  // 循环移位的三步反转算法
  reverse(str + len - n, str + len - 1); // 反转最后 n 个字符
  reverse(str, str + len - n - 1);       // 反转前 (len-n) 个字符
  reverse(str, str + len - 1);           // 反转整个字符串
}

void task2_main() {
  char str[51];
  int n;
  printf("--- 第二题: 循环右移字符串 ---\n");
  printf("输入字符串 (最长50字符): ");
  scanf("%50s", str); // 最多读取50个字符以防止缓冲区溢出
  printf("输入右移位数 n: ");
  scanf("%d", &n);

  shift_right(str, n);
  printf("输出样例: %s\n", str);
}

// --- 第三题: 求n个实数的方差 ---
// 函数原型: double variance(double *x, int n);
double variance(double *x, int n) {
  if (n <= 1)
    return 0.0; // n<=1时方差无定义

  double sum = 0.0;
  double mean;
  double sum_sq_diff = 0.0;

  // 计算平均值
  for (int i = 0; i < n; i++) {
    sum += *(x + i);
  }
  mean = sum / n;

  // 计算与平均值差的平方和
  for (int i = 0; i < n; i++) {
    sum_sq_diff += pow(*(x + i) - mean, 2);
  }

  // 返回样本方差
  return sum_sq_diff / (n - 1);
}

void task3_main() {
  int n;
  double x[100]; // 假设最多100个数字
  printf("--- 第三题: 求n个实数的方差 ---\n");
  printf("输入实数个数 n: ");
  scanf("%d", &n);
  printf("输入 %d 个实数:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &x[i]);
  }
  printf("方差为: %f\n", variance(x, n));
}

// 主函数处理可选的命令行部分
int main(int argc, char *argv[]) {
  // 检查是否为任务3提供了命令行参数
  if (argc > 2 && strcmp(argv[1], "variance") == 0) {
    printf("--- 第三题 (选做): 通过命令行参数求方差 ---\n");
    int n = argc - 2;
    double *nums = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
      nums[i] = atof(argv[i + 2]);
    }
    printf("输入的 %d 个数为:", n);
    for (int i = 0; i < n; i++)
      printf(" %.2f", nums[i]);
    printf("\n");

    printf("方差为: %f\n", variance(nums, n));
    free(nums);
  } else {
    // 如果没有特定的命令行参数，则运行标准的实验任务
    printf("《上机实验 07》\n");
    task1_main();
    task2_main();
    task3_main();
  }
  return 0;
}