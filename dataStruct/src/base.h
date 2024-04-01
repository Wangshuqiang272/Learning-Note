/*
 * Project: Learning-Note
 * Module: base header files
 * File: base.h
 * Created Date: 2024-03-24 14:47:19
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified 
 * -----
 * Copyright (c) 2024 - vDiscovery, Inc
 */
#ifndef BASE_H
#define BASE_H

/* ======================================================================================
 * includes
 */
#include <stdio.h>
/* ======================================================================================
 * extern
 */

/* ======================================================================================
 * macros
 */
#define SUCCESS 1
#define FAIL 0

#define RUNNING_DEMO_NUMBER SINGLE_LIST
#define ARRAY_DEMO 1
#define SINGLE_LIST 2

// #define check_param_null(x, y)                                                 \
//   if (!x) {                                                                    \
//     printf(#y "\r\n");
// }
// check_param_null(List, headInsert param NULL)

#define check_param_null_void_return(x, y)         { if (!x) {printf(y "\r\n");}}

#define check_param_null_var_return(x, y,var)         { if (!x) {printf(y "\r\n"); return var;}}
/* ======================================================================================
 * types
 */

/* ======================================================================================
 * declaration
 */

/* ======================================================================================
 * extern
 */ 
#endif // BASE_H