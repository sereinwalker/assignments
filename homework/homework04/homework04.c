#include <math.h> // 用于第三题的数学计算
#include <stdio.h>

// --- 第2题: 编程实现: 成绩转换 (if-else版本) ---
// 功能：输入百分制成绩，根据规则输出五分制等级和GPA
void task2_grade_conversion_if() {
  int score;
  printf("--- 第2题: 成绩转换 (if-else版本) ---\n");
  printf("请输入百分制成绩 (0-100): ");
  scanf("%d", &score);

  // 检查输入合法性
  if (score < 0 || score > 100) {
    printf("错误: 成绩必须在 0-100 之间。\n");
    return;
  }

  printf("百分制=%d, ", score);

  if (score >= 95) {
    printf("五分制=A+, GPA=4.3\n");
  } else if (score >= 90) {
    printf("五分制=A, GPA=4.0\n");
  } else if (score >= 85) {
    printf("五分制=A-, GPA=3.7\n");
  } else if (score >= 82) {
    printf("五分制=B+, GPA=3.3\n");
  } else if (score >= 78) {
    printf("五分制=B, GPA=3.0\n");
  } else if (score >= 75) {
    printf("五分制=B-, GPA=2.7\n");
  } else if (score >= 72) {
    printf("五分制=C+, GPA=2.3\n");
  } else if (score >= 68) {
    printf("五分制=C, GPA=2.0\n");
  } else if (score >= 65) {
    printf("五分制=C-, GPA=1.7\n");
  } else if (score == 64) {
    printf("五分制=D+, GPA=1.5\n");
  } else if (score >= 61) {
    printf("五分制=D, GPA=1.3\n");
  } else if (score == 60) {
    printf("五分制=D-, GPA=1.0\n");
  } else { // < 60
    printf("五分制=F, GPA=0\n");
  }
  printf("\n");
}

// --- 第2题: 编程实现: 成绩转换 (switch版本) ---
// 功能：使用switch语句实现与上面if版本相同的功能
void task2_grade_conversion_switch() {
  int score;
  printf("--- 第2题: 成绩转换 (switch版本) ---\n");
  printf("请输入百分制成绩 (0-100): ");
  scanf("%d", &score);

  // 检查输入合法性
  if (score < 0 || score > 100) {
    printf("错误: 成绩必须在 0-100 之间。\n");
    return;
  }

  printf("百分制=%d, ", score);

  // 由于switch无法直接处理范围，对不规则的区间（如64, 60）需要特殊处理
  if (score == 64) {
    printf("五分制=D+, GPA=1.5\n");
    return;
  }
  if (score == 60) {
    printf("五分制=D-, GPA=1.0\n");
    return;
  }

  // 将分数除以特定数值来简化switch case，这里以10为单位进行划分
  int decade = score / 10;
  switch (decade) {
  case 10: // 100分
  case 9:  // 90-99分
    if (score >= 95)
      printf("五分制=A+, GPA=4.3\n");
    else
      printf("五分制=A, GPA=4.0\n");
    break;
  case 8: // 80-89分
    if (score >= 85)
      printf("五分制=A-, GPA=3.7\n");
    else if (score >= 82)
      printf("五分制=B+, GPA=3.3\n");
    else
      printf("五分制=B, GPA=3.0\n");
    break;
  case 7: // 70-79分
    if (score >= 78)
      printf("五分制=B, GPA=3.0\n");
    else if (score >= 75)
      printf("五分制=B-, GPA=2.7\n");
    else if (score >= 72)
      printf("五分制=C+, GPA=2.3\n");
    else
      printf("五分制=C, GPA=2.0\n");
    break;
  case 6: // 60-69分, 已经提前处理了64和60分
    if (score >= 68)
      printf("五分制=C, GPA=2.0\n");
    else if (score >= 65)
      printf("五分制=C-, GPA=1.7\n");
    else
      printf("五分制=D, GPA=1.3\n");
    break;
  default: // 0-59分
    printf("五分制=F, GPA=0\n");
    break;
  }
  printf("\n");
}

// --- 第3题: 编程实现: 三角形判断与面积计算 ---
// 功能：输入三个边长，判断能否构成三角形，并判断其类型、计算面积
void task3_triangle_calculator() {
  double a, b, c;
  const double EPSILON = 1e-6; // 定义一个极小值，用于浮点数的相等比较

  printf("--- 第3题: 三角形判断与面积计算 ---\n");
  printf("请输入三个边长 (用空格分隔): ");
  scanf("%lf %lf %lf", &a, &b, &c);

  // 1. 判断能否构成三角形: 两边之和大于第三边
  if (a + b > c && a + c > b && b + c > a) {
    printf("边长为 %.6f, %.6f, %.6f 的三角形", a, b, c);

    // 2. 判断三角形类型 (使用fabs和EPSILON来比较浮点数)
    int isEquilateral = (fabs(a - b) < EPSILON) && (fabs(b - c) < EPSILON);
    int isIsosceles = (fabs(a - b) < EPSILON) || (fabs(b - c) < EPSILON) ||
                      (fabs(a - c) < EPSILON);
    // 勾股定理判断直角三角形
    int isRight = (fabs(a * a + b * b - c * c) < EPSILON) ||
                  (fabs(a * a + c * c - b * b) < EPSILON) ||
                  (fabs(b * b + c * c - a * a) < EPSILON);

    if (isEquilateral) {
      printf("是等边三角形");
    } else if (isRight && isIsosceles) {
      printf("是等腰直角三角形");
    } else if (isIsosceles) {
      printf("是等腰三角形");
    } else if (isRight) {
      printf("是直角三角形");
    } else {
      printf("是普通三角形");
    }

    // 3. 使用海伦公式计算面积
    double s = (a + b + c) / 2.0;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    printf(", 其面积为: %.6f\n", area);

  } else {
    printf("输入的三条边无法构成三角形。\n");
  }
  printf("\n");
}

int main() {
  printf("《计算机程序设计》作业 04 - 编程题\n");

  // 执行第2题的两个版本
  task2_grade_conversion_if();
  task2_grade_conversion_switch();

  // 执行第3题
  task3_triangle_calculator();

  return 0;
}