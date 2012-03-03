/******************************************************
FILENAME:			ass0.c
VERSION:			1
STUDENT_NAME:		William Curtis Collins
STUDENT_NUMBER:		040652633
COURSE:				CST8219 (C++ Programming)
LAB_SECTION:		11
ASSIGNMENT#:		1
ASSIGNMENT_NAME:	Students Database
DUE_DATE:			June 2, 2011
SUBMISSION_DATE:	May 26, 2011
PROFESSOR_NAME:		Andrew Tyler
PURPOSE:			Manage a database of students
*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
typedef enum {FALSE=0, TRUE}BOOL;

struct Name
{
	char* first_name;
	char* last_name;
};

struct Student
{
	struct Name* pName;
	int ID;
	float Fee;
};

//forward declarations
void InitStudents();
BOOL AddNewStudent();
BOOL DeleteStudent();
BOOL ReportStudents();
BOOL CleanUp();

struct Student g_Students[MAX];
BOOL b_running = TRUE;

int main(void)
{
	int i_response;

	InitStudents();

	while(b_running)
	{
		printf("\nPlease enter your choice\n");
		printf("1. Add a new student\n");
		printf("2. Delete a student\n");
		printf("3. Report Students\n");
		printf("4. Quit\n");

		scanf("%d", &i_response);
		switch(i_response)
		{
		case 1:
			if(!AddNewStudent())
				return 1;
			break;
		case 2:
			if(!DeleteStudent())
				return 1;
			break;
		case 3:
			if(!ReportStudents())
				return 1;
			break;
		case 4:
			CleanUp();
			b_running=FALSE;
			break;
		}
	}
	return 0;
}
/*****************************************************
FUNCTION NAME:	InitStudents
PURPOSE:		Initializes the Student structures
ARGUMENTS:		none
RETURN:			none
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void InitStudents()
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		g_Students[i].ID = -1;
	}
}
/*****************************************************
FUNCTION NAME:	AddNewStudent
PURPOSE:		Adds a new student to the database
ARGUMENTS:		none
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
BOOL AddNewStudent()
{
	int i;
	int largest_ID = -1;
	float fee;
	char* first_name = malloc(sizeof(char) * MAX);
	char* last_name = malloc(sizeof(char) * MAX);

	printf("\nPlease enter the new student first name (e.g. Barack): ");
	scanf("%s", first_name);

	printf("Please enter the new student last name (e.g. Obama): ");
	scanf("%s", last_name);
	
	/*Get fee to be paid checking the input for validity*/
	printf("Please enter the fee to be paid (e.g. $1000.00): ");
	fee = -1;
	while (!scanf("%f", &fee) || fee <= 0)
	{
		printf("Please enter the fee to be paid (e.g. $1000.00): ");
		fflush(stdin);
	}

	/*Find the largest of the IDs*/
	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID > largest_ID)
		{
			largest_ID = g_Students[i].ID;
		}
	}

	/*Find the next free Student structure*/
	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID == -1)
		{
			g_Students[i].Fee = fee;
			g_Students[i].ID = ++largest_ID;
			g_Students[i].pName = malloc(sizeof(struct Name));

			/*Allocate and assign first name*/
			g_Students[i].pName->first_name = malloc(sizeof(char) * (strlen(first_name)+1));
			strcpy(g_Students[i].pName->first_name, first_name);
			/*Allocate and assign second name*/
			g_Students[i].pName->last_name = malloc(sizeof(char) * (strlen(last_name)+1));
			strcpy(g_Students[i].pName->last_name, last_name);

			break;
		}	
	}

	/*Make sure to free up the buffer when we're done*/
	free(first_name);
	free(last_name);

	return TRUE;
}
/*****************************************************
FUNCTION NAME:	DeleteStudent
PURPOSE:		Deletes a student from the database
ARGUMENTS:		none
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
BOOL DeleteStudent()
{
	int ID;
	int i;
	char *buffer;
	int success = FALSE;

	printf("Please enter the ID of the student to delete: ");
	scanf("%d", &ID);

	/*locate the corresponding structure to the ID entered*/
	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID == ID)
		{
			free(g_Students[i].pName->first_name);
			free(g_Students[i].pName->last_name);
			free(g_Students[i].pName);
			g_Students[i].Fee = 0;
			g_Students[i].ID = -1;
			success = TRUE;

			break;
		}
	}

	if (success == FALSE)
	{
		printf("That ID does not exist!\n");
	}
	else
	{
		printf("\nstudent with ID = %d deleted\n", ID);
	}

	return TRUE;
}
/*****************************************************
FUNCTION NAME:	ReportStudents
PURPOSE:		Shows a list of the students in the database
ARGUMENTS:		none
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
BOOL ReportStudents()
{
	int i;

	/*Print a lovely table of values in the database*/
	printf("NAME\t\t\t\tID\t\tFEE\n");

	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID != -1)
		{
			printf("%s\t%s", g_Students[i].pName->first_name, g_Students[i].pName->last_name);
			printf("\t\t\t%d", g_Students[i].ID);
			printf("\t\t%.2f\n", g_Students[i].Fee);
		}
	}

	return TRUE;
}
/*****************************************************
FUNCTION NAME:	CleanUp 
PURPOSE:		Frees the memory that has been allocated
ARGUMENTS:		none
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
BOOL CleanUp()
{
	int i;

	/*Let's not forget to free this memory back into the wild*/
	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID != -1)
		{
			free(g_Students[i].pName->first_name);
			free(g_Students[i].pName->last_name);
			free(g_Students[i].pName);
		}
	}

	return TRUE;
}