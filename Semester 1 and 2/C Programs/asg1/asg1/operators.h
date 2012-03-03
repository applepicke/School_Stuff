/**********************************************************************
 * Filename:            operators.h
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
 *     all arithmetic operations supported
 **********************************************************************/

/* operators - '@' is only a place-holder for offset 0 */
#define OPS         "@+-x/"

/* offsets in OPS for use in switch */
#define OP_UNDEF    0       /* unused */
#define ADD         1       /* + */
#define SUBTRACT    2       /* - */
#define MULTIPLY    3       /* x - note, not * due to shell */
#define DIVIDE      4       /* / */
