/******************************************************
 FILENAME:			FullTimeCourse.h
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
 PURPOSE:			Students attend this course full time
 *******************************************************/
#ifndef FULLTIMECOURSE_H
#define FULLTIMECOURSE_H
class FullTimeCourse: public Course
{
	char m_id[30];
public:
	FullTimeCourse(double =0.0, char* = "");
	FullTimeCourse(FullTimeCourse&);
	~FullTimeCourse();
	void Report();
};
#endif