#ifndef LIST_H
#define LIST_H
#include <stdint.h>

typedef struct listNode
{
    struct listNode* next;
    void* value;
} ListNode;

typedef struct
{
    int size;
    ListNode* head;
    ListNode* tail;
} List;

// Initialization functions
void init_list(List* list);
ListNode* create_node(void* value);

// List util functions
void list_push(List* list, ListNode* node);
void list_pop_head(List* list);
void list_pop(List* list, int index);
void list_append(List * list, ListNode* node);
int8_t find_node_index(List* list, ListNode* node);

#endif