#include <stdio.h>
#include <string.h>

// --- 第一题: 字符串循环右移 ---
// 辅助函数：反转字符串的一部分
void reverse(char *str, int start, int end) {
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

void task1_string_shift() {
  char str[51];
  int n;
  printf("--- 第一题: 字符串循环右移 ---\n");
  printf("输入字符串: ");
  scanf("%s", str);
  printf("输入右移位数 n: ");
  scanf("%d", &n);

  int len = strlen(str);
  if (len == 0) {
    printf("输出: \n");
    return;
  }
  n = n % len; // 规约 n 以避免不必要的完整旋转

  // 高效的三步反转算法
  reverse(str, 0, len - 1); // 1. 反转整个字符串
  reverse(str, 0, n - 1);   // 2. 反转前 n 个字符
  reverse(str, n, len - 1); // 3. 反转剩余部分

  printf("输出: %s\n", str);
}

// --- 第二题: 学生成绩处理 ---
// 定义一个结构体来存储学生数据
typedef struct {
  int id;
  int scores[3];
  double average;
} Student;

void task2_score_analysis() {
  Student students[50];
  int i, j;
  int count_over_85 = 0;

  printf("--- 第二题: 学生成绩处理 ---\n");
  printf("请使用输入重定向来从 score50.txt 读取数据 (e.g., a.exe < "
         "score50.txt)\n");

  // 1. 读取数据并计算每个学生的平均分
  for (i = 0; i < 50; i++) {
    students[i].id = i + 1;
    scanf("%d %d %d", &students[i].scores[0], &students[i].scores[1],
          &students[i].scores[2]);
    students[i].average = (students[i].scores[0] + students[i].scores[1] +
                           students[i].scores[2]) /
                          3.0;
    printf("学生 %d 的平均成绩: %.2f\n", students[i].id, students[i].average);

    // 2. 统计平均分大于等于85分的学生人数
    if (students[i].average >= 85.0) {
      count_over_85++;
    }
  }
  printf("\n平均成绩在85分及以上的人数: %d\n", count_over_85);

  // 3. 使用冒泡排序按平均分降序排序
  for (i = 0; i < 49; i++) {
    for (j = 0; j < 49 - i; j++) {
      if (students[j].average < students[j + 1].average) {
        Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }

  printf("\n按平均成绩从高到低排序后:\n");
  printf("排名  学生ID   平均分\n");
  for (i = 0; i < 50; i++) {
    printf("%-6d %-8d %-7.2f\n", i + 1, students[i].id, students[i].average);
  }
  printf("\n");
}

// --- 第三题: 约瑟夫问题 ---
void task3_josephus_problem() {
  int soldiers[101]; // soldiers[i] = 1 表示存活, 0 表示被淘汰
  int n, m;
  int i;

  printf("--- 第三题: 约瑟夫问题 ---\n");
  printf("输入人数 n 和报数 m: ");
  scanf("%d %d", &n, &m);

  if (n <= 0 || m <= 0 || n > 100) {
    printf("输入无效。\n");
    return;
  }

  // 初始化所有士兵为存活状态
  for (i = 1; i <= n; i++) {
    soldiers[i] = 1;
  }

  int num_left = n;    // 剩余士兵人数
  int count = 0;       // 当前报数 (1 到 m)
  int current_pos = 1; // 当前士兵索引 (1 到 n)

  while (num_left > 1) {
    if (soldiers[current_pos] == 1) { // 如果士兵还活着
      count++;
      if (count == m) {
        soldiers[current_pos] = 0; // 淘汰该士兵
        num_left--;
        count = 0; // 为下一个人重置报数
      }
    }
    // 移动到圈子里的下一个位置
    current_pos++;
    if (current_pos > n) {
      current_pos = 1; // 环绕
    }
  }

  // 找到最后剩下的士兵
  for (i = 1; i <= n; i++) {
    if (soldiers[i] == 1) {
      printf("最后留下的是 %d 号\n", i);
      break;
    }
  }
}

int main() {
  printf("《上机实验 04》\n");
  task1_string_shift();
  // task2_score_analysis(); // 取消此行注释并使用输入重定向来运行
  task3_josephus_problem();
  return 0;
}