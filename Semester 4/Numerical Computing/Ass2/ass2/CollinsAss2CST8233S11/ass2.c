/******************************************************
FILENAME:			ass2.c
VERSION:			1
STUDENT_NAME:		William Curtis Collins
STUDENT_NUMBER:		040652633
COURSE:				CST8233 (Numerical Computing)
LAB_SECTION:		310
ASSIGNMENT#:		2
ASSIGNMENT_NAME:	Least Squares Fit
DUE_DATE:			July 12, 2011
SUBMISSION_DATE:	July 12, 2011
PROFESSOR_NAME:		Andrew Tyler
PURPOSE:			To perform linear regression to either linear or
					exponential data. The data points can be determined at
					runtime by the user, or from a file.
*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

/*Constants*/
#define R_FROM_USER 1
#define R_FROM_FILE 2
#define EXIT 3

#define FIT_STRAIGHT 1
#define FIT_EXP 2

#define MAX_FILENAME 30
#define MAX_NUM_SIZE 40
#define SIG_DIG 3

/* Function prototypes */
int getSelectionFromUser(int min, int max);
int readDataFromKeyboard(float **x, float **y);
int readDataFromFile(float **x, float **y);
int getDecimalPlaces(float error, int sig_digits);
void linearRegression(float *x, float *y, int ndata, float *m, float *c, float *sigm, float *sigc);

int main()
{
	int choice = 0, dpm, dpc, i;
	int ndata;
	float *x, *y;
	float m, c;
	float sigm, sigc;

	while (1) {
		
		printf("\n***********************************************\n");
		printf("Linear Regression of Data - DATA SOURCE MENU\n");
		printf("1. Read Data from Keyboard\n");
		printf("2. Read Data from File\n");
		printf("3. Quit\n");
		printf("***********************************************\n");
		printf("Select an option: ");

		choice = getSelectionFromUser(1, 3);

		if (choice == EXIT){
			break;
		}

		if (choice == R_FROM_USER){
			ndata = readDataFromKeyboard(&x, &y);
		}
		if (choice == R_FROM_FILE){
			ndata = readDataFromFile(&x, &y);
		}

		printf("\nLINEAR OR EXPONENTIAL FUNCTION\n");
		printf("1. Fit data to straight line:\ty = m*x + c\n");
		printf("2. Fit data to exponential:\ty = a*exp(-b*x)\n");
		printf("Select an option: ");

		choice = getSelectionFromUser(1, 2);

		
		
		if (choice == FIT_STRAIGHT){

			/*Perform linear regression on our data*/
			linearRegression(x, y, ndata, &m, &c, &sigm, &sigc);

			/*Create a string out of the errors to determine decimal places*/\
			/*NOTE: decimal places for errors are to 3 significant digits!*/
			dpm = getDecimalPlaces(sigm, SIG_DIG);
			dpc = getDecimalPlaces(sigc, SIG_DIG);

			printf("\nSTRAIGHT LINE:\ty = (%.*f+-%.*g)*x + (%.*f+-%.*g)\n", dpm, m, SIG_DIG, sigm, dpc, c, SIG_DIG, sigc);
		}

		if (choice == FIT_EXP){
			/*Each y should be a lnY*/
			for (i = 0; i < ndata; i++){
				y[i] = (float) log(y[i]);
			}

			/*Perform linear regression on our data*/
			linearRegression(x, y, ndata, &m, &c, &sigm, &sigc);

			/*C is equal to lna*/
			c = (float) exp(c);
			/*Since we are not calculating errors, I am using a consistent number of decimal places*/
			printf("\nEXPONENTIAL:\ty = (%.3f)*exp((%.3f)*x)\n", c, m);
		}
	}
	free(x);
	free(y);

	printf("\nToodles!!\n");
	return 0;
}

/*****************************************************
FUNCTION NAME:	getSelectionFromUser
PURPOSE:		Asks the user for a selection choice
ARGUMENTS:		min - the minimum value the user can choose
				max - the maximum value the user can choose
RETURN:			Returns the user's selection
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
int getSelectionFromUser(int min, int max)
{
	int i = 0;

	while (!scanf("%d", &i) || (i < min || i > max) ){
		printf("Not a valid choice! Please re-enter: ");
		while( fgetc( stdin )!= '\n' ); /*flush garbage from the buffer*/
	}

	return i;
}

