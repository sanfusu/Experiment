/**
 * @brief 队列使用循环双链表实现
 * 本部分只给出一些接口，可以利用这些接口实现特定的队列，如循环队列
 * 或者对队列长度做限制
 */
#include "list.h"
typedef double_list_header_t queue_header_t;

#define enqueue(queue_head, queue_head_new) double_list_add_next(double_list_prev(queue_head), queue_head_new)
#define dequeue(queue_head) double_list_delete(queue_head)