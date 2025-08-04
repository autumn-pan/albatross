#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(List* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

ListNode* create_node(void* value) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        perror("Node allocation failed");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->next = NULL;
    return node;
}

void list_push(List* list, ListNode* node)
{
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
    list->size++;
}

void list_pop_head(List* list)
{
    ListNode* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->size--;
}

void list_pop(List* list, int index)
{
    if(index > list->size)
    {
        perror("Node index out of bounds");
        exit(EXIT_FAILURE);
    }

    ListNode* tmp = list->head;
    for(int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next; 
    }

    free(tmp->next);
    tmp->next = tmp->next->next;
    list->size--;
}