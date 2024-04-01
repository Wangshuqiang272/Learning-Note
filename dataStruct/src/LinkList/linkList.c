/*
 * Project: Learning-Note
 * Module: linkList interface
 * File: linkList.c
 * Created Date: 2024-03-24 16:33:16
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

#include <stdio.h>
#include <stdlib.h>
#define LOG_ENABLE_DEBUG (1)

/* ======================================================================================
 * includes
 */
#include "../base.h"
#include "linkList.h"
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

LNode *initLinkList(void) {
  LNode *headpoint = NULL;
  // 创建头节点
  headpoint = (LNode *)malloc(sizeof(LNode));
  if (!headpoint) {
    return NULL;
  } else {
    headpoint->data = 0;
    headpoint->next = NULL;
    return headpoint;
  }
}

int headInsert(LNode *List, int value) {
  // 形参判断
  check_param_null_void_return(List, "headInsert param NULL");
  LNode *L = NULL;
  // 创建节点
  LNode *newNode = (LNode *)malloc(sizeof(LNode));
  if (!newNode) {
    return FAIL;
  }

  newNode->data = value;
  newNode->next = NULL;

  L = List->next;

  if (!L) {
    List->next = newNode;
  } else {
    newNode->next = L;
    List->next = newNode;
  }
  List->data++;
  return SUCCESS;
}

static int backInsertNode(LNode *node, int value) {
  check_param_null_var_return(node, "backInsertNode param null", FAIL);
  LNode *L = node;
  LNode *newNode = (LNode *)malloc(sizeof(LNode));
  newNode->data = value;
  newNode->next = L->next;
  L->next = newNode;
  return SUCCESS;
}

static LNode *getItem(LNode *List, int pos) {
  check_param_null_void_return(List, "getItem param NULL");
  if (pos < 0)
    return NULL;

  int j = 0;
  LNode *L = List;
  while (L != NULL && j < pos) {
    L = L->next;
    j++;
  }
  return L;
}

int ListInsertByPosition(LNode *list, int pos, int value) {
  check_param_null_var_return(list, "ListInsertByPosition param null", FAIL);

  LNode* L = getItem(list, pos - 1);

  backInsertNode(L, value);
}

int frontInsertNode(LNode *node, int value) {

  check_param_null_var_return(node, "insertNodebyFront param NULL", FAIL);

  LNode *L = node;
  LNode *newNode = (LNode *)malloc(sizeof(LNode));
  newNode->next = L->next;
  newNode->data = L->data;
  L->next = newNode;
  L->data = value;
  return SUCCESS;
}

void traverseList(LNode *List) {
  check_param_null_void_return(List, "traverseList param NULL");
  int i = 1;
  LNode *L = List->next;
  printf("List count number is %d\r\n", List->data);
  while (L != NULL) {
    printf("Number.%d data = %d\r\n", i++, L->data);
    L = L->next;
  }
}

int ListDeleteNode(LNode *List, int pos, int *deleteValue) {
  check_param_null_void_return(List, "ListDeleteNode param NULL");

  LNode* L = getItem(List,pos -1);

  if (L == NULL)
    return FAIL;

  if (L->next == NULL)
    return FAIL;

  LNode* q = L->next;
  *deleteValue = q->data;
  L->next = q->next;
  q->next = NULL;
  free(q);
  List->data--;
  return SUCCESS;
}

void testSingleList(void) {
  LNode *LIST = initLinkList();
  if (!LIST) {
    return;
  }

  for (int i = 0; i < 10; i++) {
    if (headInsert(LIST, i) == FAIL) {
      break;
    }
  }

  traverseList(LIST);
}
