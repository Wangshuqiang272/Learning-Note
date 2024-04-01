/*
 * Project: Learning-Note
 * Module: linkList interface
 * File: linkList.h
 * Created Date: 2024-03-24 16:33:32
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified 
 * -----
 * Copyright (c) 2024 - vDiscovery, Inc
 */
#ifndef LINKLIST_H
#define LINKLIST_H

/* ======================================================================================
 * includes
 */

/* ======================================================================================
 * extern
 */

/* ======================================================================================
 * macros
 */

/* ======================================================================================
 * types
 */
typedef struct LNode{
  int data;
  struct LNode* next;
}LNode;
/* ======================================================================================
 * declaration
 */

/**
 * @brief 初始化链表
 * 
 * @return LNode* 
 */
LNode *initLinkList(void);

/**
 * @brief 头插法新增单链表数据
 * 
 * @param List 
 * @param value 
 * @return int 
 */
int headInsert(LNode *List, int value);


/**
 * @brief 根据位置插入对应节点至链表中
 * 
 * @param list 
 * @param pos 从1开始计算
 * @param value 
 * @return int 
 */
int ListInsertByPosition(LNode *list, int pos, int value);

/**
 * @brief 遍历链表数据
 * 
 * @param List 
 */
void traverseList(LNode *List);


/**
 * @brief 节点删除
 * 
 * @param List 
 * @param pos 从1开始
 * @param deleteValue 
 * @return int 
 */
int ListDeleteNode(LNode *List, int pos, int *deleteValue);


/**
 * @brief 测试接口函数
 * 
 */
void testSingleList(void);
/* ======================================================================================
 * extern
 */ 
#endif // LINKLIST_H