#include <ctype.h> // 用于 islower(), isupper(), toupper() 函数
#include <stdio.h>

// 第一题: 判断点是否在正方形内
void task1_point_in_square() {
  float x, y;
  printf("--- 第一题: 判断点是否在正方形内 ---\n");
  printf("输入点的坐标 x y: ");
  scanf("%f %f", &x, &y);

  if (x >= -2.0 && x <= 2.0 && y >= -2.0 && y <= 2.0) {
    printf("输出: Yes\n");
  } else {
    printf("输出: No\n");
  }
}

// 第二题 (1): 使用if语句计算分段函数
void task2_piecewise_if() {
  float x, y;
  printf("--- 第二题 (1): 使用if语句计算分段函数 ---\n");
  printf("输入一个实数 x: ");
  scanf("%f", &x);

  if (x > 0 && x < 10) {
    y = x;
    printf("输出: x=%.6f时, y=%.6f\n", x, y);
  } else if (x >= 10 && x < 20) {
    y = x * x + 1;
    printf("输出: x=%.6f时, y=%.6f\n", x, y);
  } else if (x >= 20 && x < 30) {
    y = x * x * x + x * x + 1;
    printf("输出: x=%.6f时, y=%.6f\n", x, y);
  } else {
    printf("输出: x取值非法。\n");
  }
  printf("\n");
}

// 第二题 (2): 使用switch语句计算分段函数
void task2_piecewise_switch() {
  int x;
  long long y; // 使用 long long 类型的 y 来防止 x^3 溢出
  printf("--- 第二题 (2): 使用switch语句计算分段函数 ---\n");
  printf("输入一个整数 x: ");
  scanf("%d", &x);

  // 使用整数除法来确定 switch 语句的范围
  int range_indicator = x / 10;

  switch (range_indicator) {
  case 0:        // 对应 x 在 [0, 9] 的情况
    if (x > 0) { // 检查 (0, 10) 的条件
      y = x;
      printf("输出: x=%d时, y=%lld\n", x, y);
    } else {
      printf("输出: x取值非法。\n");
    }
    break;
  case 1: // 对应 x 在 [10, 19] 的情况
    y = (long long)x * x + 1;
    printf("输出: x=%d时, y=%lld\n", x, y);
    break;
  case 2: // 对应 x 在 [20, 29] 的情况
    y = (long long)x * x * x + (long long)x * x + 1;
    printf("输出: x=%d时, y=%lld\n", x, y);
    break;
  default:
    printf("输出: x取值非法。\n");
    break;
  }
  printf("\n");
}

// 第三题: 字符处理
void task3_char_processing() {
  char ch;
  printf("--- 第三题: 字符处理 ---\n");
  printf("循环输入字符 ('0' 退出):\n");

  // 在开始 getchar 循环之前清除输入缓冲区
  while (getchar() != '\n')
    ;

  while ((ch = getchar()) != '0') {
    if (ch == '\n')
      continue; // 忽略回车键

    if (islower(ch)) {
      printf("%c\n", toupper(ch));
    } else if (isupper(ch)) {
      printf("'%c'已经是大写字母\n", ch);
    } else {
      printf("'%c'不是字母\n", ch);
    }
  }
  printf("\n程序已退出。\n");
}

int main() {
  printf("《上机实验 02》\n");
  task1_point_in_square();
  task2_piecewise_if();
  task2_piecewise_switch();
  task3_char_processing();
  return 0;
}