#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 在Windows环境下编译需要包含windows.h
#ifdef _WIN32
#include <windows.h>
#endif

// --- 第一题: 自制三角函数表 ---
// 函数原型
void table(double (*func)(double), const char *filename, double first,
           double last, double incr);

// 功能: 生成函数值表并写入文件
void table(double (*func)(double), const char *filename, double first,
           double last, double incr) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("无法打开文件 %s\n", filename);
    return;
  }

  fprintf(fp, "--- Function Table for %s ---\n", filename);
  fprintf(fp, "%-10s %-10s\n", "x", "f(x)");
  fprintf(fp, "----------------------\n");

  for (double x = first; x <= last; x += incr) {
    fprintf(fp, "%-10.4f %-10.4f\n", x, func(x));
  }

  fclose(fp);
  printf("已成功生成函数表: %s\n", filename);
}

void task1_main() {
  printf("--- 第一题: 自制三角函数表 ---\n");
  // 生成 sin(x) 表, 范围 [0, PI], 步进 PI/10
  table(sin, "sin_table.txt", 0.0, M_PI, M_PI / 10.0);

  // 生成 cos(x) 表
  table(cos, "cos_table.txt", 0.0, M_PI, M_PI / 10.0);

  // 生成 tan(x) 表
  table(tan, "tan_table.txt", 0.0, M_PI / 2.0 - 0.1,
        M_PI / 20.0); // 避开 tan(PI/2)
  printf("\n");
}

// --- 第二题: 演奏乐谱 ---
void task2_main() {
  printf("--- 第二题: 演奏乐谱 ---\n");

#ifndef _WIN32
  printf("此功能仅在Windows环境下可用。\n");
  return;
#else
  FILE *music_file = fopen("music.txt", "r");
  if (music_file == NULL) {
    printf("错误: 找不到乐谱文件 music.txt\n");
    printf("请确保 music.txt 与程序在同一目录下。\n");
    return;
  }

  DWORD freq, duration;
  printf("正在从 music.txt 读取乐谱并演奏...\n");
  // fscanf 返回成功读取的项目数，应为2
  while (fscanf(music_file, "%lu %lu", &freq, &duration) == 2) {
    printf("演奏: 频率 %lu Hz, 时长 %lu ms\n", freq, duration);
    if (freq >= 37 && freq <= 32767) {
      Beep(freq, duration);
    } else {
      // 如果频率为0或其他无效值，则表示休止
      Sleep(duration);
    }
  }

  printf("演奏完毕。\n");
  fclose(music_file);
#endif
}

int main() {
  task1_main();
  task2_main();
  return 0;
}