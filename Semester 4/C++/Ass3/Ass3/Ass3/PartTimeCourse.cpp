/******************************************************
 FILENAME:			PartTimeCourse.cpp
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
 PURPOSE:			Students attend this course, PART TIME!
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Course.h"
#include "PartTimeCourse.h"

using namespace std;

/*****************************************************
 FUNCTION NAME:	PartTimeCourse
 PURPOSE:		construct a PartTimeCourse with optional fee and id
 ARGUMENTS:		optional fee - The fee for the course
				optional id - The id for the course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
PartTimeCourse::PartTimeCourse(double fee, char* id): Course(fee){
	strcpy(m_id, "PT_");
	strcat(m_id, id);
}

/*****************************************************
 FUNCTION NAME:	PartTimeCourse
 PURPOSE:		construct a PartTimeCourse from an existing one
 ARGUMENTS:		oldCourse - the course to copy
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
PartTimeCourse::PartTimeCourse(PartTimeCourse& oldCourse): Course(oldCourse){
	strcpy(m_id, oldCourse.m_id);
}

/*****************************************************
 FUNCTION NAME:	~PartTimeCourse
 PURPOSE:		destructor for a parttimecourse
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
PartTimeCourse::~PartTimeCourse(){
	
}

/*****************************************************
 FUNCTION NAME:	Report
 PURPOSE:		Reports the member items of the parttime course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
void PartTimeCourse::Report(){
	cout << "Part Time Course " << m_id << endl;
	Course::Report();
}