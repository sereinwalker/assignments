#include <stdio.h>
#include <string.h>

#define N 10 // For Task 3

// --- 第一题: 计算给定日期是本年度第几天 ---

// 检查是否为闰年的函数
int is_leap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 函数原型: int day_of_year(int year, int month, int day);
// 计算给定日期是其年份的第几天。
int day_of_year(int year, int month, int day) {
  int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int day_count = 0;

  // 为闰年进行调整
  if (is_leap(year)) {
    days_in_month[2] = 29;
  }

  // 加上前面几个月的天数
  for (int i = 1; i < month; i++) {
    day_count += days_in_month[i];
  }

  // 加上当月的天数
  day_count += day;

  return day_count;
}

void task1_main() {
  int year, month, day;
  printf("--- 第一题: 计算给定日期是本年度第几天 ---\n");
  printf("请输入日期 (格式 yyyy-mm-dd, yyyy/mm/dd, 或 yyyy,mm,dd): ");

  // 使用 scanf 灵活处理不同的分隔符
  if (scanf("%d[-/,]%d[-/,]%d", &year, &month, &day) == 3) {
    int day_num = day_of_year(year, month, day);
    printf("%d年%d月%d日 是当年的第 %d 天。\n", year, month, day, day_num);
  } else {
    printf("输入格式错误。\n");
  }
  // 为下一个任务清除输入缓冲区
  while (getchar() != '\n')
    ;
}

// --- 第二题: 替换字符串中的指定字符 ---

// 函数原型: void get_string(char s[]);
// 读取一行字符串输入。
void get_string(char s[]) {
  printf("输入字符串: ");
  fgets(s, 100, stdin);
  // 移除 fgets 产生的末尾换行符
  s[strcspn(s, "\n")] = 0;
}

// 函数原型: void replace_char(char s[], char c1, char c2);
// 将字符串 s 中所有出现的 c1 替换为 c2。
void replace_char(char s[], char c1, char c2) {
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == c1) {
      s[i] = c2;
    }
  }
}

void task2_main() {
  char str[100];
  char c1, c2;

  printf("--- 第二题: 替换字符串中的指定字符 ---\n");
  get_string(str);

  printf("输入两个字符 c1 c2: ");
  scanf(" %c %c", &c1, &c2); // 注意 %c 前的空格用于消耗空白字符

  replace_char(str, c1, c2);
  printf("输出结果: %s\n", str);
  // 为下一个任务清除输入缓冲区
  while (getchar() != '\n')
    ;
}

// --- 第三题: 判定数字序列是升序或者降序 ---

// 函数原型: int get_array(int a[]);
// 将数字序列读入数组，并返回计数。
int get_array(int a[]) {
  int count = 0;
  printf("输入一个数字序列 (按回车结束):\n");
  while (count < N && scanf("%d", &a[count]) == 1) {
    count++;
  }
  // 清除输入行剩余的内容
  while (getchar() != '\n')
    ;
  return count;
}

// 函数原型: int is_asc_or_desc(int a[], int n);
// 检查数组是严格升序(1)、严格降序(-1)还是两者都不是(0)。
int is_asc_or_desc(int a[], int n) {
  if (n < 2)
    return 0; // 少于2个元素无法判断顺序

  int is_ascending = 1;
  int is_descending = 1;

  for (int i = 0; i < n - 1; i++) {
    if (a[i] >= a[i + 1]) {
      is_ascending = 0;
    }
    if (a[i] <= a[i + 1]) {
      is_descending = 0;
    }
  }

  if (is_ascending)
    return 1;
  if (is_descending)
    return -1;
  return 0;
}

void task3_main() {
  int a[N];
  printf("--- 第三题: 判定数字序列是升序或者降序 ---\n");
  int n = get_array(a);
  int result = is_asc_or_desc(a, n);

  if (result == 1) {
    printf("序列是升序的。\n");
  } else if (result == -1) {
    printf("序列是降序的。\n");
  } else {
    printf("序列既非升序也非降序。\n");
  }
}

int main() {
  printf("《上机实验 06》\n");
  task1_main();
  task2_main();
  task3_main();
  return 0;
}