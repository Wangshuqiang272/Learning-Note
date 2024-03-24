#include "Config.h"
#include "stdio.h"
int main() {
  printf("wangshuqiang printf step1\r\n");
  printf("wangshuqiang printf VERSION_MAJOR %d\r\n", VERSION_MAJOR);
  printf("wangshuqiang printf VERSION_MINOR %d\r\n", VERSION_MINOR);
  printf("wangshuqiang printf VERSION_PATCH %d\r\n", VERSION_PATCH);
  printf("wangshuqiang printf time stamp %s\r\n", BUILD_TIMESTAMP);
  return 1;
}