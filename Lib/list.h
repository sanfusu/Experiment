/**
 * @brief   通用链表数据结构
 * @author  sanfusu@foxmail.com
 * @date    2019/1/9
 * @update  2019-03-08 17:49:53
 */
#ifndef __LIST_H
#define __LIST_H
#include <stdlib.h>

#ifndef offsetof
// 等同于 stddef.h 中的 offsetof
#define offsetof(type, member) (size_t)((type *)0->(member))
#endif

/**
 * containerof - 获取结构体成员所在的容器地址
 * 如果链表头部不位于容器起始位置，则可以使用该宏来获取容器起始位置。
 */
#define containerof(type, member, memberaddr) (memberaddr - offsetof(type, member))

// single list part
typedef void **single_list_header_ptr_t;
typedef single_list_header_ptr_t *single_list_header_t;
#define single_list_header(name) single_list_header_ptr_t name[1] // single_list_header_ptr_t * name
#define single_list_next(current_header) ((single_list_header_t)((current_header)[0]))

#define single_list_add_next(current_header, next_header)            \
    {                                                                \
        (current_header)[0] = (single_list_header_ptr_t)next_header; \
    }

#define single_list_delete(prev_header, next_header) single_list_add_next(prev_header, next_header)
#define single_list_delete_next(current_header) single_list_delete(current_header, single_list_next(single_list_next(current_header)))

// end of single list

// double list part
#define _double_prev 1
#define _double_next 0

typedef void **double_list_header_ptr_t;
typedef double_list_header_ptr_t *double_list_header_t;
#define double_list_header(name) double_list_header_ptr_t name[2]
#define double_list_next(current_header) ((double_list_header_t)(current_header)[_double_next])
#define double_list_prev(current_header) ((double_list_header_t)(current_header)[_double_prev])

#define double_list_add(current_header, new_header, pn)                                                            \
    {                                                                                                              \
        single_list_add_next((single_list_header_t)(&new_header[!pn]), (single_list_header_t)current_header);      \
        single_list_add_next((single_list_header_t)(&new_header[pn]),                                              \
                             (single_list_header_t)single_list_next((single_list_header_t)(&current_header[pn]))); \
        single_list_add_next((single_list_header_t)(&current_header[pn]), (single_list_header_t)new_header);       \
        if (single_list_next((single_list_header_t)(&new_header[pn])) != NULL)                                     \
        {                                                                                                          \
            single_list_add_next(single_list_next((single_list_header_t)(&new_header[pn])), new_header);           \
        }                                                                                                          \
    }

#define double_list_add_next(current_header, new_header) double_list_add(current_header, new_header, _double_next)
#define double_list_add_prev(current_header, new_header) double_list_add(current_header, new_header, _double_prev)

#define double_list_delete(current_header)                                                       \
    {                                                                                            \
        double_list_add_next(double_list_prev(current_header), double_list_next(current_header)) \
    }

// end of double list

#endif
