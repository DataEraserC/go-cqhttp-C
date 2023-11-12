#include "win.h"
#include <stdio.h>

int color(int a) {
  switch (a) {
  case 1:
    printf("\033[31m"); // 红色
    break;
  case 2:
    printf("\033[32m"); // 绿色
    break;
  case 3:
    printf("\033[33m"); // 黄色
    break;
  case 4:
    printf("\033[34m"); // 蓝色
    break;
  case 5:
    printf("\033[35m"); // 紫色
    break;
  case 6:
    printf("\033[36m"); // 青色
    break;
  case 7:
    printf("\033[37m"); // 白色
    break;
  default:
    printf("\033[0m"); // 默认颜色
    break;
  }
  return 0;
}
void test_color() {
  color(1);
  printf("1. 红色\n");
  color(2);
  printf("2. 绿色\n");
  color(3);
  printf("3. 黄色\n");
  color(4);
  printf("4. 蓝色\n");
  color(5);
  printf("5. 紫色\n");
  color(6);
  printf("6. 青色\n");
  color(7);
  printf("7. 白色\n");
}