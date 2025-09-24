#include "list.h"

#include <stddef.h>
#include <stdint.h>
#include "list.h"
#include "alloc.h"

void init_list(List_t* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

ListNode_t* create_node(void* value) 
{
    ListNode_t* node = (ListNode_t*)alloc(sizeof(ListNode_t));

    node->value = value;
    node->next = NULL;

    return node;
}

// Push a node to the front of a linked list
void list_push(List_t* list, ListNode_t* node)
{
    node->next = list->head;
    list->head = node;

    if(list->tail == NULL) 
        list->tail = node;

    list->size++;
}


void list_append(List_t * list, ListNode_t* node)
{
    node->next = NULL;
    if (list->head == NULL) { // Empty list
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    // Track list size
    list->size++;
}

// Destroy the first node of some list
void list_pop_head(List_t* list)
{
    if(!list->head) 
        return;

    if(list->head->next)
    {
        list->head = list->head->next;
    }
    else
    {
        list->head = NULL;
        list->tail = NULL;
    }
    
    list->size--;
}

// Destroy any node in a list by index
void list_pop(List_t* list, int index)
{
    ListNode_t* tmp = list->head;

    for(int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next; 
    }

    free(tmp->next);
    tmp->next = tmp->next->next;
    list->size--;
}

// Find the index of a node in a list
int8_t find_node_index(List_t* list, ListNode_t* node)
{
    ListNode_t* tmp = list->head;

    uint8_t index = 0;
    while(tmp != node)
    {
        tmp = tmp->next;

        // If not found, return -1
        if(!tmp)
            return -1;

        index++;
    }

    return index;
}