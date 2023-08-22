/*
Name:- Aashutosh Dahal
CS 241, Lab08
linkedlist.c is the program that creates a linkedlist and perform a basic 
operation like insertSorted list, removeItem from linkedlist, print, push, pop...
*/
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

/* Alloc a new node with given data. */
struct ListNode* createNode(char data)
{
  struct ListNode* node = malloc(sizeof(struct ListNode));
  node->data = data;
  node->next = NULL;
  return node;
}

/* Insert data at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, char data)
{
  struct ListNode* newNode = createNode(data);
  newNode->next = head; 
  if (head == NULL)
    {
        head = newNode;
    }
  else if (data < head->data)
    {
      /* new head of the node */
        newNode->next = head;
        head = newNode;
    }
  else
    {
      /* going through linked list to find the appropriate location to sort */
        struct ListNode* currNode = head;
	      while(currNode->next != NULL && currNode->next->data < data)
        { 
		      currNode = currNode->next;
        }
        /* inserting the new node */
        newNode->next = currNode->next;
        currNode->next = newNode;
    }
  return head;
}
/* Remove data from list pointed to by headRef, changing head if necessary.                                                                                                                                 
 * Make no assumptions as to whether the list is sorted.                                                                                                                                                    
 * Memory for removed node should be freed.                                                                                                                                                                 
 * Return 1 if data was present, 0 if not found. */


int removeItem(struct ListNode** headRef, char data)
{
  struct ListNode* currHead;
    if (*headRef == NULL)
      {
        return 0;
      }
    
    /*  head node is the one to be removed */
    if ((*headRef)->data == data)
      {
        struct ListNode* tempList = *headRef;
        *headRef = (*headRef)->next;
        free(tempList);
        return 1;
      }
    
    /* going through the list to remove */
    currHead = *headRef;
    while(currHead->next != NULL && currHead->next->data != data)
    {
	    currHead = currHead->next;
	  }
  
    /* removing node */
    if (currHead->next != NULL)
      {
        struct ListNode* tempList = currHead->next;
        currHead->next = currHead->next->next;
        free(tempList);
        return 1;
      }
    
    /* nothing to remove */
    return 0;
}


/* Treat list as a stack. (LIFO - last in, first out)                                                                                                                                                       
 * Insert data at head of list, return new list head. */
struct ListNode* pushStack(struct ListNode* head, char data)
{
  struct ListNode* newNode = malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = head;
  return newNode;
}


/* Treat list as a stack. (LIFO - last in, first out)                                                                                                                                                       
 * Remove and return data from head of non-empty list, changing head.                                                                                                                                       
 * Memory for removed node should be freed. */
char popStack(struct ListNode** headRef)
{
  struct ListNode* tempList = *headRef;
  char data = tempList->data;
  *headRef = tempList->next;
  free(tempList);
  return data;
}

/* Return length of the list. */
int listLength(struct ListNode* head)
{
  struct ListNode* currList = head;
  int counter = 0; /* counter for length */
  while(currList != NULL)
    {
      counter ++;
      currList = currList->next;
    }
  return counter;
}


/* Print list data on single line, separating values with a comma and                                                                                                                                       
 * a space and ending with newline. */

void printList(struct ListNode* head)
{
  struct ListNode* currHead = head;
  while(currHead != NULL)
    {
      printf("%c", currHead->data);
      if(currHead->next!=NULL)
      {
        printf(", ");
      }
      currHead  = currHead->next;
    }
    printf("\n");
}

/* Free memory used by the list. */

void freeList(struct ListNode* head)
{
    while (head != NULL)
      {
        struct ListNode* tempList = head;
        head = head->next;
        free(tempList);
      }
}
    

/* Reverse order of elements in the list */

void reverseList(struct ListNode** headRef)
{
    struct ListNode* before = NULL;
    struct ListNode* current = *headRef;
    struct ListNode* after = NULL;
    
    while (current != NULL)
      {
        after = current->next;
        current->next = before;
        before = current;
        current = after;
      }
    
    *headRef = before;
}
