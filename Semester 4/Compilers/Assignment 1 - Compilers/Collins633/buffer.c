/* File Name: buffer.c
 * Version: 1.0
 * Author: William Collins (040652633)       
 * Course: CST8152 - Compilers
 * Assignment: 1
 * Date: May 18, 2011
 * Professor: Svillen Ranev
 * Purpose: Provide a utility to create and manage a buffer
 * Function list: b_create, ca_addc, b_reset, b_destroy, ca_isfull, 
				  ca_getsize, ca_getcapacity, ca_setmark, ca_getmark,
				  ca_getmode, ca_pack, ca_print, ca_load
 */
#include "buffer.h"

/*
 * Purpose: Creates a new buffer in memory
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: malloc, free
 * Parameters:	init_capacity - how many chars of storage you want initially
				inc_factor - when storage runs out, this determines how much it will increase by
				o_mode - what mode the buffer is in. 
 * Return value: A pointer to the newly created buffer, or NULL on error
 */
Buffer *b_create(int init_capacity, char inc_factor, char o_mode)
{
	/* Allocate memory for the buffer*/
	Buffer *buff = (Buffer *)malloc(sizeof(Buffer)); 
	if (buff == NULL)
	{ 
		return NULL;
	}

	/* Make sure the capacity is a positive amount */
	if (init_capacity <= 0)
	{
		free(buff);
      buff = NULL;
		return NULL;
	}
	/* set the buffer's initial capacity */
	buff->capacity = init_capacity;

	/* Allocate memory for the data in the buffer */
	buff->ca_head = (char *) malloc(init_capacity);
	if (buff->ca_head == NULL)
	{
		free(buff);
      buff = NULL;
		return NULL;
	}

	/* check for a valid mode, and a valid inc_factor */ 
	if (o_mode == 'f' || inc_factor == 0) 
	{
		buff->mode = FIXED;
		buff->inc_factor = 0;
	}
	else if (o_mode == 'a')
	{
		buff->mode = ADDITIVE;
		buff->inc_factor = inc_factor;
	}
	else if (o_mode == 'm' && inc_factor >= MULTI_MIN && inc_factor <= MULTI_MAX)
	{
		buff->mode = MULTIPLICATIVE;
		buff->inc_factor = inc_factor;
	}
	else
	{
		/* This buffer isn't valid, so free up the memory we took and get out of here */
		free(buff->ca_head);
		free(buff);
      buff = NULL;
		return NULL;
	}

	/* Default the remaining members of the buffer */
	buff->addc_offset = 0;
	buff->mark_offset = 0;
	buff->r_flag = 0;

	return buff;
	

}

/*
 * Purpose: Adds a single character to the buffer, expanding storage if it needs to
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: realloc
 * Parameters:	pB - a pointer to the buffer you want to add to
				symbol - the character you want to add to the buffer
 * Return value: A pointer to the altered buffer, or NULL on error
*/
Buffer *ca_addc(Buffer *pB, char symbol)
{
	/*I don't want to work with a null pointer*/
	if (pB == NULL)
	{
		return NULL;
	}

	/* reset the r_flag to say the last call wasn't to reallocate memory */
	pB->r_flag = 0;

	/*If we are about to overflow, get some more memory for the buffer*/
	if (pB->addc_offset >= pB->capacity)
	{
		char *temp; /* temporary character array that can hold the buffer data while we reallocate */
		int space_avail; /* holds the amount of free space we can realistically use for the buffer data */
		int new_inc = 0; /* holds the increment amount based on buffer mode */

		switch (pB->mode)
		{
		case FIXED: 
			/* We aren't about to increase a fixed buffer, so get out of here*/
			return NULL;
		case ADDITIVE: 
			/* Check for int overflow, and assign new capacity to the buffer*/
			if ( (pB->capacity + (unsigned char)pB->inc_factor) < 1)
			{
				return NULL;
			}
			/* in additive mode, the increment factor is simply added to the capacity */
			new_inc = (unsigned char)pB->inc_factor;
			break;
		case MULTIPLICATIVE:
			/* Check for overflow, and increase the increase amount if it is okay */
			if (pB->capacity >= INT_MAX)
			{
				return NULL;
			}
			/* for multiplicative mode the new increment is calculated using how much space you can reasonably hold */
			space_avail = INT_MAX - pB->capacity;
			new_inc = space_avail * (float)pB->inc_factor / (float)100.00;
         
      	/* If we can't increase the buffer anymore then we need to get out of here
         before it blows! */
      	if (new_inc == 0)
      	{
       		return NULL;
      	}
			break;

		}
		/* Reallocate the memory for the data in the buffer*/
		temp = realloc(pB->ca_head , sizeof(char) * (pB->capacity + new_inc));
		if (temp == NULL)
		{
			return NULL;
		}
		if (pB->ca_head != temp)
		{
			pB->r_flag = SET_R_FLAG;
		}
		pB->ca_head = temp;
		pB->capacity += new_inc;
	
	}
	/*Now we can finally add the symbol to the buffer*/
	pB->ca_head[pB->addc_offset] = symbol;
	pB->addc_offset++;

	return pB;

}

/*
 * Purpose: Resets the data in the buffer
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - pointer to the buffer to be cleared			   
 * Return value: -1 is returned on error, while 0 is returned on success
 */
