#ifndef LIST_H
#define LIST_H

typedef struct
{
    ListNode* next;
    void* value;
} ListNode;

typedef struct
{
    int size;
    ListNode* head;
    ListNode* tail;
} List;

void init_list(List* list);

#endif