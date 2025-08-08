#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// --- 第一题: 恺撒加密与解密 ---
void task1_caesar_cipher() {
  char filename[100];
  int choice, shift;

  printf("--- 第一题: 恺撒加密与解密 ---\n");
  printf("请选择操作 (1: 加密, 2: 解密): ");
  scanf("%d", &choice);
  printf("请输入文件名: ");
  scanf("%s", filename);
  printf("请输入偏移量 n: ");
  scanf("%d", &shift);

  // 以读写方式打开文件
  FILE *fp = fopen(filename, "r+");
  if (fp == NULL) {
    printf("错误: 无法打开文件 %s\n", filename);
    return;
  }

  // 确定实际的移位方向
  if (choice == 2) {
    shift = -shift; // 解密是向后移位
  }

  // 将整个文件读入缓冲区
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, 1, fsize, fp);
  buffer[fsize] = '\0';

  // 对缓冲区中的内容进行加密/解密
  for (int i = 0; buffer[i] != '\0'; i++) {
    if (isalpha(buffer[i])) {
      char base = islower(buffer[i]) ? 'a' : 'A';
      // 应用移位并处理回绕
      buffer[i] = (buffer[i] - base + shift % 26 + 26) % 26 + base;
    }
  }

  // 将修改后的缓冲区写回文件
  rewind(fp);
  fwrite(buffer, 1, fsize, fp);

  printf("操作完成。\n");

  fclose(fp);
  free(buffer);
}

// --- 第二题: 比较两个文本文件是否相同 ---
// 这个任务最好在 main 函数中处理命令行参数
void task2_file_compare(int argc, char *argv[]) {
  printf("--- 第二题: 比较两个文本文件是否相同 ---\n");
  if (argc < 3) {
    printf("用法: %s <file1> <file2>\n", argv[0]);
    return;
  }

  FILE *f1 = fopen(argv[1], "rb");
  FILE *f2 = fopen(argv[2], "rb");

  if (f1 == NULL) {
    printf("无法打开文件: %s\n", argv[1]);
    if (f2 != NULL)
      fclose(f2);
    return;
  }
  if (f2 == NULL) {
    printf("无法打开文件: %s\n", argv[2]);
    fclose(f1);
    return;
  }

  // 比较文件大小
  fseek(f1, 0, SEEK_END);
  long size1 = ftell(f1);
  fseek(f2, 0, SEEK_END);
  long size2 = ftell(f2);
  rewind(f1);
  rewind(f2);

  printf("比较文件 '%s' (大小: %ld字节) 和 '%s' (大小: %ld字节)\n", argv[1],
         size1, argv[2], size2);
  if (size1 != size2) {
    printf("文件大小不同，文件不相同。\n");
    fclose(f1);
    fclose(f2);
    return;
  }

  // 逐字节比较内容
  int ch1, ch2;
  long pos = 0;
  while ((ch1 = fgetc(f1)) != EOF) {
    ch2 = fgetc(f2);
    pos++;
    if (ch1 != ch2) {
      printf("文件在位置 %ld 处发现不同。\n", pos);
      fclose(f1);
      fclose(f2);
      return;
    }
  }

  printf("相同\n");
  fclose(f1);
  fclose(f2);
}

int main(int argc, char *argv[]) {
  // 检查是否提供了用于文件比较的参数
  if (argc == 3) {
    task2_file_compare(argc, argv);
  } else {
    printf("《上机实验 10》\n");
    task1_caesar_cipher();
    printf("要执行文件比较, 请使用命令行: %s a.txt b.txt\n", argv[0]);
  }

  return 0;
}