int b_reset (Buffer *pB)
{
	/* Can't do anything with a NULL pointer*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	/* setting the offset to zero points the array back to the first element */
	pB->addc_offset = 0;	

	return 0;
}

/*
 * Purpose: frees up the memory taken by the buffer and its data
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: free
 * Parameters:	pB - a pointer to the buffer you want to destroy		   
 */
void b_destroy (Buffer *pB)
{
	/* Make sure the buffer exists */
	if (pB != NULL)
	{
		/* Make sure it has data in it */
		if (pB->ca_head != NULL)
		{
			free(pB->ca_head);
         pB->ca_head = NULL;
		}
		free(pB);
      pB = NULL;
	}
}

/*
 * Purpose: Tests to see if the buffer is at capacity
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer you want to test		   
 * Return value: returns -1 on error, 1 if the buffer is at capacity, and 0 otherwise
*/
char ca_isfull (Buffer *pB)
{
	/*We say no to null*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	if (pB->addc_offset == pB->capacity)
	{
		return 1;
	}
	return 0;
}

/*
 * Purpose: gets the size of what is currently stored in the buffer
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer you want the size of		   
 * Return value: returns -1 on error or the size of the buffer otherwise
*/
int ca_getsize (Buffer *pB)
{
	/*Let's cut out this null pointer passing nonsense*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	return pB->addc_offset;
}

/*
 * Purpose: gets the capacity of the specified buffer
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer in which you want the capacity of		   
 * Return value: returns -1 on error, otherwise it returns the capacity of the buffer
*/
int ca_getcapacity (Buffer *pB)
{
	/*Are you null? We don't want you here if you are*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	return pB->capacity;
}

/*
 * Purpose: Sets a particular mark in the buffer designating some point of interest
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer in which to set the mark
				mark - the offset from the beginning of the buffer data where the mark will point to
 * Return value: returns -1 on error, otherwise returns the mark
*/
int ca_setmark (Buffer *pB, int mark)
{
	/*We hate null pointers*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	if (mark > pB->addc_offset || mark <= 0)
	{
		return R_FAIL_1;
	}
	pB->mark_offset = mark;
	return mark;

}

/*
 * Purpose: returns the mark of a buffer to the caller
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer that holds the mark		   
 * Return value: -1 on error, otherwise returns the mark offset
*/
int ca_getmark (Buffer *pB)
{
	/*Get these null pointers out of here*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	return pB->mark_offset;
}

/*
 * Purpose: returns the storage mode of the buffer to the caller
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - a pointer to the buffer you want the mofe of		   
 * Return value: -1 on error, otherwise returns the mode 
*/
int ca_getmode (Buffer *pB)
{
	/*We don't take kindly to null pointers around here*/
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	return pB->mode;

}

/*
 * Purpose: shrinks the capacity of a buffer to the size of the data currently occupying it
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: realloc
 * Parameters:	pB - a pointer to the buffer that is to be packed		   
 * Return value: a pointer to the altered buffer, or NULL on error
*/
Buffer *ca_pack( Buffer *pB )
{
	char *temp;

	/*Null pointers aren't welcome here*/
	if (pB == NULL)
	{
		return NULL;
	}
	if (pB->ca_head == NULL)
	{
		return NULL;
	}
   /*Make sure that we don't have a weird offset*/
	if (pB->addc_offset > pB->capacity || pB->addc_offset < 0)
	{
		return NULL;
	}
	temp = realloc(pB->ca_head, (sizeof(char) * (pB->addc_offset + 1 )));
	if (temp == NULL)
	{
		return NULL;
	}
	if (temp != pB->ca_head)
	{
		pB->r_flag = 1;
	}
	pB->ca_head = temp;

   /*Temp will go out of scope anyway, but we are practicing overly-defensive
   programming, so why not protect against a dangling pointer here in case we
   add more to the function eventually later on*/
   temp = NULL;
   
	pB->capacity = (sizeof(char) * (pB->addc_offset + 1));
	return pB;

}

/*
 * Purpose: prints the data in the buffer to stdout
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: printf
 * Parameters:	pB - a pointer to the buffer that is to be printed		   
 * Return value: returns -1 on error, otherwise returns the number of characters printed
*/
int ca_print (Buffer *pB)
{
	int i;
	if (pB == NULL)
	{
		return R_FAIL_1;
	}
	/*Need to loop through the character array because there is no null terminator*/
	for (i = 0; i < pB->addc_offset; i++)
	{
		printf("%c", pB->ca_head[i]);
	}
	printf("\n");
	return pB->addc_offset;
}

/*
 * Purpose: copy's a file of data into the buffer
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Called functions: fgetc
 * Parameters:	fi - a pointer to a file descriptor to a valid file containing data
				pB - a pointer to the buffer that is to hold the data
 * Return value: returns -1 on error, LOAD_FAIL if there is an error while copying, and otehrwise returns character count
*/
int ca_load (FILE *fi,Buffer *pB)
{
	char temp; /* Temporary character storage used for checking for end of file character */

	if (pB == NULL || fi == NULL)
	{
		return R_FAIL_1;
	}
	if (pB->ca_head == NULL)
	{
		return R_FAIL_1;
	}

	/* copy over the contents of the file */
	while (!feof(fi)) 
	{
		if ((temp = (char) fgetc(fi)) != EOF )
		{
			if ( (pB = ca_addc(pB, temp) ) == NULL)
			{
				return LOAD_FAIL;
			}
		}
	}
	return pB->addc_offset;
}

