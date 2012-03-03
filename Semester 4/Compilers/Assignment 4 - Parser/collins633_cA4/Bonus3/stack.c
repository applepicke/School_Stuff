/* File Name: stack.c
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 4
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: A stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*
 * Purpose: creates a stack
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	data_size - the size of the data the stack will hold
				capacity - how many data elements the stack can hold
 * Returns: A stack if successful, otherwise NULL
*/
Stack *s_create(int data_size, int capacity){
	Stack *stack = (Stack*)malloc(sizeof(Stack));

	stack->data = (unsigned char *)malloc(data_size * capacity);

	/*handle an allocation error*/
	if (stack->data == NULL){
		return NULL;
	}

	stack->capacity = capacity;
	stack->data_size = data_size;

	/*The next piece of data will be placed at the beginning*/
	stack->next = 0;

	return stack;
}

/*
 * Purpose: pushes a piece of data onto the stack
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - The stack to use
				data - the piece of data to be pushed
*/
void push(Stack *stack, void *data){
	int i;
	char *c_data = (char*) data;

	/*return to prevent runtime errors*/
	if (stack == NULL || data == NULL){
		return;
	}

	/*Let's not allow overflow*/
	if (stack->next == stack->capacity){
		return;
	}

	/*copy the data into the stack*/
	for (i = 0; i < stack->data_size; i++){
		stack->data[stack->next * stack->data_size + i] = c_data[i];
	}

	/*Let's not forget to move where our next item will go*/
	stack->next++;
}

/*
 * Purpose: pops a piece of data off the stack
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack to use
				data - the location to put the data. If NULL, 
				then will pop off the next item and it will disappear
*/
void* pop(Stack *stack, char *data){
	int i;

	/*Errors*/
	if (stack == NULL){
		return NULL;
	}
	
	if (stack->next * stack->data_size <= 0){
		return NULL;
	}

	stack->next--;

	if (data == NULL){
		return NULL;
	}

	/*Retrieve the data from the stack*/
	for(i = 0; i < stack->data_size; i++){
		data[i] = stack->data[stack->next * stack->data_size + i];
	}

	return (void*)data;

}

/*
 * Purpose: destroys a stack
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack to use
*/
void s_destroy(Stack *stack){

	/*Free Memory*/	
	free(stack->data);
	free(stack);
	
}

void s_reverse(Stack *stack){
	int i, j, k;
	int length = stack->next;
	unsigned char *r_string = stack->data;
	unsigned char *t_string = (unsigned char*)malloc(stack->data_size * stack->capacity);

	/*reverse the order of chunks of data*/
	for (i = 0, j = length - 1 ; i < length && j >= 0; i++, j--){
		for (k = 0; k < stack->data_size; k++){
			t_string[j * stack->data_size + k] = r_string[i * stack->data_size + k];
		}	
	}

	/*copy the temporary values into the stack*/
	memcpy(stack->data, t_string, (size_t)stack->data_size * length);
	free(t_string);
}

void* peak(Stack *stack){
	return &stack->data[stack->next * stack->data_size - stack->data_size];
}
