/**********************************************************************
 * Filename:            output.c
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
 *    Convert a value to a string in a given base representation
 **********************************************************************/

#include "numbers.h"
#define SET_ERR(x,y,z)    *(z) = '*'; \
            if ((x) > sizeof (y)) strcpy((z), (y))

/**********************************************************************
 * Function name:   out_cvt
 * Purpose:         convert num in base as int to string for output 
 * Function Inputs: number representing the value
 *                  the base of the representation
 *                  string address for result
 *                  size of string
 * Function Output: returns a pointer to the string result;
 *                  there may be an error word in the string
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
char *out_cvt(int output, int base, char *place, size_t size)
{
    unsigned int rem, i = 0;
    int sign = +1;
    char temp[MAX_STR] = { 0 };

    /* zero output string */
    memset(place, '\0', size);

    /* size must be at least 1 char + EOS */
    if (size < 2)
        return place;
    if (output < 0)
    {
        /* work internally as positive only, save sign */
        output = -output;
        sign = -1;
    }
    else if (output == 0)
    {
        /* zero conversion is easy */
        *place = '0';
        return place;
    }
	
    /* loop ends when no digits left */
    while (output > 0)
    {
        /* return "overflow" or "*" for number too big */
        if (i >= sizeof temp)
        {
            SET_ERR(size, "overflow", place);
            return place;
        }
        /* get the right-most digit */
        rem = output % base;
        /* and convert to character or '*' for error */
		
		/* ****************WC 1010-01-25 ********************/
		if ((base == 16) && (rem > 10 && rem < 16))
		{
			temp[i] = hex_out(rem);
		}
		/****************************************************/
		
		else if ((temp[i] = btoc(rem, base)) == '*')
        {
            /* return bad digit*/
            SET_ERR(size, "invalid", place);
            return place;
        }
        i++;
        /* remove digit converted */
        output /= base;
    }
    /* add '-' if negative */
    if (sign == -1)
        temp[i++] = '-';
    if (strlen(temp) > (size - 1))
    {
        /* return output string too short */
        SET_ERR(size, "short", place);
        return place;
    }
    /* reverse string for output */
    rev_str(place, temp);
    return place;
}

/**********************************************************************
 * Function name:   btoc
 * Purpose:         convert digit value as int to char for output 
 * Function Inputs: number representing the value
 *                  the base of the representation
 * Function Output: returns a char for the digit; '*' for error
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
char btoc(int num, int base)
{
    /* return '*' for error or the character */
    if (num > base || base > MAX_BASE)
        return '*';
    return "01234567"[num];
}

/**********************************************************************
 * Function name:   hex_out
 * Purpose:         convert output to hex 
 * Function Inputs: output
 *                 
 * Function Output: char 
 * Version:         1.0
 * Author:          William Collins
 **********************************************************************/
char hex_out(int output)
{
	if (output == 10)
		return 'A';
	else if (output == 11)
		return 'B';
	else if (output == 12)
		return 'C';
	else if (output == 13)
		return 'D';
	else if (output == 14)
		return 'E';
	else if (output == 15)
		return 'F';
	else return '0';
}
