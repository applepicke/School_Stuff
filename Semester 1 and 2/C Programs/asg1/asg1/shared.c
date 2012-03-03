/**********************************************************************
 * Filename:            shared.c
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
 *     Service functions
 **********************************************************************/

#include "numbers.h"

/**********************************************************************
 * Function name:   get_base
 * Purpose:         get base value from argv[1] as "base=b"
 * Function Inputs: pointer to argv[1] (or equivalent)
 * Function Output: returns the base value or -1 if error
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
int get_base(char *base_str)
{
    int base;
    char *err_ptr;

    /* if the string starts wrong, return error */
    if (strncmp(base_str, "base=", 5) != 0)
        return -1;
    /* convert the value */
    base = strtoul(&base_str[5], &err_ptr, 10);
    /* return base or -1 for error */
    if (base == 0 || *err_ptr != '\0')
        return -1;
    return base;
}

/**********************************************************************
 * Function name:   rev_str
 * Purpose:         reverse a string end-for-end
 * Function Inputs: pointer to destination string
 *                  pointer to source string
 * Function Output: returns pointer to destination string
 * Version:         1.0
 * Author:          Robert Allison
 * Note:            destination size is assumed to be large enough
 *                  for the source string; check before call
 **********************************************************************/
char *rev_str(char *to, char *from)
{
    size_t len = strlen(from);
    size_t i, j;

    /* copy characters from right end to left end */
    for (i = 0, j = len - 1; i < len; i++, j--)
        to[i] = from[j];
    /* return pointer */
    return to;
}
