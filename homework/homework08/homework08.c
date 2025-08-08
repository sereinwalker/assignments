#include <ctype.h> // 用于 isalpha 函数
#include <stdio.h>
#include <string.h>

// --- 第一题: 合法的括号序列 ---
// 函数原型: int goodbrackets(char str[]);
// 功能: 判断字符串中的括号序列是否合法
int goodbrackets(char str[]) {
  int counter = 0; // 括号计数器
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      counter++;
    } else if (str[i] == ')') {
      counter--;
    }
    // 如果在任何时候计数器为负，说明右括号多于左括号，非法
    if (counter < 0) {
      return 0; // 返回0表示非法
    }
  }
  // 循环结束后，如果计数器为0，说明左右括号匹配，合法
  return (counter == 0); // 返回1表示合法，否则返回0
}

void task1_main() {
  char input_str[101];
  printf("--- 第一题: 合法的括号序列 ---\n");
  printf("输入带括号的字符串: ");
  // 使用fgets读取一行，可以包含空格
  fgets(input_str, sizeof(input_str), stdin);
  // 移除fgets可能带来的换行符
  input_str[strcspn(input_str, "\n")] = 0;

  if (goodbrackets(input_str)) {
    printf("输出: true\n");
  } else {
    printf("输出: false\n");
  }
}

// --- 第二题: 求转置矩阵 ---
// 函数原型: void transpose(int matrix[][5]);
// 功能: 将5x5矩阵进行转置
void transpose(int matrix[][5]) {
  int temp;
  for (int i = 0; i < 5; i++) {
    // j从i+1开始，避免重复交换和对角线元素的交换
    for (int j = i + 1; j < 5; j++) {
      // 交换 matrix[i][j] 和 matrix[j][i]
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }
}

void task2_main() {
  int a[5][5] = {{1, 2, 3, 4, 5},
                 {6, 7, 8, 9, 10},
                 {11, 12, 13, 14, 15},
                 {16, 17, 18, 19, 20},
                 {21, 22, 23, 24, 25}};
  printf("--- 第二题: 求转置矩阵 ---\n");
  printf("原始矩阵:\n");
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%-4d", a[i][j]);
    }
    printf("\n");
  }

  transpose(a); // 调用函数进行转置

  printf("\n转置后的矩阵:\n");
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%-4d", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// --- 第三题: 统计单词个数 ---
// 函数原型: int wordcounter(char str[]);
// 功能: 统计由连续英文字母或连字符构成的单词数量
int wordcounter(char str[]) {
  int count = 0;
  int in_word = 0; // 状态标志：0表示在单词外，1表示在单词内

  for (int i = 0; str[i] != '\0'; i++) {
    // 如果当前字符是字母或连字符
    if (isalpha(str[i]) || str[i] == '-') {
      if (in_word == 0) {
        // 如果之前不在单词内，说明一个新单词开始了
        in_word = 1;
        count++;
      }
    } else {
      // 如果是分隔符，则标记为不在单词内
      in_word = 0;
    }
  }
  return count;
}

void task3_main() {
  char input_str[101];
  printf("--- 第三题: 统计单词个数 ---\n");
  printf("输入一行字符串: ");
  fgets(input_str, sizeof(input_str), stdin);
  input_str[strcspn(input_str, "\n")] = 0;

  int count = wordcounter(input_str);
  printf("样例输出: %d\n", count);
}

int main() {
  printf("《计算机程序设计》作业 08 - 函数\n");
  task1_main();
  task2_main();
  task3_main();
  return 0;
}