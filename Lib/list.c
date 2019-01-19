#include "list.h"

void(double_list_add_prev)(double_list_header_t current_header, double_list_header_t new_header)
{
    double_list_add_prev(current_header, new_header);
}

void(double_list_add_next)(double_list_header_t current_header, double_list_header_t new_header)
{
    double_list_add_next(current_header, new_header);
}

#ifdef MODULE_TEST_LIST_C

#include <stdio.h>
typedef struct Node
{
    double_list_header(header);
    int num;
} Node_t;

int main()
{
#undef double_list_add_next
    Node_t node[10];
    Node_t *c_node = node;
    node[0].header[0] = node[0].header[1] = NULL;
    for (int i = 0; i < 9; i++)
    {
        node[i].num = i;
        node[i + 1].num = i + 1;
        double_list_add_next(node[i].header, node[i + 1].header);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", c_node->num);
        c_node = (Node_t *)double_list_next(c_node->header);
    }
}

#endif