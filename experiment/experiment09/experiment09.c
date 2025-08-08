#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 第一题: 用结构体数组实现学生成绩表 ---
struct student_array {
  int stunum;
  char name[20];
  float examscore;
  float labscore;
  float totalmark;
};

void task1_main() {
  struct student_array stutable[10] = {
      {71250, "李霞", 95, 82, 0},   {69753, "李友友", 88, 86, 0},
      {12254, "东方亮", 87, 88, 0}, {61256, "张男", 73, 85, 0},
      {30258, "孙杰", 25, 88, 0},   {11260, "柯以乐", 82, 76, 0},
      {33262, "谢涛", 91, 85, 0},   {29263, "叶林", 80, 75, 0},
      {22483, "陈翔", 80, 76, 0},   {71525, "王子", 71, 88, 0}};

  printf("--- 第一题: 用结构体数组实现学生成绩表 ---\n");
  // 1. 计算总分并排序
  for (int i = 0; i < 10; i++) {
    stutable[i].totalmark =
        stutable[i].examscore * 0.6 + stutable[i].labscore * 0.4;
  }

  // 按总分降序进行冒泡排序
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9 - i; j++) {
      if (stutable[j].totalmark < stutable[j + 1].totalmark) {
        struct student_array temp = stutable[j];
        stutable[j] = stutable[j + 1];
        stutable[j + 1] = temp;
      }
    }
  }

  printf("排序后的学生成绩表:\n");
  printf("%-10s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "考试成绩",
         "实验成绩", "总评成绩");
  for (int i = 0; i < 10; i++) {
    printf("%-10d %-10s %-10.1f %-10.1f %-10.2f\n", stutable[i].stunum,
           stutable[i].name, stutable[i].examscore, stutable[i].labscore,
           stutable[i].totalmark);
  }
  printf("\n");

  // 2. 查找指定分数范围内的学生
  int a, b;
  printf("查找: 输入总评分数范围 a b (如 80 90): ");
  scanf("%d %d", &a, &b);
  printf("总评分数在 [%d, %d] 之间的学生有:\n", a, b);
  int found = 0;
  for (int i = 0; i < 10; i++) {
    if (stutable[i].totalmark >= a && stutable[i].totalmark <= b) {
      printf("%-10d %-10s %-10.2f\n", stutable[i].stunum, stutable[i].name,
             stutable[i].totalmark);
      found = 1;
    }
  }
  if (!found) {
    printf("未找到该分数段的学生。\n");
  }
  printf("\n");
}

// --- 第二题: 用链表实现学生成绩表 ---
struct student_node {
  int stunum;
  char name[20];
  float score;
  struct student_node *next;
};

// 函数原型: struct student_node* buildlist(int n);
struct student_node *buildlist(int n) {
  struct student_node *head = NULL, *current = NULL, *newNode;
  for (int i = 0; i < n; i++) {
    newNode = (struct student_node *)malloc(sizeof(struct student_node));
    printf("输入第 %d 个学生的学号、姓名、成绩: ", i + 1);
    scanf("%d %s %f", &newNode->stunum, newNode->name, &newNode->score);
    newNode->next = NULL;

    if (head == NULL) {
      head = current = newNode;
    } else {
      current->next = newNode;
      current = newNode;
    }
  }
  return head;
}

// 函数原型: void printlist(struct student_node *head);
void printlist(struct student_node *head) {
  printf("\n链表中的所有学生数据:\n");
  printf("%-10s %-10s %-10s\n", "学号", "姓名", "成绩");
  struct student_node *current = head;
  while (current != NULL) {
    printf("%-10d %-10s %-10.1f\n", current->stunum, current->name,
           current->score);
    current = current->next;
  }
}

// 函数原型: void searchlist(struct student_node *head, char *name);
void searchlist(struct student_node *head, char *name) {
  struct student_node *current = head;
  int found = 0;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
      printf("找到学生 %s, 成绩为: %.1f\n", name, current->score);
      found = 1;
      break;
    }
    current = current->next;
  }
  if (!found) {
    printf("不存在\n");
  }
}

// 释放链表使用的内存
void freelist(struct student_node *head) {
  struct student_node *current = head;
  while (current != NULL) {
    struct student_node *temp = current;
    current = current->next;
    free(temp);
  }
}

void task2_main() {
  int n;
  char search_name[20];
  printf("--- 第二题: 用链表实现学生成绩表 ---\n");
  printf("输入要建立链表的学生人数: ");
  scanf("%d", &n);

  struct student_node *head = buildlist(n);
  printlist(head);

  printf("\n输入要查找的学生姓名: ");
  scanf("%s", search_name);
  searchlist(head, search_name);

  freelist(head); // 清理内存
}

int main() {
  printf("《上机实验 09》\n");
  task1_main();
  task2_main();
  return 0;
}