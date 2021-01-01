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

void compliantExample1(struct Node* head)
{
    // cache a reference to p->next in q before freeing p
    struct Node* q;
    for (struct Node* p = head; p != NULL; p = q)
    {
        q = p->next;
        free(p);
    }
}

void nonCompliantExample2(char* c_str1, size_t size)
{
    std::cout << "size of input str= " << sizeof(c_str1) << "\n";

    /* realloc() may free c_str1 when it returns a null pointer,
     * resulting in c_str1 being freed twice */
    /* if parameter size = 0 then realloc will be the equivalent of free() */
    //@todo dokimase to
    char* c_str2 = (char*)realloc(c_str1, size);
    if (c_str2 == NULL)
    {
        free(c_str1);
    }
}

void compliantExample2(char* c_str1, size_t size)
{
    /* Check the parameter size so it won't be passed as zero to the realloc() function,
     * eliminating the possibility of c_str1 being freed twice */
    if (size != 0)
    {
        char* c_str2 = (char*)realloc(c_str1, size);
        if (c_str2 == NULL)
        {
            free(c_str1);
        }
    }
    else
    {
        free(c_str1);
    }
}

}  // namespace MEM30C