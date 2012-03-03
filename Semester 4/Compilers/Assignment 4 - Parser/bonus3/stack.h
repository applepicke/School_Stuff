/* File Name: stack.h
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 4
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: A stack
 */

/*The Stack Structure*/
typedef struct Stack {
	int capacity;		/*The capacity of the stack*/
	int data_size;		/*The size of the data being placed in the stack in BYTES*/
	int next;			/*The offset to where the next data will be placed*/
	unsigned char *data;/*The stack data itself*/
}Stack;

/*function prototypes for the stack*/
Stack *s_create(int data_size, int capacity);
void push(Stack *, void *);
void* pop(Stack *, char *data);
void s_destroy(Stack *);
void s_reverse(Stack *);
void* peak(Stack *);
