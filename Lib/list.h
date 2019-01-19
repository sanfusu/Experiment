/**
 * @brief   通用链表数据结构
 * @author  sanfusu@foxmail.com
 * @date    2019/1/9
 */
#ifndef __LIST_H
#define __LIST_H
#include <stdlib.h>

// single list part
typedef void *list_header_ptr_t;
#define single_list_header(name) list_header_ptr_t name
#define single_list_next(current_header) ((current_header))

#define single_list_add_next(current_header, next_header) \
    {                                                     \
        (current_header) = (next_header);                 \
    }
// end of single list

// double list part
#define _double_prev 1
#define _double_next 0

typedef list_header_ptr_t *double_list_header_t;
#define double_list_header(name) list_header_ptr_t name[2]
#define double_list_next(current_header) ((current_header)[_double_next])
#define double_list_prev(current_header) ((current_header)[_double_prev])

#define double_list_add(current_header, new_header, pn)                                                      \
    {                                                                                                        \
        single_list_add_next(new_header[!pn], current_header);                                               \
        single_list_add_next(new_header[pn], single_list_next(current_header[pn]));                          \
        single_list_add_next(current_header[pn], new_header);                                                \
        if (single_list_next(new_header[pn]) != NULL)                                                        \
        {                                                                                                    \
            single_list_add_next(((double_list_header_t)single_list_next(new_header[pn]))[!pn], new_header); \
        }                                                                                                    \
    }

#define double_list_add_next(current_header, new_header) double_list_add(current_header, new_header, _double_next)
#define double_list_add_prev(current_header, new_header) double_list_add(current_header, new_header, _double_prev)
// end of double list

#endif
