#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calc.h"

typedef struct Node {
	float val;
        struct Node * next;
} Node;

Node * cons(float val, Node * list) {
    	//Allocate the new node
	Node * newNode = malloc(sizeof(Node));
    	//Set up the value
    	newNode->val = val;
	//The new node points to the old list
	newNode->next = list;
	//return a pointer to the new node
	return newNode;
}

Node * removeFirst(Node * list) {
    if (list == NULL) return NULL; //empty list; nothing to remove
    
    Node * restOfList = list->next;
    free(list);
    return restOfList;
}

typedef struct Stack {
    Node * top; //top of the stack. If it points to NULL, the stack is empty
} Stack;

/* Allocate and initialize an empty stack*/
Stack * initialize() {
    Stack * s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isEmpty(Stack * s) {
    return s->top == NULL;
}

void push(Stack * s, float key) {
    s->top = cons(key, s->top);
}

float peek(Stack * s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Peeking at an empty stack at address %p\n", s);
        exit(1); 
    }
    
    return s->top->val; //return the value in the first node
}

float pop(Stack * s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Popping off an empty stack at address %p\n", s);
        exit(1);
    }
    
    float retval = peek(s);
    s->top = removeFirst(s->top);
    
    return retval; //value of the top stack
}

//free stack
void freeStack(Stack * s) {
    while (!isEmpty(s)) {
        pop(s);
    }
    free(s);
}

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}

	FILE * input = fopen(argv[1], "r");
	if(input == NULL){
		printf("Error opening input file for reading\n");
		fclose(input);
		return EXIT_FAILURE;
	}

	float head, headnext;	
	float result; //store the result of your calculation here.
	char * operation = malloc(sizeof(char *));
		
	Stack * s = initialize();
	
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */
	while (!feof(input)) //if scan string
	{
		if(feof(input))
		{
			freeStack(s);
                        //free(operation);
                        fclose(input);
                        return EXIT_FAILURE;
		}
		fscanf(input, "%s", operation);
		if (strcmp(operation, "*") == 0 || strcmp(operation, "/") == 0 || strcmp(operation, "+") == 0 || strcmp(operation, "-") == 0){
			head = pop(s);
			//headnext = pop(s);
			if (strcmp(operation, "*") == 0)
			{
				if(isEmpty(s))
				{
					freeStack(s);
					free(operation);
                			fclose(input);
					return EXIT_FAILURE;
				}
				headnext = pop(s);
				result = head * headnext;
			}
			if (strcmp(operation, "/") == 0)
			{
				if(isEmpty(s))
                                {
					freeStack(s);
					free(operation);
                                        fclose(input);
                                        return EXIT_FAILURE;
                                }
                                headnext = pop(s);
				result = headnext / head;
			}
			if (strcmp(operation, "+") == 0)
                	{
				if(isEmpty(s))
                                {
					freeStack(s);
					free(operation);
                                        fclose(input);
                                        return EXIT_FAILURE;
                                }
                                headnext = pop(s);
                		result = headnext + head;
                	}
			if (strcmp(operation, "-") == 0)
                	{
				if(isEmpty(s))
                                {
					freeStack(s);
					free(operation);
                                        fclose(input);
                                        return EXIT_FAILURE;
                                }
                                headnext = pop(s);
                		result = headnext - head;
                	}
			push(s, result);
		}
		else
		{
			push(s, atof(operation));
		}
	}
	free(operation);
	if(isEmpty(s))
	{
		freeStack(s);
		fclose(input);
		return EXIT_FAILURE;		
	}

	result = pop(s);

	if(!isEmpty(s))
        {
                freeStack(s);
                fclose(input);
                return EXIT_FAILURE;
        }

	printf("%f\n", result);
	freeStack(s);
	fclose(input);
	return EXIT_SUCCESS;
}