/*****************************************************
FUNCTION NAME:	readDataFromKeyboard
PURPOSE:		Asks the user for an arbitrary number of data sets
ARGUMENTS:		x - A pointer to the set of x data values
				y - A pointer to the set of y data values
RETURN:			Returns the number of data sets acquired
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
int readDataFromKeyboard(float **x, float **y)
{
	int ndata, i;

	printf("\nKeyboard Input\n");
	printf("How many x-y data pairs?\n");

	/*Get number of pairs, and allocate memory for them*/
	ndata = getSelectionFromUser(2, INT_MAX);
	*x = malloc(sizeof(float) * ndata);
	*y = malloc(sizeof(float) * ndata);

	/*Get each pair from the user*/
	for (i = 0; i < ndata; i++){
		printf("enter x, y pair #%d: ", i+1);
		while (!scanf("%f %f", (*x)+i, (*y)+i)){
			printf("Invalid x, y pair! Re-enter: ");
			while (fgetc(stdin) != '\n'); /*flush garbage from the buffer*/
		}
	}

	printf("\ndata entry complete\n");

	return ndata;
}

/*****************************************************
FUNCTION NAME:	readDataFromFile
PURPOSE:		Reads an arbitrary number of data sets from a text file
ARGUMENTS:		x - A pointer to the set of x data values
				y - A pointer to the set of y data values
RETURN:			Returns the number of data sets acquired
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
int readDataFromFile(float **x, float **y) 
{
	int ndata = 0, i;
	float temp;
	char filename[MAX_FILENAME];
	FILE *dataFile;
	
	/*Ask the user for a file to open*/
	printf("please enter the name of the file to open:");
	scanf("%s", filename);
	while ( (dataFile = fopen(filename, "r")) == NULL) {		
		printf("File cannot be opened! Try a different name: ");
		while (fgetc(stdin) != '\n');
		scanf("%s", filename);
	}
	printf("\nFILE OPENED FOR READING\n");
	
	/*Determine how many elements are in the file*/
	while ( fscanf(dataFile, "%f %f", &temp, &temp) != EOF ) {
		ndata++;		
	}
	
	*x = malloc(sizeof(float) * ndata);
	*y = malloc(sizeof(float) * ndata);
	
	/*Re-open the file*/
	dataFile = fopen(filename, "r");
	
	/*Get data pairs from the file*/
	for (i = 0; i < ndata; i++) {
		fscanf(dataFile, "%f %f", (*x)+i, (*y)+i);
	}
	
	printf("There are %d records.\n", ndata);
	
	return ndata;
}

/*****************************************************
FUNCTION NAME:	getSignificantDigits
PURPOSE:		Determine the number of significant digits in a number
ARGUMENTS:		error - The error value that you want to use as a reference point
				sig_digits - The number of significant digits you want represented in the error
RETURN:			The number of digits after the decimal
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
int getDecimalPlaces(float error, int sig_digits){
	char str_error[MAX_NUM_SIZE];
	int i, dec_places = 0, len;

	/*Make a string representation of the error*/
	sprintf(str_error, "%.*g", sig_digits, error);
	len = strlen(str_error);

	/*calculate the digits after the decimal*/
	for (i = 0; str_error[i] != '.'; i++);
	i++;
	for ( ; i < len; i++, dec_places++);
	
	return dec_places;

}

/*****************************************************
FUNCTION NAME:	linearRegression
PURPOSE:		performs linear regression on a set of data.
ARGUMENTS:		x - A pointer to the set of x data values
				y - A pointer to the set of y data values
				ndata - The number of x,y sets provided
				m - The slope of the best fit line
				sigm - The error in m
				sigc - The error in c
RETURN:			void
VERSION:		1.0
AUTHOR:			Andrew Tyler (Taken from Statistics and 
				Least Squares Fitting with comments added)
*****************************************************/
void linearRegression(float *x, float *y, int ndata, float *m, float *c, float *sigm, float *sigc)
{	
	int i;
	float t, sxoss, sx=0.0, sy=0.0, st2=0.0, ss, sumSquares=0.0, sigma2, residual;
	*m = 0.0;

	/* determine the sum of the x's and the sum of the y's */
	for (i = 0; i < ndata; i++){
		sx += x[i];
		sy += y[i];
	}

	ss = (float) ndata; /* ss is a convenient notation for the number of x,y sets */
	sxoss = sx/ss;

	/*Calculate st2 and a partial m*/
	for(i = 0; i < ndata; i++){
		t = x[i] - sxoss;
		st2 += t * t;
		*m += t * y[i];
	}

	*m /= st2; /* Finish the calculation of m */
	*c = (sy-sx*(*m)) / ss; /*Calculate c*/

	/*Calculate the standard deviation */
	for (i = 0; i < ndata; i++) {
		residual = y[i] - (*m)*x[i]-(*c);
		sumSquares += residual * residual;
	}
	sigma2 = sumSquares / (ndata - 2);

	/*Calculate the errors in m and c */
	*sigm = (float) sqrt(sigma2 / st2);	
	*sigc = (float) sqrt( sigma2 * ((1.0 + sx*sx/(ss*st2)) / ss));

	/*If the error is more than the value, make them equal
	if (*sigc >= *c){
		*sigc = *c;
	}
	if (*sigm >= *m){
		*sigm = *m;
	}*/
}