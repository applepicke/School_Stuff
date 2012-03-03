/******************************************************
 FILENAME:			Course.h
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
#ifndef COURSE_H
#define COURSE_H
class Course
{
	double m_fee;
public:
	Course(double=0.0);
	Course(Course&);
	virtual~Course();
	bool operator>(Course&);
	bool operator<(Course&);
	virtual void Report()=0;
};
#endif