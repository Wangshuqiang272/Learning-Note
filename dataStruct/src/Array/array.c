/*
 * Project: Learning-Note
 * Module: array source
 * File: array.c
 * Created Date: 2024-03-24 13:05:29
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
#include "array.h"
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

int initList(Array *list) {
  if (!list) {
    return FAIL;
  }
  memset(list->data, 0, sizeof(list->data));
  list->length = 0;
  return SUCCESS;
}

int DestroyList(Array *list) { return initList(list); }

int ListInsert(Array *list, int position, int value) {
  if ((!list) || (list->length >= sizeof(list->data))) {
    return FAIL;
  }

  if (position >= list->length) {
    list->data[list->length] = value;
    list->length++;
    return SUCCESS;
  }

  for (int i = list->length - 1; i >= position; i--) {
    list->data[i] = list->data[i + 1];
  }
  list->data[position] = value;
  list->length++;
  return SUCCESS;
}

int ListDelete(Array *list, int position, int *value) {
  if ((!list) || (list->length <= 0) || (position >= list->length)) {
    return FAIL;
  }

  *value = list->data[position];
  for (int i = position; i < list->length - 1; i++) {
    list->data[i] = list->data[i + 1];
  }
  list->data[--list->length] = 0;
  return SUCCESS;
}

int LocateElem(Array *list, int value) {
  if (!list) {
    return FAIL;
  }

  for (int i = 0; i < list->length; i++) {
    if (list->data[i] == value) {
      return i;
    }
  }
  return FAIL;
}

int GetElem(Array *list, int position) {
  if ((!list) || (position >= list->length)) {
    return FAIL;
  }

  return list->data[position];
}

int getListLength(Array *list) {
  if (!list) {
    return FAIL;
  }
  return list->length;
}

void testArrayDemo(Array* array) {
  if (SUCCESS == initList(array)) {
    printf("demo array init successed\r\n");
  }
  for (int i = 0; i < 30; i++) {
    ListInsert(array, i, i);
  }
  int value = -1;
  ListDelete(array, 0, &value);
  ListDelete(array, 15, &value);
  ListDelete(array, 40, &value);

  printf("location position is %d\r\n", LocateElem(array, 20));
  printf("Number.14 value is %d\r\n", GetElem(array, 14));
  printf("whole array number is %d\r\n", getListLength(array));
}