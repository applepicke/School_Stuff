/******************************************************
FILENAME:			Name.cpp
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
PURPOSE:			Implementation of the Name object
*******************************************************/
#include <iostream>
#include "Name.h"

using namespace std;

/*****************************************************
FUNCTION NAME:	Name 
PURPOSE:		Constructs a name
ARGUMENTS:		Two char pointers representing a first name and a last name
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
Name::Name(char *first_name, char *last_name){
	this->first_name = first_name;
	this->last_name = last_name;
}

/*****************************************************
FUNCTION NAME:	Report
PURPOSE:		Prints the first and last name
ARGUMENTS:		none
RETURN:			void
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void Name::Report(){
	if (first_name != NULL && last_name != NULL)
		cout << first_name << "\t\t" << last_name; 
}

/*****************************************************
FUNCTION NAME:	~Name
PURPOSE:		Deconstructs the Name
ARGUMENTS:		none
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
Name::~Name(){
	//It doesn't matter if the pointers are null, delete will just have no effect.
	delete []first_name;
	delete []last_name;
}