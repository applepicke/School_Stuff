/**********************************************************************
 * Filename:            numbers.h
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
 *     #includes and constants for all files
 **********************************************************************/

/* system includes */
#define _GNU_SOURCE     /* proper form of basename(3) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* local includes */
#include "operators.h"
#include "functions.h"

/* constants */
#define MIN_BASE    2   /* smallest base */
/* WC 1010-01-25 */
#define MAX_BASE    16   /* largest base */
#define MAX_STR     (31 + 1 + 1) /* 31 bits, 1 sign, 1 EOS */
