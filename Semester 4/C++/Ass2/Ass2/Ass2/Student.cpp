/******************************************************
 FILENAME:			Student.cpp
 VERSION:			1
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:	040652633
 COURSE:			CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		2
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			July 14, 2011
 SUBMISSION_DATE:	July 14, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			A representation of a student in the database
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include "Student.h"
#include "Link.h"

using namespace std;


/*****************************************************
 FUNCTION NAME:	Student 
 PURPOSE:		Constructs a student
 ARGUMENTS:		fName - The first name of the student
				lName - The last name of the student
				fee - The student's tuition fee
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student::Student(char *fName, char *lName, double fee){
	int len = strlen(fName) + strlen(lName) + 3;
	name = new char[len];
	
	/* Copy over the first name followed by the last name */
	strcpy(name, fName);
	strcat(name, " ");
	strcat(name, lName);
	
	this->fee = fee;
}

/*****************************************************
 FUNCTION NAME:	Student 
 PURPOSE:		Constructs a student
 ARGUMENTS:		name - the student's name
				fee - the studen't tuition fee
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student::Student(char *name, double fee){
	int len = strlen(name);
	this->name = new char[len];

	/*copy the name into new memory*/
	strcpy(this->name, name);

	this->fee = fee;
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Copy constructor for Student
 ARGUMENTS:		student - A reference to a student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student::Student(Student& student): fee(student.fee){
	int len = strlen(student.name);
	name = new char[len];

	/*copy over the name into a new memory space*/
	strcpy(name, student.name);
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Destructor for the Student class
 ARGUMENTS:		student - A reference to a student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student::~Student(){
	delete []name;
}

/*****************************************************
 FUNCTION NAME:	operator=
 PURPOSE:		The equals overloaded operator
 ARGUMENTS:		student - A reference to the r-value student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student& Student::operator=(Student& student){

	/*Release whatever memory name previosuly had, and allocate new memory*/
	int len = strlen(student.name);
	delete []name;
	name = new char[len];

	/*replace name with the new one, and fee with the new fee*/
	strcpy(name, student.name);
	fee = student.fee;

	return *this;
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		determines whether or not a student pays more than another
 ARGUMENTS:		student - A reference to a student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Student::operator>(Student& student){
	return (fee > student.fee);
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		The less than overloaded operator
 ARGUMENTS:		student - A reference to a student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Student::operator<(Student& student){
	return (fee < student.fee);
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Get's the student's names
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
char* Student::GetName(){
	return name;
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Reports the student details
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
void Student::Report(){
	cout<<"name = "<<name<<endl;
	cout<<"fee = "<<fee<<endl<<endl;
}


