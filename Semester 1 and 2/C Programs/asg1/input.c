/**********************************************************************
 * Filename:            input.c
 * Version:             1.0
 * Author:              Robert Allison
 * Student Number:      N/A
 * CST8204              Linux C Programming
 * Lab Section:         N/A
 * Assignment Number:   1
 * Assignment Name:     Multibase Calculator
 * Due Date:            N/A
 * Submission date:     N/A
 * Professor:           Robert Allison
 * Purpose:
 *     Convert a string to a value in a given base representation
 **********************************************************************/

#include "numbers.h"

/**********************************************************************
 * Function name:   in_cvt
 * Purpose:         convert input string to num in base as int 
 * Function Inputs: string representing the value
 *                  the base of the representation
 * Function Output: returns the value or -INT_MAX if error
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
int in_cvt(char *input, int base)
{
    size_t i, j, len = strlen(input);
    int value = 0, val;
    int sign = +1;
    unsigned int pos = 1;
	
	
    /* remove leading spaces */
    for ( i = 0; i < len; i++)
        if (input[i] != ' ')
            break;
    /* remove leading + */
    if (input[i] == '+')
        i++;
    /* see if negative */
    if (input[i] == '-')
    {
        i++;
        sign = -1;
    }
    /* skip trailing spaces */
    for ( j = len; j > i; j--)
        if (input[j - 1] != ' ')
            break;
    /* convert each char by base, add by position */
    for ( ; j > i; j--)
    {
		/***************** WC 1010-01-25******************/
		if (hex_in(input[j - 1]) != 0) 
			val = hex_in(input[j - 1]);
		/***************** WC 1010-01-25*****************/
		else if ((val = ctob(input[j - 1], base)) == -INT_MAX)
            return -INT_MAX; 
        value += (val * pos);
        pos *= base;
    }
    /* return value of string, correctly signed */
    return sign * value;
}

/**********************************************************************
 * Function name:   ctob
 * Purpose:         character to base 
 * Function Inputs: char (as int) to convert
 *                  base for conversion
 * Function Output: returns converted value or -INT_MAX if error
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
int ctob(int ch, int base)
{
    int val;

    /* static table of values for 0x00 to 0xFF
     * including values for '0' to '7' (0x30 to 0x37)
     */
    static const char values[256] = {
        "****************" /* 0x */
        "****************" /* 1x */
        "****************" /* 2x */
        "\x0\x1\x2\x3\x4\x5\x6\x7********" /* 3x */
        "****************" /* 4x */
        "****************" /* 5x */
        "****************" /* 6x */
        "****************" /* 7x */
        "****************" /* 8x */
        "****************" /* 9x */
        "****************" /* Ax */
        "****************" /* Bx */
        "****************" /* Cx */
        "****************" /* Dx */
        "****************" /* Ex */
        "****************" /* Fx */ };

    /* return value from look-up table or -INT_MAX */
    if (base > MAX_BASE)
        return -INT_MAX;
    return (val = values[ch]) >= base || val == '*' ? -INT_MAX : val;
}

/**********************************************************************
 * Function name:   hex_in
 * Purpose:         letter to hex
 * Function Inputs: char to be converted to int
 *                  
 * Function Output: Returns letters as Hex values
 * Version:         1.0
 * Author:          William Collins
 **********************************************************************/

char hex_in(char let)
{	
	if (let == 'a' || let == 'A')
		return 10;
	else if (let == 'b' || let == 'B')
		return 11;
	else if (let == 'c' || let == 'C')
		return 12;
	else if (let == 'd' || let == 'D')
		return 13;
	else if (let == 'e' || let == 'E')
		return 14;
	else if (let == 'f' || let == 'F')
		return 15;
	else
		return 0;
}

