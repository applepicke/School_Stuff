/******************************************************
 FILENAME:			Student.cpp
 VERSION:			1.5
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:	040652633
 COURSE:			CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		3
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			August 11, 2011
 SUBMISSION_DATE:	August 11, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			A representation of a student in the database
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include "Course.h"
#include "Student.h"
#include "Link.h"

using namespace std;

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Destructor for the Student class
 ARGUMENTS:		student - A reference to a student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student::~Student(){
	delete []m_name;
	for (unsigned int i = 0; i < m_numCourses; i++){
		delete m_ppCourses[i];
	}
	delete m_ppCourses;
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Get's the student's names
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
char*& Student::GetName(){
	return m_name;
}

/*****************************************************
 FUNCTION NAME:	GetNumCourses
 PURPOSE:		Returns a reference to an unsigned int
				that is the number of courses the student is in
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
unsigned int& Student::GetNumCourses(){
	return m_numCourses;
}

/*****************************************************
 FUNCTION NAME:	GetppCourses
 PURPOSE:		Returns a reference to a pointer that points to 
				an array of pointers to Courses
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Course**& Student::GetppCourses(){
	return m_ppCourses;
}

/*****************************************************
 FUNCTION NAME:	Student
 PURPOSE:		Reports the student details
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
void Student::Report(){
	cout<<"name = "<<m_name<<endl<<endl;
}


