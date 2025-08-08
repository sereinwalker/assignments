#include <math.h> // 用于 fabs() 函数
#include <stdio.h>
#include <stdlib.h> // 用于 rand(), srand() 函数
#include <time.h>   // 用于 time() 函数

// 任务2: 计算两个实数差的绝对值
void task2_absolute_difference() {
  double num1, num2;
  printf("--- 任务2: 计算两实数差的绝对值 ---\n");
  printf("请输入两个实数 (用空格分隔): ");
  scanf("%lf %lf", &num1, &num2);

  double difference = fabs(num1 - num2);

  printf("输出样例: %.6f\n", difference);
}

// 任务3: 猜数字游戏
void task3_guess_the_number() {
  // 生成一个 [0, 10] 之间的随机数
  srand(time(NULL));
  int secret_number = rand() % 11;
  int guess;
  int tries = 0;
  int max_tries = 3;
  int guessed_correctly = 0;

  printf("--- 任务3: 猜数字游戏 ---\n");
  printf("我心里想了一个 [0, 10] 之间的整数, 你有 %d 次机会猜.\n", max_tries);

  while (tries < max_tries) {
    printf("请输入你的猜测: ");
    scanf("%d", &guess);
    tries++;

    if (guess == secret_number) {
      printf("猜对了!\n");
      guessed_correctly = 1;
      break; // 猜对就退出循环
    } else if (guess < secret_number) {
      printf("猜小了, 再来一次: ");
    } else {
      printf("猜大了, 再来一次: ");
    }

    if (tries < max_tries) {
      printf("你还有 %d 次机会.\n", max_tries - tries);
    }
  }

  if (!guessed_correctly) {
    printf("\n很遗憾, 3次机会都用完了. 正确答案是 %d.\n", secret_number);
  }
  printf("\n");
}

int main() {
  printf("《上机实验【1】》\n");

  // 执行任务2
  task2_absolute_difference();

  // 执行任务3
  task3_guess_the_number();

  return 0;
}