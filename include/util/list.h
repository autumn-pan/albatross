#ifndef LIST_H
#define LIST_H
#include <stdint.h>

typedef struct listNode
{
    struct listNode* next;
    void* value;
} ListNode_t;

typedef struct
{
    int size;
    ListNode_t* head;
    ListNode_t* tail;
} List_t;

// Initialization functions
void init_list(List_t* list);
ListNode_t* create_node(void* value);

// List util functions
void list_push(List_t* list, ListNode_t* node);
void list_pop_head(List_t* list);
void list_pop(List_t* list, int index);
void list_append(List_t* list, ListNode_t* node);
int8_t find_node_index(List_t* list, ListNode_t* node);

#endif