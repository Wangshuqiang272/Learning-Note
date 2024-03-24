/*
 * Project: Learning-Note
 * Module: main
 * File: main.c
 * Created Date: 2024-03-23 13:48:10
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2024 - vDiscovery, Inc
 */

/* ======================================================================================
 * log
 */
#define LOG_ENABLE_DEBUG (1)

/* ======================================================================================
 * includes
 */
#include "build/config.h"
#include "libDemo/manager_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ======================================================================================
 * macros
 */

/* ======================================================================================
 * types
 */

/* ======================================================================================
 * declaration
 */

/* ======================================================================================
 * globals
 */

/* ======================================================================================
 * helper
 */

/* ======================================================================================
 * private implementation
 */

/* ======================================================================================
 * implementation
 */

int main(int argc, char *argv[]) {
  printf("wangshuqiang STEP2 test:\r\n");
#ifdef USE_MANAGER_COMMON_LIB
  printf("%d is leapYear,the answer is %d\r\n", 2024, isLeapYear(2024));
#endif
  return 0;
}