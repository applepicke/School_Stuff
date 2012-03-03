/******************************************************
FILENAME:			Student.h
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
PURPOSE:			Contains the declaration of the Student Object
*******************************************************/
#ifndef STUDENT_H
#define STUDENT_H

class Student
{
	Name* pName;
	float Fee;
public:
	int ID;
	Student();
	~Student();
	bool EnterStudentData(int);
	void Report();
};

#endif