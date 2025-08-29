#include "util/list.h"

#include <stddef.h>
#include <stdint.h>
#include "util/list.h"
#include "util/alloc.h"

void init_list(List* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

ListNode* create_node(void* value) 
{
    ListNode* node = (ListNode*)alloc(sizeof(ListNode));

    node->value = value;
    node->next = NULL;
    return node;
}

// Push a node to the front of a linked list
void list_push(List* list, ListNode* node)
{
    if(list->head == NULL) // First insertion
    {
        list->head = node;
    }
    else if(list->tail == NULL) // Second insertion
    {
        list->tail = list->head;
        list->head = node;
        node->next = list->tail;
    }
    else // Any subsequent insertion
    {
        node->next = list->head;
        list->head = node;
    }

    // Track list size
    list->size++;
}


void list_append(List * list, ListNode* node)
{
    if(list->head == NULL) // First insertion
    {
        list->head = node;
        list->tail = node;
    }
    else if(list->tail == NULL) // Second insertion
    {
        list->tail = list->head;
        list->head = node;
        node->next = list->tail;
    }
    else // Any subsequent insertion
    {
        list->tail->next = node;
        list->tail = node;
    }

    // Track list size
    list->size++;
}

// Destroy the first node of some list
void list_pop_head(List* list)
{
    ListNode* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->size--;
}

// Destroy any node in a list by index
void list_pop(List* list, int index)
{
    ListNode* tmp = list->head;

    for(int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next; 
    }

    free(tmp->next);
    tmp->next = tmp->next->next;
    list->size--;
}

// Find the index of a node in a list
int8_t find_node_index(List* list, ListNode* node)
{
    ListNode* tmp = list->head;

    uint8_t index = 0;
    while(tmp != node)
    {
        tmp = tmp->next;

        // If not found, return -1
        if(!tmp)
            return -1;

        index++;
    }

    free(tmp);
    return index;
}