#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FALSE = 0, TRUE }BOOL;

double enter_num();
int report(int);
void report_f(float);
void report_d(double);
void print_binary(size_t, unsigned char *);
void print_hex(size_t, unsigned char *);
int reverse(size_t, unsigned char *);
void safe_free(void *);
BOOL is_bigendian();

int main (int argc, const char * argv[]) {

	int running = TRUE;
	int control = 0;
	
	
	/* Let's loop through forever and break out when the user wants to */
	while (running){
			
		printf("\n1 = convert a float\n");
		printf("2 = convert a double\n");
		printf("3 - quit\n");
		
		/*Let's get a number from the user*/
		scanf("%d", &control);
		
		/* Convert to float or double depending on the user's choice */
		if (control == 1)
		{
			
			report_f((float)enter_num());
		}
		else if (control == 2)
		{
			report_d((double) enter_num());
		}
		/* Time to leave */
		else if (control == 3)
		{
			break;
		}
		/*Catch any errors without crashing */
		else 
		{
			int c;
			printf("You must enter a valid number!\n");
			/* Flush the input buffer */
			while( (c = fgetc( stdin )) != EOF && c != '\n' );
		}
		
		
	}
	
	printf("Toodles!!\n");
	return 0;
	
}

double enter_num()
{
	double num;
	
	printf("\nPlease enter the number to convert: ");
	while (!scanf("%lf", &num))
	{
		int c;
		printf("That is not valid! Please re-enter: ");
		/* Flush the garbage out of the input buffer */
		while( (c = fgetc( stdin )) != EOF && c != '\n' );
	}
	
	return num;	
}

void report_f(float f_num)
{	
	/*print out the original value */
	printf("\nfloat number is\t\t\t%f\n", f_num);
	
	/* We need to reverse the byte order if we are in little endian */
	if (!is_bigendian())
	{
		reverse(sizeof(float), (unsigned char *)&f_num);
	}
	
	/*print out the rest of the byte based values */
	print_binary(sizeof(float), (unsigned char *)&f_num);
	printf("Big-endian Hex:\t\t\t");
	print_hex(sizeof(float), (unsigned char *)&f_num);
	reverse(sizeof(float), (unsigned char *)&f_num);
	printf("Little-endian Hex:\t\t");
	print_hex(sizeof(float), (unsigned char *)&f_num);
	
}

void report_d(double d_num)
{	
	/*print out the original value */
	printf("\ndouble number is\t\t\t%lf\n", d_num);
	
	/* We need to reverse the byte order if we are in little endian */
	if (!is_bigendian())
	{
		reverse(sizeof(double), (unsigned char *)&d_num);
	}
	
	/* print the rest of the byte based values */
	print_binary(sizeof(double), (unsigned char *)&d_num);
	printf("Big-endian Hex:\t\t\t");
	print_hex(sizeof(double), (unsigned char *)&d_num);
	reverse(sizeof(double), (unsigned char *)&d_num);
	printf("Little-endian Hex:\t\t");
	print_hex(sizeof(double), (unsigned char *)&d_num);

}

void print_binary(size_t size, unsigned char *data)
{
	unsigned char i, j;
	
	printf("Binary:\t\t\t\t\t");
	
	/* cycle through each byte, storing it's binary value as chars */
	for (i = 0 ; i < size; i++)
	{
		for (j = 128; j > 0; j >>= 1)
		{
			if (data[i] & j)
			{
				printf("%c", '1');
			}
			else 
			{
				printf("%c", '0');
			}
			/* make sure to include spaces after each nibble */
			if (j == 16 || j == 1)
			{
				printf("%c", ' ');
			}
		}
	}
	printf("\n");
}

void print_hex(size_t size, unsigned char *data)
{	
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%.2X", (unsigned int)data[i]);
		printf(" ");
	}
	
	printf("\n");
}

int reverse(size_t count, unsigned char *bytes)
{
	unsigned char *temp;
	int i;
	
	/* Allocate enough to fit the string to be reversed as well as a null terminator */
	if ((temp = malloc(count)) == NULL)
	{
		return -1;
	}
	
	/* copy over the data in reverse */
	for (i = 0; i < count; i++)
	{
		temp[count - (i + 1)] = bytes[i];
	}
	/* now copy the bytes back to the original array of chars */
	for (i = 0; i < count; i++)
	{
		bytes[i] = temp[i];
	}
	
	/* clean up the mess we made */
	safe_free(temp);
	
	return 0;
}
		   
void safe_free(void *p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}	   
}

BOOL is_bigendian()
{
	int i = 1;
	/* The first byte of the int will tell if we are in big or little endian */
	if ( *(unsigned char *)&i == 0 )
	{
		return TRUE;
	}
	
	return FALSE;	
}
