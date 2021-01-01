#pragma once

#include <iostream>
#include <stdlib.h>

/* MEM30-C. Do not access freed memory*/
namespace MEM30C
{
struct Node
{
    int value;
    struct Node* next;
};

void nonCompliantExample1(struct Node* head)
{
    /*, p is freed before p->next is executed
     * so that p->next reads memory that has already been freed. */
    for (struct Node* p = head; p != NULL; p = p->next)
    {
        free(p);
    }
}
}  // namespace MEM30C