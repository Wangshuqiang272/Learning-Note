/*
 * Project: Learning-Note
 * Module: array source
 * File: array.h
 * Created Date: 2024-03-24 13:08:38
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified 
 * -----
 * Copyright (c) 2024 - vDiscovery, Inc
 */
#ifndef ARRAY_H
#define ARRAY_H

/* ======================================================================================
 * includes
 */
#include "../base.h"
/* ======================================================================================
 * extern
 */

/* ======================================================================================
 * macros
 */
#define ARRAY_NUMBER 500
/* ======================================================================================
 * types
 */
typedef struct {
  int data[ARRAY_NUMBER];
  int length;
}Array;
/* ======================================================================================
 * declaration
 */

/**
 * @brief init the array
 * 
 * @param list 
 * @return int 
 */
int initList(Array *list);
/**
 * @brief Destroy the list
 * 
 * @param list 
 * @return int 
 */
int DestroyList(Array *list);
/**
 * @brief insert a data factor into the list
 * 
 * @param list  
 * @param position  begin position is 0
 * @param value 
 * @return int 
 */
int ListInsert(Array *list, int position, int value);
/**
 * @brief delete a data factor from list
 * 
 * @param list 
 * @param position 
 * @param value 
 * @return int 
 */
int ListDelete(Array *list, int position, int *value);
/**
 * @brief locate data factor according to the value
 * 
 * @param list 
 * @param value 
 * @return int 
 */
int LocateElem(Array *list, int value);
/**
 * @brief locate data factor according to the position
 * 
 * @param list 
 * @param position 
 * @return int 
 */
int GetElem(Array *list, int position);
/**
 * @brief Get the data Length of list 
 * 
 * @param list 
 * @return int 
 */
int getListLength(Array *list);

/**
 * @brief 测试代码
 * 
 * @param array 
 */
void testArrayDemo(Array* array);
/* ======================================================================================
 * extern
 */ 
#endif // ARRAY_H