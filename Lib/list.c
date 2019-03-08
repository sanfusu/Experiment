/**
 * @brief   通用链表数据结构
 * @author  sanfusu@foxmail.com
 * @update  2019-03-08 17:50:25
 */

#include "list.h"
#ifdef __DEBUG
#undef single_single_list_header
#undef single_list_next
#undef single_list_add_next
#undef single_list_delete
#undef single_list_delete_next
#undef double_single_list_header
#undef double_list_next
#undef double_list_prev
#undef double_list_add
#undef double_list_add_next
#undef double_list_add_prev
#undef double_list_delete
#endif

single_list_header_t(single_list_next)(single_list_header_t current_header)
{
    single_list_header_t ret = (single_list_header_t)current_header[0];
    return ret;
}

void(single_list_add_next)(single_list_header_t current_header, single_list_header_t next_header)
{
    current_header[0] = (single_list_header_ptr_t)next_header;
}

void(single_list_delete_next)(single_list_header_t current_header)
{
    single_list_header_t nnext_header = single_list_next(single_list_next(current_header));
    single_list_add_next(current_header, nnext_header);
}

double_list_header_t(double_list_next)(double_list_header_t current_header)
{
    double_list_header_t ret = (double_list_header_t)current_header[_double_next];
    return ret;
}

double_list_header_t(double_list_prev)(double_list_header_t current_header)
{
    double_list_header_t ret = (double_list_header_t)current_header[_double_prev];
    return ret;
}

void(double_list_add)(double_list_header_t current_header, double_list_header_t new_header, unsigned pn)
{

    single_list_add_next((single_list_header_t)(&new_header[!pn]), (single_list_header_t)current_header);
    single_list_add_next((single_list_header_t)(&new_header[pn]),
                         (single_list_header_t)single_list_next((single_list_header_t)(&current_header[pn])));
    single_list_add_next((single_list_header_t)(&current_header[pn]), (single_list_header_t)new_header);
    if (single_list_next((single_list_header_t)(&new_header[pn])) != NULL)
    {
        single_list_add_next(single_list_next((single_list_header_t)(&new_header[pn])), new_header);
    }
}

void(double_list_delete)(double_list_header_t current_header)
{
    double_list_add_next(double_list_prev(current_header), double_list_next(current_header));
}
