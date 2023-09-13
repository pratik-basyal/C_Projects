/****
*NAME : Pratik Basyal
*CS 241
****/

#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

/**
 * This function creates new node
*/
struct ListNode* createNode(char data)
{
    struct ListNode* new_node = malloc(sizeof(struct ListNode));

    new_node -> data = data;
    new_node -> next = NULL;

    return new_node;
}

/* Insert data at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, char data)
{
    struct ListNode* new_node = malloc(sizeof(struct ListNode));
    struct ListNode* current = head;
    new_node->data = data;
    new_node->next = NULL;

    if (head == NULL || head->data > data) /* if list is empty or new node goes at the beginning */
    {
        new_node->next = head;
        return new_node;
    }

    while (current->next != NULL && current->next->data < data) 
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;

    return head;
}

/* Remove data from list pointed to by headRef, changing head if necessary.
 * Make no assumptions as to whether the list is sorted.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeItem(struct ListNode** headRef, char data) 
{
    struct ListNode* curr = *headRef;
    struct ListNode* prev = NULL;

    while (curr != NULL) 
    {
        if (curr->data == data) {
            if (prev == NULL) 
            {
                /* If the node to remove is the head node, update headRef to point to the next node */
                *headRef = curr->next;
            } 
            else 
            {
                /*Otherwise, update the previous node's next pointer to skip over the node to be removed*/
                prev->next = curr->next;
            }
            /*Free the memory used by the node to be removed*/
            free(curr);
            return 1;
            
        }
        prev= curr;
        curr= curr->next;
    }
    return 0;
}

/* Treat list as a stack. (LIFO - last in, first out)
 * Insert data at head of list, return new list head. */
struct ListNode* pushStack(struct ListNode* head, char data)
{
    struct ListNode* new_list_head = createNode(data);

    new_list_head -> next = head;

    return new_list_head;
}

/* Treat list as a stack. (LIFO - last in, first out)
 * Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
char popStack(struct ListNode** headRef)
{
    char data;
    struct ListNode* curr = *headRef;

    if(*headRef == NULL)
    {
        return 0;
    }
    data = (*headRef) -> data;
    *headRef = (*headRef) -> next;
    free(curr);
    return data;
}

/* Return length of the list. */
int listLength(struct ListNode* head)
{
    int count = 0;
    struct ListNode* curr = head;

    while(curr != NULL)
    {
        curr = curr -> next;
        count++;
    }
    return count;
}

/* Print list data on single line, separating values with a comma and
 * a space and ending with newline. */
void printList(struct ListNode* head)
{
    struct ListNode* temp = head;
    while (temp != NULL) 
    {
        printf("%c", temp->data);
        temp = temp->next;
        if (temp != NULL) 
        {
            printf(", ");
        }
    }
    printf("\n");
}

/* Free memory used by the list. */
void freeList(struct ListNode* head)
{
    struct ListNode* temp = head;

    while(temp != NULL)
    {
        struct ListNode* next = temp->next;
        free(temp);
        temp = next;
    }
}

/* Reverse order of elements in the list */
void reverseList(struct ListNode** headRef)
{
    struct ListNode* current = *headRef;
    struct ListNode* prev = NULL;
    struct ListNode* next = NULL;

    while (current != NULL) 
    {
        /*Store next*/
        next = current->next;
 
        /*Reverse current node's pointer*/
        current->next = prev;
 
        /*Move pointers one position ahead.*/
        prev = current;
        current = next;
    }
    *headRef = prev;
}

