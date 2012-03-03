/******************************************************
 FILENAME:			FullTimeCourse.cpp
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
 PURPOSE:			Students attend this course, FULL TIME!
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Course.h"
#include "FullTimeCourse.h"

using namespace std;

/*****************************************************
 FUNCTION NAME:	FullTimeCourse
 PURPOSE:		construct a FullTimeCourse with optional fee and id
 ARGUMENTS:		optional fee - The fee for the course
				optional id - The id for the course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
FullTimeCourse::FullTimeCourse(double fee, char* id): Course(fee){
	strcpy(m_id, "FT_");
	strcat(m_id, id);
}

/*****************************************************
 FUNCTION NAME:	FullTimeCourse
 PURPOSE:		copy constructor for a fulltime course
 ARGUMENTS:		origCourse - The course to be copied
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
FullTimeCourse::FullTimeCourse(FullTimeCourse& origCourse):	Course(origCourse){
	for (int i = 0; i < 30; i++){
		m_id[i] = origCourse.m_id[i];
	}
}

/*****************************************************
 FUNCTION NAME:	~FullTimeCourse
 PURPOSE:		destructor for the full time course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
FullTimeCourse::~FullTimeCourse(){
	
}

/*****************************************************
 FUNCTION NAME:	Report
 PURPOSE:		Reports the member data within the full time course
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
void FullTimeCourse::Report(){
	cout << "Full Time Course " << m_id << endl;
	Course::Report();
}