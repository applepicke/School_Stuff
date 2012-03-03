#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){

	Stack *stack = s_create(sizeof(double), 100);
	double a = 25.098;
	double b = 35.89;
	double c = 45.34;

	push(stack, &a);
	push(stack, &b);

	printf("popped value is %.2lf\n", *(double*)pop(stack, (char*)&b));

	push(stack, &c);

	printf("popped value is %.2lf\n", *(double*)pop(stack, (char*)&c));
	printf("popped value is %.2lf\n", *(double*)pop(stack, (char*)&a));

	return 0;
}