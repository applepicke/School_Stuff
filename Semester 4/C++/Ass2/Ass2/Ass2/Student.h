/******************************************************
 FILENAME:			Student.h
 VERSION:			1
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:		040652633
 COURSE:				CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		2
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			July 14, 2011
 SUBMISSION_DATE:	July 14, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			A representation of a student in the database
 *******************************************************/
#ifndef STUDENT_H
#define STUDENT_H
class Student
{
	char* name; //full name
	double fee;
public:
	Student():name(0), fee(0){}
	Student(char*, char*, double);
	Student(char*, double);
	Student(Student&);
	~Student();
	
	Student& operator=(Student&);
	bool operator>(Student&);
	bool operator<(Student&);
	char* GetName();
	void Report();
	
};
#endif