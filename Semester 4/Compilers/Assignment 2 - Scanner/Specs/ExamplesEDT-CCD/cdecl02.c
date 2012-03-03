/* Complex C declarations - reading and writing
 Pointers to functions, array of pointer to functions 
 Author: Svillen Ranev
*/
#include <stdio.h>
/*function declarations - protopypes */
int sum (int a, int b);
int max (int a, int b);
int min (int a, int b);
/* pointer to function taking two ints and returning int */
typedef int (*PTR_F)(int,int); /*PTR_F is the new data type name */

/* exotic declarations */
/* foo is a function returning a pointer to array of pointer
   to function taking char and returning int */
int (*(*foo(void))[])(char);

/* arr is an array of 3 pointer to function taking no parameters
  returning pointer to array [5] of pointer to int */
int * (*(*arr[3])(void))[5];

int main (void){
/* pointer to function taking two ints and returning int */
int (*ptr_f)(int,int);
PTR_F ptr_ft; /* same as above */
/* array of pointer to function */
int (*aptr_f[3])(int,int);
PTR_F aptr_ft[3]; /* same as above */

/* Initialization or assignment */
ptr_f = ptr_ft = sum;
aptr_f[0] = aptr_ft[0] = sum;
aptr_f[1] = aptr_ft[1] = max;
aptr_f[2] = aptr_ft[2] = min;

/* function call */
(*ptr_f)(2,2); /* calls sum() */
  ptr_f (2,2); /* ANSI standard extension */
(*ptr_ft)(2,2); /* calls sum(2.2) */
(*aptr_f[0])(2,2); /* calls sum() */
printf("Sum: %d\n", aptr_f[0](2,2)); /* ANSI extension */
(*aptr_f[1])(3,2); /* calls max() */
printf("Min: %d\n",(*aptr_f[2])(2,7)); /* calls min() */
return 0;
}
/* function definitions */
int sum (int a, int b){return a+b;}
int max (int a, int b){return (a>b)? a:b;}
int min (int a, int b){return (a<b)? a:b;}
