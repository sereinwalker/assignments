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
  printf("输入多项式非零项的个数 n: ");
  scanf("%d", &n);
  if (n <= 0)
    return NULL;

  printf("请依次输入 %d 对系数和指数（指数可任意顺序）：\n", n);
  Node *head = NULL;
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &c, &e);
    // 清空输入缓冲区，防止输入异常
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    if (c == 0)
      continue; // 忽略系数为0的项

    // 查找是否已存在相同指数的项
    Node *prev = NULL, *curr = head;
    while (curr != NULL && curr->exp > e) {
      prev = curr;
      curr = curr->next;
    }
    if (curr != NULL && curr->exp == e) {
      // 指数相同，合并系数
      curr->coef += c;
      if (curr->coef == 0) { // 合并后系数为0，删除该节点
        if (prev == NULL) {
          head = curr->next;
        } else {
          prev->next = curr->next;
        }
        free(curr);
      }
    } else {
      // 插入新节点
      Node *newNode = (Node *)malloc(sizeof(Node));
      if (!newNode)
        return NULL;
      newNode->coef = c;
      newNode->exp = e;
      if (prev == NULL) {
        newNode->next = head;
        head = newNode;
      } else {
        newNode->next = curr;
        prev->next = newNode;
      }
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
    if (current->exp != 0) {
      printf("x");
      if (current->exp > 1) {
        printf("^%d", current->exp);
      } else if (current->exp < 0) {
        printf("^(%d)", current->exp);
      }
    }
    isFirstTerm = 0;
    current = current->next;
  }
  printf("\n");
}

// 功能: 将两个多项式p和q相加 (使用虚拟头结点优化)
Node *PolyAdd(Node *p, Node *q) {
  Node dummyHead;
  dummyHead.next = NULL;
  Node *tail = &dummyHead;

  // 两链表已无重复指数，直接合并
  while (p != NULL && q != NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
      return NULL;
    if (p->exp > q->exp) {
      newNode->coef = p->coef;
      newNode->exp = p->exp;
      p = p->next;
    } else if (p->exp < q->exp) {
      newNode->coef = q->coef;
      newNode->exp = q->exp;
      q = q->next;
    } else {
      newNode->coef = p->coef + q->coef;
      newNode->exp = p->exp;
      p = p->next;
      q = q->next;
    }
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;
  }
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

  // 移除系数为0的项
  Node *prev = &dummyHead, *curr = dummyHead.next;
  while (curr != NULL) {
    if (curr->coef == 0) {
      prev->next = curr->next;
      free(curr);
      curr = prev->next;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  return dummyHead.next;
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
  printf("--- 一元多项式相加（输入时指数可任意顺序，程序自动排序）---\n");

  printf("\n创建第一个多项式（每项输入格式：系数 指数）：\n");
  Node *poly1 = PolyInput();

  printf("\n创建第二个多项式（每项输入格式：系数 指数）：\n");
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

  printf("\n按任意键退出...");
  getchar();
  return 0;
}