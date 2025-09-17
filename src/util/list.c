#include "util/list.h"

#include <stddef.h>
#include <stdint.h>
#include "util/list.h"
#include "util/alloc.h"

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


void list_append(List_t * list, ListNode_t* node)
{
    if(list->head == NULL) // First insertion
    {
        list->head = node;
        list->tail = node;
    }
    else if(list->tail == NULL) // Second insertion
    {
        list->tail = node;
        list->head->next = list->tail;
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
void list_pop_head(List_t* list)
{
    ListNode_t* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
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