/******************************************************
FILENAME:			Student.cpp
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
PURPOSE:			Implementation of the Student Object
*******************************************************/
#include <iostream>
#include <stdio.h>
#include "Name.h"
#include "Student.h"

using namespace std;

/*****************************************************
FUNCTION NAME:	Student
PURPOSE:		Initializes the student
ARGUMENTS:		none
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
Student::Student(){
	pName = NULL;
	ID = -1;
	Fee = 0;
}

/*****************************************************
FUNCTION NAME:	EnterStudentData
PURPOSE:		Prompts the user for the student information
ARGUMENTS:		An integer that specifies the student ID
RETURN:			Returns success or failure
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
bool Student::EnterStudentData(int ID){

	//Use temporary storage for the names
	char *temp = new char[100];
	char *fName;
	char *lName;
	
	//Make sure we don't have any dynamically allocated memory already in use
	if (pName != NULL){
		delete pName;
	}

	//Get the first name of the student
	cout << "Please enter the new student first name (e.g. Barack): " << endl;
	cin >> temp;
	fName = new char[strlen(temp) + 1];
	strcpy(fName, temp);

	//Get the last name of the student
	cout << "Please enter the new student last name (e.g. Obama): " << endl;
	cin >> temp;
	lName = new char[strlen(temp) + 1];
	strcpy(lName, temp);

	//Create the Name with the new first and last names
	pName = new Name(fName, lName);

	//Get the student fee
	do {
		Fee = -1;
		cout << "Please enter the fee to be paid (e.g. $1000): " << endl;
		cin >> Fee;
	
		if (cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			Fee = -1;
		}

	} while (Fee < 0);

	//Set Student ID
	this->ID = ID;
	
	//Release the memory of the temp variable
	delete []temp;

	return true;
}

/*****************************************************
FUNCTION NAME:	Report
PURPOSE:		Shows a list of the students in the database
ARGUMENTS:		none
RETURN:			void
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void Student::Report(){
	//Print the student information
	pName->Report();
	cout << "\t\t" << ID << "\t" << Fee << endl;
}

/*****************************************************
FUNCTION NAME:	~Student
PURPOSE:		Deconstructs the Student
ARGUMENTS:		none
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
Student::~Student(){
	//Deleting a null pointer has no effect, so no point in checking
	delete pName;
}

