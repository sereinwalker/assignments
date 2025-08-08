#include <stdio.h>

// 第一题函数
void printStarPattern() {
  printf("--- 第一题: 输出星号 ---\n");
  printf("    *\n");
  printf("   ***\n");
  printf("  *****\n");
  printf(" *******\n");
  printf("  *****\n");
  printf("   ***\n");
  printf("    *\n");
  printf("\n");
}

// 第二题函数
void findMaxOfThree() {
  int num1, num2, num3;
  printf("--- 第二题: 输入三个整数,输出较大的值 ---\n");
  printf("请输入三个整数 (用空格分隔): ");
  scanf("%d %d %d", &num1, &num2, &num3);

  int max = num1; // 先假设第一个是最大值

  if (num2 > max) {
    max = num2;
  }
  if (num3 > max) {
    max = num3;
  }

  printf("三个数中最大的值为: %d\n", max);
}

// 第三题函数
void convertFahrenheitToCelsius() {
  float fahrenheit, celsius;
  printf("--- 第三题: 华氏度转换为摄氏度 ---\n");
  printf("请输入华氏度值: ");
  scanf("%f", &fahrenheit);

  celsius = (5.0 / 9.0) * (fahrenheit - 32); // 使用 5.0/9.0 进行浮点数除法

  printf("%.2f 华氏度等于 %.2f 摄氏度.\n", fahrenheit, celsius);
}

int main() {
  printf("《计算机程序设计》作业 02\n");

  // 执行第一题
  printStarPattern();

  // 执行第二题
  findMaxOfThree();

  // 执行第三题
  convertFahrenheitToCelsius();

  return 0;
}