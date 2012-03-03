/**********************************************************************
Filename:		ass0.c
Version: 		1.0                                         
Author:			William Collins                                             
Student No:  	040652633                                           
Course Name/Number: Game Programming CST8237                                 
Lab Sect: 		310                                                      
Assignment #:	0
Assignment name:Assignment 0	
Due Date:		January 28, 2012                                           
Submission Date:January 20, 2012
Professor:		Andrew Tyler                                           
Purpose: 		To create and manage a database of students
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SZ 128
#define MAX_RECORDS 1000

typedef struct StudentRecord
{
	char* firstName;
	char* lastName;
	int id;
	float mark;
}StudentRecord;

StudentRecord** g_ppRecords;
int g_numRecords = 0;
char* g_FileName;
FILE* g_pf;
typedef enum{FALSE,TRUE}BOOL;

void OpenFile(void);
void ListRecords(void);
void AddRecord(void);
void DeleteRecord(void);
void SaveRecords(void);

/********************************************************************
Function Name: 	main
Purpose: 		Main loop of the program
In parameters:	none
Out parameters: exit code
Version: 		1.0
Author: 		William Collins
**********************************************************************/

int main()
{
	BOOL running = TRUE;
	char response;
	OpenFile(); //Open a file and copy the records into memory

	while(running)
	{
		// The menu
		printf(
			"1. List records in memory\n"
			"2. Add a new record\n"
			"3. Delete last record\n"
			"4. Quit and Save records to file\n"
		);

		fflush(stdin);
		scanf("%c", &response);

		switch(response)
		{
		case '1':
			ListRecords();
			break;
		case '2':
			AddRecord();
			break;
		case '3':
			DeleteRecord();
			break;
		case '4':
			running = FALSE;
			SaveRecords();
			break;
		default: printf("Invalid choice\n");
		}
	}
	return 0;
}

/********************************************************************
Function Name: 	OpenFile
Purpose: 		Opens a file based on user input
In parameters:	none
Out parameters: none
Version: 		1.0
Author: 		William Collins
**********************************************************************/

void OpenFile()
{
	printf("OPEN FILE\n");
	printf("Please enter the name of the file to open: ");

	g_FileName = (char*) malloc(NAME_SZ * sizeof(char));
	scanf("%s", g_FileName);
	g_pf = fopen(g_FileName, "r+");

	printf("READING RECORDS INTO MEMORY\n");
	g_ppRecords = (StudentRecord**)malloc(sizeof(StudentRecord*) * MAX_RECORDS);

	//The file doesn't exists, so create it
	if (g_pf == NULL)
	{
		g_pf = fopen(g_FileName, "w+");
		printf("Empty File\n\n");
	}
	//The file does exists, so load it up into memory
	else 
	{
		StudentRecord *record = NULL;

		//Grab input from file one record/line at a time
		while(1){
			char fname[NAME_SZ];
			char lname[NAME_SZ];
			int result;
			record = (StudentRecord*) malloc(sizeof(StudentRecord));

			result = fscanf(g_pf, "%s %s %d %f", fname, lname, &record->id, &record->mark);
			if (result == EOF) break;

			record->firstName = (char*) malloc((strlen(fname) + 1) * sizeof(char));
			strcpy(record->firstName, fname);
			record->lastName = (char*) malloc((strlen(lname) + 1) * sizeof(char));
			strcpy(record->lastName, lname);
			g_ppRecords[g_numRecords] = record;

			g_numRecords++;
		}
		if (g_numRecords == 0)
			printf("Empty File\n\n");
		else
			printf("records read = %d\n\n", g_numRecords);
	}
	fclose(g_pf);
	 
}

/********************************************************************
Function Name:  ListRecords
Purpose: 		Lists all the records in the database
In parameters:	none
Out parameters: none
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void ListRecords()
{
	int i;
	printf("LIST RECORDS IN MEMORY\n");
	for (i = 0; i < g_numRecords; i++)
	{
		printf("Record #%d\n", i+1);
		printf("First Name = %s\n", g_ppRecords[i]->firstName);
		printf("Last Name = %s\n", g_ppRecords[i]->lastName);
		printf("ID = %d\n", g_ppRecords[i]->id);
		printf("Mark = %.2f\n\n", g_ppRecords[i]->mark);
	}
	if (g_numRecords == 0) {
		printf("No records\n\n");
	}
}

/********************************************************************
Function Name: 	AddRecord
Purpose: 		Adds a record to the database
In parameters:	none
Out parameters: none
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void AddRecord()
{
	StudentRecord *currentRecord = (StudentRecord*) malloc(sizeof(StudentRecord));
	char firstName[NAME_SZ];
	char lastName[NAME_SZ];
	
	//Check for array overflow
	if (g_numRecords == MAX_RECORDS){
		printf("Database is full. Cannot add new student\n");
		return;
	}

	printf("Please enter First Name: ");
	scanf("%s", firstName);

	printf("Please enter Last Name: ");
	scanf("%s", lastName);
	
	printf("Please enter ID: ");
	while (!scanf("%d", &currentRecord->id))
	{
		printf("Invalid ID.\nPlease enter ID: ");
		while(fgetc(stdin) != '\n');
	}

	printf("Please enter mark: ");
	while (!scanf("%f", &currentRecord->mark))
	{
		printf("Invalid mark.\nPlease enter mark: ");
		while(fgetc(stdin) != '\n');
	}
	
	currentRecord->firstName = (char *) malloc(strlen(firstName) * sizeof(char) + 1);
	strcpy(currentRecord->firstName, firstName);
	currentRecord->lastName = (char *) malloc(strlen(lastName) * sizeof(char) + 1);
	strcpy(currentRecord->lastName, lastName);

	g_ppRecords[g_numRecords] = currentRecord;
	g_numRecords++;

	printf("Number of Records = %d\n", g_numRecords);
	printf("ADDED A NEW RECORD IN MEMORY OK\n\n");
}

/********************************************************************
Function Name: 	DeleteRecord
Purpose: 		Deletes a record from the database
In parameters:	none
Out parameters: none
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void DeleteRecord()
{
	if (g_numRecords == 0){
		printf("No records to delete\n\n");
		return;
	}

	free(g_ppRecords[g_numRecords-1]->firstName);
	free(g_ppRecords[g_numRecords-1]->lastName);
	free(g_ppRecords[g_numRecords-1]);
	printf("Number of Records = %d\n", --g_numRecords);
	printf("DELETED A RECORD IN MEMORY OK\n\n");
}
/********************************************************************
Function Name: 	SaveRecords
Purpose: 		Saves the records to a file
In parameters:	none
Out parameters: none
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void SaveRecords()
{
	int i;
	//Write to file
	g_pf = fopen(g_FileName, "w");
	for (i = 0; i < g_numRecords; i++)
	{
		fprintf(g_pf, "%s %s %d %.2f\n", 
			g_ppRecords[i]->firstName,
			g_ppRecords[i]->lastName,
			g_ppRecords[i]->id,
			g_ppRecords[i]->mark);
	}
	fclose(g_pf);

	//Free up memory
	free(g_FileName);
	for (i = 0; i < g_numRecords; i++)
	{
		free(g_ppRecords[i]->firstName);
		free(g_ppRecords[i]->lastName);
		free(g_ppRecords[i]);
	}
	free(g_ppRecords);
}