/******************************************************
FILENAME:			ass1.cpp
VERSION:			1
STUDENT_NAME:		William Curtis Collins
STUDENT_NUMBER:		040652633
COURSE:				CST8219 (C++ Programming)
LAB_SECTION:		11
ASSIGNMENT#:		1
ASSIGNMENT_NAME:	Students Database
DUE_DATE:			June 16, 2011
SUBMISSION_DATE:	June 16, 2011
PROFESSOR_NAME:		Andrew Tyler
PURPOSE:			Manage a database of students
*******************************************************/
#include <iostream>
#include "Name.h"
#include "Student.h"

//ass1.cpp
using namespace std;
#define MAX 1000
Student g_Students[MAX];
bool b_running = true;

//Forward declarations
bool AddNewStudent();
void DeleteStudent();
void ReportStudents();

int main(void)
{
	int i_response;

	while(b_running)
	{
		cout <<"\nPlease enter your choice"<<endl;
		cout <<"1. Add a new student"<<endl;
		cout <<"2. Delete a student"<<endl;
		cout <<"3. Report Students"<<endl;
		cout <<"4. Quit\n"<<endl;

		cin>>i_response;
		switch(i_response)
		{
		case 1:
			if(!AddNewStudent())
				return 1;
			break;
		case 2:
			DeleteStudent();
			break;
		case 3:
			ReportStudents();
			break;
		case 4:
			b_running=false;
			break;
		}
	}
	return 0;

}

/*****************************************************
FUNCTION NAME:	AddNewStudent
PURPOSE:		Adds a new student to the database
ARGUMENTS:		none
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
bool AddNewStudent()
{
	int i;
	int largest_ID = -1;

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
			g_Students[i].EnterStudentData(++largest_ID);
			break;
		}	
	}

	/*Let's tell the user if they are overflowing the array*/
	if (i == MAX)
	{
		printf("You cannot add any more users to the database!\n");
	}

	return true;
}
/*****************************************************
FUNCTION NAME:	DeleteStudent
PURPOSE:		Deletes a student from the database
ARGUMENTS:		none
RETURN:			void
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void DeleteStudent()
{
	int ID;
	int i;
	int success = false;

	cout << "Please enter the ID of the student to delete: ";
	cin >> ID;

	/*locate the corresponding structure to the ID entered*/
	for (i = 0; i < MAX; i++)
	{
		/*Check for a valid ID*/
		if (ID < 0)
		{
			break;
		}
		if (g_Students[i].ID == ID)
		{
			g_Students[i].ID = -1;
			success = true;

			break;
		}
	}

	if (success == false)
	{
		cout << "That ID does not exist!" << endl;
	}
	else
	{
		cout << "\nstudent with ID = " << ID << " deleted" << endl;
	}
}
/*****************************************************
FUNCTION NAME:	ReportStudents
PURPOSE:		Shows a list of the students in the database
ARGUMENTS:		none
RETURN:			void
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void ReportStudents()
{
	int i;

	/*Print a lovely table of values in the database*/
	cout << "FIRST NAME\tLAST NAME\tID\tFEE" << endl;

	for (i = 0; i < MAX; i++)
	{
		if (g_Students[i].ID != -1)
		{
			g_Students[i].Report();
		}
	}
}
