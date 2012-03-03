/******************************************************
 FILENAME:			Course.cpp
 VERSION:			1.0
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:	040652633
 COURSE:			CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		3
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			August 11, 2011
 SUBMISSION_DATE:	August 11, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			Students attend this course
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include "Course.h"

using namespace std;

/*****************************************************
 FUNCTION NAME:	Course
 PURPOSE:		Destructor for the Course class
 ARGUMENTS:		optional fee - The fee for the course, defaults to
				zero if not specified
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Course::Course(double fee){
	m_fee = fee;
}

/*****************************************************
 FUNCTION NAME:	Course
 PURPOSE:		Course copy constructor
 ARGUMENTS:		origCourse - The course you want to copy
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Course::Course(Course& origCourse){
	m_fee = origCourse.m_fee;
}

/*****************************************************
 FUNCTION NAME:	~Course
 PURPOSE:		The destructor for the Course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Course::~Course(){
}

/*****************************************************
 FUNCTION NAME:	operator>
 PURPOSE:		Overloaded operator used for greater than comparison
 ARGUMENTS:		rCourse - The course on the right side of the operator
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Course::operator>(Course& rCourse){
	return (m_fee > rCourse.m_fee);
}

/*****************************************************
 FUNCTION NAME:	operator<
 PURPOSE:		Overloaded operator used for less than comparison
 ARGUMENTS:		rCourse - The course on the right side of the operator
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Course::operator<(Course& rCourse){
	return (m_fee < rCourse.m_fee);
}

/*****************************************************
 FUNCTION NAME:	Report
 PURPOSE:		Reports the fee of the course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
void Course::Report(){
	cout << "fee = " << m_fee << endl << endl;
}