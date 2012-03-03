/* This program illustrates how to use masks and bitwise operation 
 * Similar masks and operations should be used in
 * Symbol table implementation
 * Author: Svillen Ranev.
 */
#include <stdio.h>

/* MASKS*/
/* 16 bit field  MSB-> 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 <-LSB */
#define DEFAULTZ    0x0000   /* 0000 0000 0000 0000 */
#define DEFAULT     0xEA56   /* 1110 1010 0101 0110 */
#define RESET1413   0x9FFF   /* 1001 1111 1111 1111 */
#define SET1413_01  0x2000   /* 0010 0000 0000 0000 */
#define SET1413_10  0x4000   /* 0100 0000 0000 0000 */
#define SET_LSB     0x0001   /* 0000 0000 0000 0001 */
#define CHK_LSB     0x0001   /* 0000 0000 0000 0001 */

int main(void){
	
unsigned int s_field;

/* Print the number of bits in s_field */
 printf("Number of bits in s_field: %d\n", sizeof(s_field)*8);

/* Print the contents of s_field in hexadecimal */
 printf("Print garbage - variable not initialized\n");
/*Will generate a warrning - s_filed is not initialized yet */
 printf("The contents of s_field in hex: %4X\n", s_field);

/* set s_field to 0 using bitwise AND(&) */
 s_field = s_field & DEFAULTZ;
 printf("Set all bits to zero\n");
 printf("The contents of s_field in hex: %4X\n", s_field);

/* Set the default value of s_field using bitwise OR (|)  
 * Bitwise OR (|) is used because all bits in s_field was set to 0 
 * Bitwise AND can be used as well but all bits must be set to 1 first
 */
 s_field = s_field | DEFAULT;
 printf("Set all bits to default - 0xEA56 -> 1110 1010 0101 0110\n");
 printf("The contents of s_field in hex: %X\n", s_field);

/* Set bit 14 and 13 to 01. Do not change any other bit.
 * First reset, then set
 */
 s_field &= RESET1413;
 printf("Reset bits 14 and 13 - set them to zero\n");
 printf("The contents of s_field in hex: %X\n", s_field);
 printf("Set bits 14 and 13 to 01\n");
 s_field |= SET1413_01;
 printf("The contents of s_field in hex: %X\n", s_field);

/* Set bit 14 and 13 to 10. First reset, then set */
 s_field &= RESET1413;
 printf("Reset bits 14 and 13 - set them to zero\n");
 printf("The contents of s_field in hex: %X\n", s_field);
 s_field |= SET1413_10;
 printf("Set bits 14 and 13 to 10\n");
 printf("The contents of s_field in hex: %X\n", s_field);


/*Check the LSB (bit 0). If 0, set to 1. Do not change any other bits */
if((s_field & CHK_LSB) == 0){
  s_field |= SET_LSB;
  printf("Set LSB to 1\n");
}  
printf("The contents of s_field in hex: %X\n", s_field);

return 0;
}