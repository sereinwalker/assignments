#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 在 Windows 上使用 Sleep, 在 Linux/macOS 上使用 usleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x) * 1000)
#endif

// 函数原型
void evolution(int M, int N, char (**current_grid_ptr)[N],
               char (**next_grid_ptr)[N], int num_generations);
void print_grid(int M, int N, char (*grid)[N]);
int count_live_neighbors(int M, int N, char (*grid)[N], int r, int c);

// 功能: 计算一个细胞周围的8个邻居中有多少是活的
int count_live_neighbors(int M, int N, char (*grid)[N], int r, int c) {
  int count = 0;
  // 遍历周围的 3x3 区域
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue; // 跳过细胞本身

      int neighbor_r = r + i;
      int neighbor_c = c + j;

      // 检查边界，确保邻居坐标在网格范围内
      if (neighbor_r >= 0 && neighbor_r < M && neighbor_c >= 0 &&
          neighbor_c < N) {
        if (grid[neighbor_r][neighbor_c] == '*') {
          count++;
        }
      }
    }
  }
  return count;
}

// 功能: 实现生命网格n代的进化 (通过交换指针优化)
void evolution(int M, int N, char (**current_grid_ptr)[N],
               char (**next_grid_ptr)[N], int num_generations) {
  for (int gen = 0; gen < num_generations; gen++) {
    // 清屏 (适用于Windows和Linux/macOS)
    system("clear || cls");
    printf("第 %d 代:\n", gen + 1);
    print_grid(M, N, *current_grid_ptr);
    Sleep(200); // 暂停 0.2 秒

    // 根据 current_grid 的状态计算 next_grid 的状态
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live_neighbors =
            count_live_neighbors(M, N, *current_grid_ptr, i, j);

        // 应用康威生命游戏经典规则
        if ((*current_grid_ptr)[i][j] == '*') { // 如果当前是活细胞
          if (live_neighbors < 2 || live_neighbors > 3) {
            (*next_grid_ptr)[i][j] = '-'; // 死亡 (孤独或拥挤)
          } else {
            (*next_grid_ptr)[i][j] = '*'; // 生存 (2或3个邻居)
          }
        } else { // 如果当前是死细胞
          if (live_neighbors == 3) {
            (*next_grid_ptr)[i][j] = '*'; // 再生
          } else {
            (*next_grid_ptr)[i][j] = '-'; // 保持死亡
          }
        }
      }
    }

    // 交换指针，避免了 O(M*N) 的数据复制。
    // 这使得演化一代的时间复杂度变为 O(1) (不计计算和绘制的时间)。
    char (*temp_ptr)[N] = *current_grid_ptr;
    *current_grid_ptr = *next_grid_ptr;
    *next_grid_ptr = temp_ptr;
  }
}

// 打印网格
void print_grid(int M, int N, char (*grid)[N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int M, N, n;
  double live_prob = 0.3; // 初始活细胞的概率

  printf("--- 生命游戏 (优化版) ---\n");
  printf("输入网格大小 M, N 和进化代数 n (用空格分隔): ");
  scanf("%d %d %d", &M, &N, &n);

  // 动态分配两个网格，一个作为当前代，一个用于计算下一代
  char (*lifeMatrix)[N] = malloc(M * sizeof(*lifeMatrix));
  char (*next_gen_matrix)[N] = malloc(M * sizeof(*next_gen_matrix));
  if (lifeMatrix == NULL || next_gen_matrix == NULL) {
    printf("内存分配失败\n");
    free(lifeMatrix);
    free(next_gen_matrix);
    return 1;
  }

  // 初始化网格
  srand(time(NULL));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      lifeMatrix[i][j] = ((double)rand() / RAND_MAX < live_prob) ? '*' : '-';
    }
  }

  printf("初始状态 (第0代):\n");
  print_grid(M, N, lifeMatrix);
  Sleep(1000); // 暂停1秒观察初始状态

  // 开始进化，传递指针的地址
  evolution(M, N, &lifeMatrix, &next_gen_matrix, n);

  printf("\n进化 %d 代后的最终状态:\n", n);
  print_grid(M, N, lifeMatrix); // 最终的 lifeMatrix 指向的是最后一代的结果

  // 释放两个网格的内存
  free(lifeMatrix);
  free(next_gen_matrix);

  return 0;
}