// File: homework11_optimized.c
// Description: Polynomial addition using linked lists, optimized with a dummy
// head node.

#include <stdio.h>
#include <stdlib.h>

// 节点定义
typedef struct Node {
  int coef; // 系数
  int exp;  // 指数
  struct Node *next;
} Node;

// 函数原型
Node *PolyInput(void);
Node *PolyAdd(Node *p, Node *q);
void PolyOutput(Node *head);
void FreePoly(Node *head);

// 功能: 创建并输入一个多项式
Node *PolyInput(void) {
  int n, c, e;
  Node *head = NULL, *current = NULL;

  printf("输入多项式非零项的个数 n: ");
  scanf("%d", &n);
  if (n <= 0)
    return NULL;

  printf("请按指数递减的顺序，输入 %d 对系数和指数:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &c, &e);
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL; // 内存分配失败
    newNode->coef = c;
    newNode->exp = e;
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

// 功能: 输出一个多项式
void PolyOutput(Node *head) {
  if (!head) {
    printf("0\n");
    return;
  }
  Node *current = head;
  int isFirstTerm = 1;
  while (current != NULL) {
    if (current->coef == 0) { // 不打印系数为0的项
      current = current->next;
      continue;
    }
    // 控制符号显示
    if (current->coef > 0 && !isFirstTerm) {
      printf(" + ");
    } else if (current->coef < 0) {
      printf(" - ");
    }

    int abs_coef = abs(current->coef);

    // 系数处理
    if (abs_coef != 1 || current->exp == 0) {
      printf("%d", abs_coef);
    }

    // 指数处理
    if (current->exp > 0) {
      printf("x");
      if (current->exp > 1) {
        printf("^%d", current->exp);
      }
    }
    isFirstTerm = 0;
    current = current->next;
  }
  if (isFirstTerm) { // 如果所有项系数都为0
    printf("0");
  }
  printf("\n");
}

// 功能: 将两个多项式p和q相加 (使用虚拟头结点优化)
Node *PolyAdd(Node *p, Node *q) {
  // dummyHead 是一个栈上的临时节点，用作新链表的虚拟头。
  // 这使得我们无需特殊处理第一个节点的插入，代码更统一。
  Node dummyHead;
  dummyHead.next = NULL;
  Node *tail = &dummyHead; // tail 始终指向新链表的最后一个节点

  // 合并 p 和 q 中指数相同的项
  while (p != NULL && q != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL; // 内存分配失败

    if (p->exp > q->exp) {
      newNode->coef = p->coef;
      newNode->exp = p->exp;
      p = p->next;
    } else if (p->exp < q->exp) {
      newNode->coef = q->coef;
      newNode->exp = q->exp;
      q = q->next;
    } else { // 指数相同
      newNode->coef = p->coef + q->coef;
      newNode->exp = p->exp;
      p = p->next;
      q = q->next;
    }

    // 只有系数不为0的项才加入新链表
    if (newNode->coef != 0) {
      newNode->next = NULL;
      tail->next = newNode;
      tail = newNode;
    } else {
      free(newNode); // 系数为0的项，释放内存，不加入链表
    }
  }

  // 将 p 或 q 中剩余的项直接复制到新链表尾部
  Node *rest = (p != NULL) ? p : q;
  while (rest != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL;
    newNode->coef = rest->coef;
    newNode->exp = rest->exp;
    newNode->next = NULL;

    tail->next = newNode;
    tail = newNode;
    rest = rest->next;
  }

  return dummyHead.next; // 返回真正的新链表头
}

// 释放链表内存
void FreePoly(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
}

int main() {
  printf("--- 一元多项式相加 (优化版) ---\n");

  printf("\n创建第一个多项式:\n");
  Node *poly1 = PolyInput();

  printf("\n创建第二个多项式:\n");
  Node *poly2 = PolyInput();

  printf("\n第一个多项式: ");
  PolyOutput(poly1);
  printf("第二个多项式: ");
  PolyOutput(poly2);

  Node *sumPoly = PolyAdd(poly1, poly2);
  printf("\n相加结果: ");
  PolyOutput(sumPoly);

  // 释放所有链表的内存
  FreePoly(poly1);
  FreePoly(poly2);
  FreePoly(sumPoly);

  return 0;
}