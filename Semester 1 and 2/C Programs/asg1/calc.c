/**********************************************************************
 * Filename:            calc.c
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
 *    A simple command-line calculator that supports bases 2 to 8
 **********************************************************************/
#include "numbers.h"

struct expression {
    int num[3];
    int base[3];
    int op;
};

/**********************************************************************
 * Function name:   main
 * Purpose:         calculator main function
 * Function Inputs: number of command-line arguments;
 *                  command-line arguments: base=b num1 op num2
 *                  where b can be 2 to 8 and op is one of +-x/
 * Function Output: returns 0 for success, 1 for failure
 * Version:         1.0
 * Author:          Robert Allison
 **********************************************************************/
int main(int argc, char *argv[])
{
    struct expression exp = { { 0 }, { 0 }, 0 };
    char num_str[100];

    /* check arguments */
    if (argc != 5)
    {
        fprintf(stderr, "usage: %s base=b num1 op num2\n"
            "   where b is the base (from %d to %d), and op is one of %s\n",
                basename(argv[0]), MIN_BASE, MAX_BASE, OPS);
        return 1;
    }

    /* get base value */
    if ((exp.base[0] = get_base(argv[1])) > MAX_BASE || exp.base[0] < MIN_BASE)
    {
        fprintf(stderr, "base %d too small (below %d) or too large (over %d)\n",
            exp.base[0], MIN_BASE, MAX_BASE);
        return 1;
    }

    /* use the same base for all */
    exp.base[1] = exp.base[2] = exp.base[0];

    /* get both numbers and convert */
    if ((exp.num[0] = in_cvt(argv[2], exp.base[0])) == -INT_MAX)
    {
        fprintf(stderr, "num1 %s is invalid for base %d\n",
            argv[2], exp.base[0]);
        return 1;
    }
    if ((exp.num[1] = in_cvt(argv[4], exp.base[1])) == -INT_MAX)
    {
        fprintf(stderr, "num2 %s is invalid for base %d\n",
            argv[4], exp.base[1]);
        return 1;
    }

    /* verify valid operator */
    if (strlen(argv[3]) == 1)
    {
        char *ptr;

        ptr = strchr(OPS, argv[3][0]);
        if (ptr != NULL)
            exp.op = ptr - OPS;
        else
        {
            fprintf(stderr, "invalid operation \"%s\"\n", argv[3]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "invalid operation \"%s\"\n", argv[3]);
        return 1;
    }

    /* perform arithmetic as requested */
    switch (exp.op)
    {
        case ADD:
            exp.num[2] = exp.num[0] + exp.num[1];
            break;
        case SUBTRACT:
            exp.num[2] = exp.num[0] - exp.num[1];
            break;
        case MULTIPLY:
            exp.num[2] = exp.num[0] * exp.num[1];
            break;
        case DIVIDE:
            if (exp.num[1] == 0)
            {
                printf("%s %s %s: divide by zero\n",
                    argv[2], argv[3], argv[4]);
                exp.num[2] = -INT_MAX;
                break;
            }
            exp.num[2] = exp.num[0] / exp.num[1];
            break;
        default:
            printf("invalid operator \'%s\'\n", argv[3]);
            return 1;
            break;
    }

    /* convert result for output */
    out_cvt(exp.num[2], exp.base[2], num_str, sizeof num_str);

    /* display result in both base and decimal */
    printf("%s base %2d: %s %s %s = %s\n",
        basename(argv[0]), exp.base[0], argv[2], argv[3], argv[4], num_str);
    printf("%s decimal: %d %s %d = %d\n",
        basename(argv[0]), exp.num[0], argv[3], exp.num[1], exp.num[2]);

    /* debug code is commented out */
#if 0
#define PRINT(x,y,z,w)  printf("%s = \"%s\", num = %o/%dd, out = \"%s\"\n", \
        (x), (y), (z), (z), out_cvt((z), (w), num_str, sizeof num_str))
    { /* debug block */
        char debug_str[MAX_STR + 1];

        PRINT("exp.num[0]", argv[2], exp.num[0], exp.base[0]);
        PRINT("exp.num[1]", argv[4], exp.num[1], exp.base[1]);
        out_cvt(exp.num[2], exp.base[2], debug_str, sizeof debug_str);
        PRINT("exp.num[2]", debug_str, exp.num[2], exp.base[2]);
    }
#endif
    return 0;
}
