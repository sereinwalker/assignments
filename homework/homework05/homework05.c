#include <math.h>
#include <stdio.h>

// --- 第一题: 打印弗洛伊德三角形 ---
void floyds_triangle() {
  int n, i, j, k = 1;
  printf("--- 第一题: 弗洛伊德三角形 ---\n");
  printf("输入行数 n (n>=2): ");
  scanf("%d", &n);

  printf("输出样例:\n");
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= i; j++) {
      printf("%d ", k++);
    }
    printf("\n");
  }
  printf("\n");
}

// --- 第二题: 输出倒置的弗洛伊德三角形 ---
void inverted_floyds_triangle() {
  int n, i, j;
  printf("--- 第二题: 倒置的弗洛伊德三角形 ---\n");
  printf("输入行数 n (n>=2): ");
  scanf("%d", &n);

  // 首先计算出总共有多少个数字 (即第n个三角数)
  int total_numbers = n * (n + 1) / 2;

  printf("输出样例:\n");
  for (i = n; i >= 1; i--) {
    // 计算当前行的起始数字
    int start_num = total_numbers - i * (i - 1) / 2 - i + 1;
    for (j = 0; j < i; j++) {
      printf("%d ", start_num + j);
    }
    printf("\n");
  }
  printf("\n");
}

// --- 第三题: 连续素数和 ---
// 辅助函数: 判断一个数是否为素数
int is_prime(int num) {
  if (num <= 1)
    return 0; // 1和负数不是素数
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0)
      return 0; // 如果能被整除，则不是素数
  }
  return 1; // 是素数
}

void sum_of_primes() {
  int n, count = 0, sum = 0;
  int primes[10]; // 存储找到的素数
  printf("--- 第三题: 连续素数和 ---\n");
  printf("输入正整数 n: ");
  scanf("%d", &n);

  // 从n开始递减查找素数
  for (int i = n; i >= 2 && count < 10; i--) {
    if (is_prime(i)) {
      primes[count] = i;
      sum += i;
      count++;
    }
  }

  // 根据找到的素数个数进行输出
  if (count < 10) {
    printf("failed.\n");
  } else {
    printf("输出样例: ");
    for (int i = 0; i < 9; i++) {
      printf("%d + ", primes[i]);
    }
    printf("%d = %d\n", primes[9], sum);
  }
  printf("\n");
}

// --- 第四题: 约分 ---
// 辅助函数: 计算最大公约数 (辗转相除法)
int gcd(int a, int b) {
  int temp;
  while (b != 0) {
    temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

void simplify_fraction() {
  int numerator, denominator;
  printf("--- 第四题: 约分 ---\n");
  printf("输入一个分数 (格式 a/b): ");
  scanf("%d/%d", &numerator, &denominator);

  if (denominator == 0) {
    printf("分母不能为0!\n");
    return;
  }

  int common_divisor = gcd(numerator, denominator);

  // 约分
  int sim_num = numerator / common_divisor;
  int sim_den = denominator / common_divisor;

  printf("输出样例: %d/%d\n", sim_num, sim_den);
  printf("\n");
}

int main() {
  printf("《计算机程序设计》作业 05 - 循环\n");
  floyds_triangle();
  inverted_floyds_triangle();
  sum_of_primes();
  simplify_fraction();
  return 0;
}