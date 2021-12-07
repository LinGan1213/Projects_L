// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "hw10.h"

// DO NOT MODIFY this function --->>>
void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL) // the linked list must end with NULL
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}
// <<<--- until here

// You MUST modify the following functions

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
// the linked list must end with NULL
ListNode * createList(int valn)
{
	//head node and nonhead node 
	//for loop start from 1 
	// 5 NULL
	// 4 5 NULL
	// 3 4 5 NULL assign the linked list to head, so head is a linked list
	ListNode * head = NULL;
	ListNode * nonhead = NULL;
	int i;
	for (i = 0; i < valn; i++)
	{
		nonhead = malloc(sizeof(*nonhead));//ListNode
		nonhead -> value = valn - i - 1; //start from the end of the list
		nonhead -> next = head;
		head = nonhead; // head points to what nonhead points to
	}	
	return head;
}
#endif

#ifdef TEST_ELIMINATE
// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk)
{
	ListNode *tem = NULL;//tem is the variable to store head
	ListNode *p = NULL;//p is the node to be deleted
	tem = head; //let temp stores head

	int c;
	c = 1;
        while (head->next != NULL)
        {	
                while(c < valk) 
                {
			//c++;
			if (tem->next == NULL)
                	{
                        	tem = head; //if p->next is null, set p back to the beginning (head)
				c++;
                	}
			else
			{
				tem = tem->next;
				c++;
			}
		}
		p = tem;
		//printf("%d\n", tem->value);
		if (tem->next != NULL){
			tem = tem->next;
		}
		else{
			tem = head;
		}
		#ifdef DEBUG
  		// this #ifdef ... #endif should be inside the condition *BEFORE* a
  		// node' value is printed and it is deleted
  		ListNode * todelete = p;
		printListNode (todelete);
  	        #endif
		printf("%d\n", todelete->value);
		//if(p->value == head->value){ 
                //        head = tem;
                //}
		head = deleteNode(head, p);
                c = 1;
        }
	printf("%d\n", head->value);
	free(head);
}
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete)
{
	ListNode * p = head;
	//ListNode * temp = p->next;
	if (head == NULL){return NULL;}
	if (todelete == NULL){return head;}
	if (todelete == head){
		//todelete = temp; Don't need this line at all. Has nothing to do. 
		ListNode * temp = head->next;
		free(head);//or free(todelet)
		return temp;
	}
	//while ((temp != NULL)&&((temp->value) != (todelete->value)))
	while((p->next != NULL)&&(p->next != todelete))
	{
		p = p->next;
		//temp = temp->next;//now temp = todelete
	}
	if (p != NULL)
	{
		p->next = todelete->next; //delete temp as todelete node and connect two nodes
		free(todelete);
	}
	return head;

	//while (p->next != todelete)
        //{
 	//       p = p->next; //find the node before todetele node. Delete 2 and connect 1 and 3
       	//}
        //p->next = todelete->next;
        //free(todelete);
	//return head;
}
#endif
