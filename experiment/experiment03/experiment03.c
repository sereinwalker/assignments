#include <math.h>
#include <stdio.h>

// 第一题: 求π的近似值
void task1_approximate_pi() {
  double pi_quarter = 0.0;
  double term;
  int i = 1;
  int sign = 1;

  printf("--- 第一题: 求π的近似值 ---\n");

  do {
    term = (double)sign / (2 * i - 1);
    pi_quarter += term;
    sign = -sign;
    i++;
  } while (fabs(term) > 1e-6);

  printf("π的近似值为: %.6f\n", pi_quarter * 4);
}

// 第二题: 验证哥德巴赫猜想
// 辅助函数：检查一个数是否为素数
int is_prime(int n) {
  if (n <= 1)
    return 0;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

void task2_goldbach_conjecture() {
  printf("--- 第二题: 验证哥德巴赫猜想 ---\n");
  printf("将 [6, 100] 区间的偶数表示为两个素数之和:\n");
  for (int even_num = 6; even_num <= 100; even_num += 2) {
    for (int p1 = 3; p1 <= even_num / 2; p1 += 2) {
      if (is_prime(p1)) {
        int p2 = even_num - p1;
        if (is_prime(p2)) {
          printf("%d=%d+%d\n", even_num, p1, p2);
        }
      }
    }
  }
  printf("\n");
}

// 第三题: 打印菱形图案
void task3_print_diamond() {
  int n;
  printf("--- 第三题: 打印菱形图案 ---\n");
  printf("输入一个奇数 n: ");
  scanf("%d", &n);

  if (n % 2 == 0) {
    printf("输入不是奇数, 无法打印菱形。\n");
    return;
  }

  // 打印包括中间行的上半部分
  for (int i = 1; i <= n; i += 2) {
    // 打印前导空格
    for (int j = 0; j < (n - i) / 2; j++) {
      printf(" ");
    }
    // 打印星号
    for (int j = 0; j < i; j++) {
      printf("*");
    }
    printf("\n");
  }

  // 打印下半部分
  for (int i = n - 2; i >= 1; i -= 2) {
    // 打印前导空格
    for (int j = 0; j < (n - i) / 2; j++) {
      printf(" ");
    }
    // 打印星号
    for (int j = 0; j < i; j++) {
      printf("*");
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  printf("《上机实验 03》\n");
  task1_approximate_pi();
  task2_goldbach_conjecture();
  task3_print_diamond();
  return 0;
}