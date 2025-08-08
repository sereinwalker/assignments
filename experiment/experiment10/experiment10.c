#include <ctype.h>
#include <stdio.h>

// --- 第一题: 恺撒加密与解密 ---
void task1_caesar_cipher() {
  char filename[100];
  int choice, shift;

  printf("--- 恺撒加密与解密 (O(1)空间复杂度优化版) ---\n");
  printf("请选择操作 (1: 加密, 2: 解密): ");
  scanf("%d", &choice);
  printf("请输入文件名: ");
  scanf("%s", filename);
  printf("请输入偏移量 n: ");
  scanf("%d", &shift);

  FILE *fp = fopen(filename, "r+b");
  if (fp == NULL) {
    perror("错误: 无法打开文件");
    return;
  }

  if (choice == 2) {
    shift = -shift; // 解密即反向加密
  }
  // 将 shift 规范到 [-25, 25] 之间，处理大数值的偏移
  shift = shift % 26;

  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    if (isalpha(ch)) {
      char base = islower(ch) ? 'a' : 'A';
      // 计算加密后的字符，(shift % 26 + 26) % 26 优雅地处理了正负偏移
      char encrypted_ch = (ch - base + shift + 26) % 26 + base;

      // 1. 将文件指针移回当前字符的位置
      fseek(fp, -1L, SEEK_CUR);
      // 2. 将加密后的字符写回原位
      fputc(encrypted_ch, fp);
      // 3. fputc后，文件指针会自动前进。为了下一次循环的fgetc能读到
      //    文件的下一个字符，我们需要确保流的位置正确。
      //    fseek可以强制刷新流的位置。
      fseek(fp, 0L, SEEK_CUR);
    }
  }

  printf("操作完成。\n");
  fclose(fp);
}

// --- 第二题: 比较两个文本文件是否相同 ---
void task2_file_compare(const char *file1, const char *file2) {
  printf("\n--- 第二题: 比较文件 '%s' 和 '%s' ---\n", file1, file2);

  FILE *f1 = fopen(file1, "rb");
  FILE *f2 = fopen(file2, "rb");

  if (f1 == NULL) {
    printf("无法打开文件: %s\n", file1);
    if (f2 != NULL)
      fclose(f2);
    return;
  }
  if (f2 == NULL) {
    printf("无法打开文件: %s\n", file2);
    fclose(f1);
    return;
  }

  // 比较文件大小
  fseek(f1, 0, SEEK_END);
  long size1 = ftell(f1);
  fseek(f2, 0, SEEK_END);
  long size2 = ftell(f2);

  if (size1 != size2) {
    printf("文件不相同: 大小不同 (%ld vs %ld 字节)。\n", size1, size2);
    fclose(f1);
    fclose(f2);
    return;
  }

  // 回到文件开头
  rewind(f1);
  rewind(f2);

  // 逐字节比较内容
  int ch1, ch2;
  long pos = 0;
  while ((ch1 = fgetc(f1)) != EOF) {
    ch2 = fgetc(f2);
    pos++;
    if (ch1 != ch2) {
      printf("文件不相同: 在位置 %ld 处发现第一个差异。\n", pos);
      fclose(f1);
      fclose(f2);
      return;
    }
  }

  printf("文件相同。\n");
  fclose(f1);
  fclose(f2);
}

int main(int argc, char *argv[]) {
  // 检查是否提供了用于文件比较的命令行参数
  if (argc == 3) {
    // 如果提供了两个文件名作为参数，则执行文件比较功能
    task2_file_compare(argv[1], argv[2]);
  } else {
    // 否则，执行默认的恺撒密码功能
    printf("《上机实验 10 (优化版)》\n");
    task1_caesar_cipher();
    printf("\n提示: 要执行文件比较功能, 请使用命令行调用:\n");
    printf("%s <file1> <file2>\n", argv[0]);
  }

  return 0;
}