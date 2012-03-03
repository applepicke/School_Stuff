/******************************************************
 FILENAME:			Student.h
 VERSION:			1.5
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:		040652633
 COURSE:				CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		3
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			August 11, 2011
 SUBMISSION_DATE:	August 11, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			A representation of a student in the database
 *******************************************************/
#ifndef STUDENT_H
#define STUDENT_H
class Student
{
	char* m_name;
	unsigned int m_numCourses;
	Course** m_ppCourses;
public:
	Student():m_name(0),m_ppCourses(0), m_numCourses(0){};
	~Student();
	char*& GetName();
	unsigned int& GetNumCourses();
	Course**& GetppCourses();
	void Report();	
};
#endif