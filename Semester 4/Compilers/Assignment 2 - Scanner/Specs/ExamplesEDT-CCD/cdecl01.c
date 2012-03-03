/* Complex C declarations - reading and writing
 * Working with arrays
 * Author: Svillen Ranev
*/
#include <stdio.h>
int name01[]; /* compiles - global*/

int main (void){
/*
Syntax; size is unknown or zero
int name02[];
*/
/* const declarations */
const a = 5;
/* int b[a]; illegal in C */
const int * pci; /* pointer to constant */
int const * pcoi; /* pointer to constant */

int name02[] = {1,2,3};  /* works */
int * const cpi = name02; /*constant pointer to int */
int *pi02; /*pointer to int */
/* pointer to array of int */
int (*pa02)[]; /* int (*pa02)[3]; */
/* array of pointer to int */
int *name03[3];
/* pointer to array of pointers to int */
int *(*pname04)[3]; /* must have a size */
/*array of pointer to pointer to int */
int **pname05[3]; /* *(*pname05[3]) */
 
pci = pcoi = &a;
/*Syntax: Can not modify a constant object
*pci = a; *pcoi = a;
cpi++;
*/
pi02 = name02;
printf("pi02: %d\n", pi02[1]); /* prints 2 */
pa02 = &name02;
printf("pa02: %d\n", (*pa02)[1]);  /* prints 2 */

name03[0] = &name02[2];
pname04 = &name03;
printf("pname04: %d\n", *(*pname04)[0]); /* prints 3 */

pname05[0] = &pi02;
printf("pi02: %d\n", *pi02);  /* prints 1 */
printf("pname05: %d\n", **pname05[0]); /* prints 1 */
return 0;
}