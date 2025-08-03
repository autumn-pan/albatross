#include "list.h"
#include <stdio.h>

void init_list(List* list)
{
    list->head = NULL;
    list->tail = NULL;
}

void list_append(List* list, ListNode* node)
{
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = list->tail;
        list->tail = node;
    }
}

void list_pop_head(List* list)
{
    ListNode* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
}