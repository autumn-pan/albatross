#ifndef LIST_H
#define LIST_H

typedef struct
{
    ListNode* prev;
    ListNode* next;
    void* value;
    int index;
} ListNode;

typedef struct
{
    int size;
    ListNode* head;
    ListNode* tail;
} List;

void init_list(List* list);

#endif