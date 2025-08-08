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

// 功能: 创建并输入一个多项式，返回头指针
Node *PolyInput(void) {
  int n, c, e;
  Node *head = NULL, *current = NULL;

  printf("输入多项式非零项的个数 n: ");
  scanf("%d", &n);
  if (n > 0) {
    printf("输入 %d 对系数和指数:\n", n);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &c, &e);
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL;
    newNode->coef = c;
    newNode->exp = e;
    newNode->next = NULL;

    // 插入到链表尾部 (输入已按指数递减排列)
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
  while (current != NULL) {
    // 控制符号显示
    if (current->coef > 0 && current != head) {
      printf("+");
    }
    // 不显示系数为1的情况 (除非指数为0)
    if (current->coef == 1 && current->exp != 0) {
      printf("X^%d ", current->exp);
    } else if (current->coef == -1 && current->exp != 0) {
      printf("-X^%d ", current->exp);
    } else {
      printf("%dX^%d ", current->coef, current->exp);
    }
    current = current->next;
  }
  printf("\n");
}

// 功能: 将两个多项式p和q相加，返回新多项式的头指针
Node *PolyAdd(Node *p, Node *q) {
  Node *head = NULL, *tail = NULL;
  Node *ptr_p = p;
  Node *ptr_q = q;

  while (ptr_p != NULL && ptr_q != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL;
    newNode->next = NULL;

    if (ptr_p->exp > ptr_q->exp) {
      newNode->coef = ptr_p->coef;
      newNode->exp = ptr_p->exp;
      ptr_p = ptr_p->next;
    } else if (ptr_p->exp < ptr_q->exp) {
      newNode->coef = ptr_q->coef;
      newNode->exp = ptr_q->exp;
      ptr_q = ptr_q->next;
    } else { // 指数相同
      newNode->coef = ptr_p->coef + ptr_q->coef;
      newNode->exp = ptr_p->exp;
      ptr_p = ptr_p->next;
      ptr_q = ptr_q->next;
    }

    // 只有系数不为0的项才加入新链表
    if (newNode->coef != 0) {
      if (head == NULL) {
        head = tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
    } else {
      free(newNode); // 释放系数为0的节点
    }
  }

  // 将剩余的项连接到新链表尾部
  Node *rest = (ptr_p != NULL) ? ptr_p : ptr_q;
  while (rest != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL;
    newNode->coef = rest->coef;
    newNode->exp = rest->exp;
    newNode->next = NULL;

    if (head == NULL) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    rest = rest->next;
  }

  return head;
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
  printf("--- 两个一元多项式相加 ---\n");
  printf("创建第一个多项式:\n");
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