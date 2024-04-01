/*
 * Project: Learning-Note
 * Module: data struct main function
 * File: main.c
 * Created Date: 2024-03-24 12:31:35
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
#include "base.h"
#define LOG_ENABLE_DEBUG (1)

/* ======================================================================================
 * includes
 */
#include "Array/array.h"
#include "LinkList/linkList.h"
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
#if (RUNNING_DEMO_NUMBER == ARRAY_DEMO)
static Array demoArray = {0};
#endif
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
#if (RUNNING_DEMO_NUMBER == 1)
  testArrayDemo(&demoArray);
#endif

#if (SINGLE_LIST == RUNNING_DEMO_NUMBER)
  testSingleList();
#endif
  return 0;
}