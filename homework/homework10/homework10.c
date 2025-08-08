#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // 用于 Windows 系统下的 Sleep() 函数

// 函数原型
void evolution(int M, int N, char (*lifeMatrix)[N], int n);
void print_grid(int M, int N, char (*matrix)[N]);

// 功能: 实现生命网格n代的进化
void evolution(int M, int N, char (*lifeMatrix)[N], int num_generations) {
  // 创建一个临时网格来存储下一代的状态
  char (*next_gen_matrix)[N] = malloc(M * sizeof(*next_gen_matrix));
  if (next_gen_matrix == NULL) {
    printf("内存分配失败\n");
    return;
  }

  for (int gen = 0; gen < num_generations; gen++) {
    system("clear || cls"); // 清屏 (Linux || Windows)
    printf("第 %d 代:\n", gen + 1);
    print_grid(M, N, lifeMatrix);
    Sleep(200); // 暂停0.2秒，方便观察

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live_neighbors = 0;
        // 检查周围4个邻居 (上下左右)
        if (i > 0 && lifeMatrix[i - 1][j] == '*')
          live_neighbors++; // 上
        if (i < M - 1 && lifeMatrix[i + 1][j] == '*')
          live_neighbors++; // 下
        if (j > 0 && lifeMatrix[i][j - 1] == '*')
          live_neighbors++; // 左
        if (j < N - 1 && lifeMatrix[i][j + 1] == '*')
          live_neighbors++; // 右

        // 应用生存规则
        if (lifeMatrix[i][j] == '*') { // 如果当前是活细胞
          if (live_neighbors < 2 || live_neighbors > 3) {
            next_gen_matrix[i][j] = '-'; // 死亡 (规则1和3)
          } else {
            next_gen_matrix[i][j] = '*'; // 生存 (规则2)
          }
        } else { // 如果当前是死细胞
          if (live_neighbors == 3) {
            next_gen_matrix[i][j] = '*'; // 再生 (规则4)
          } else {
            next_gen_matrix[i][j] = '-'; // 保持死亡
          }
        }
      }
    }

    // 将新一代的状态复制回原始网格
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        lifeMatrix[i][j] = next_gen_matrix[i][j];
      }
    }
  }
  free(next_gen_matrix);
}

// 打印网格
void print_grid(int M, int N, char (*matrix)[N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("%c ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int M, N, n;
  double live_prob = 0.3; // 初始活细胞的概率

  printf("--- 生命游戏 ---\n");
  printf("输入网格大小 M, N 和进化代数 n (用空格分隔): ");
  scanf("%d %d %d", &M, &N, &n);

  // 使用malloc动态分配二维数组
  // lifeMatrix 是一个指向含有N个char的数组的指针
  char (*lifeMatrix)[N] = malloc(M * sizeof(*lifeMatrix));
  if (lifeMatrix == NULL) {
    printf("内存分配失败\n");
    return 1;
  }

  // 初始化网格
  srand(time(NULL));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if ((double)rand() / RAND_MAX < live_prob) {
        lifeMatrix[i][j] = '*'; // 活细胞
      } else {
        lifeMatrix[i][j] = '-'; // 死细胞
      }
    }
  }

  printf("初始状态 (第0代):\n");
  print_grid(M, N, lifeMatrix);
  Sleep(1000); // 暂停1秒，方便观察初始状态 (Sleep参数为毫秒)
  // 开始进化
  evolution(M, N, lifeMatrix, n);

  printf("\n进化 %d 代后的最终状态:\n", n);
  print_grid(M, N, lifeMatrix);

  // 释放内存
  free(lifeMatrix);

  return 0;
}