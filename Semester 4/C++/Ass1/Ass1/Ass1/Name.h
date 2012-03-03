/******************************************************
FILENAME:			Name.h
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
PURPOSE:			Contains the declaration of the Name structure
*******************************************************/
//Name.h
#ifndef NAME_H
#define NAME_H

struct Name
{
	char* first_name;
	char* last_name;
	Name(char*, char*);
	~Name();
	void Report();
};

#endif