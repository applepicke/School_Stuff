/******************************************************
 FILENAME:			Link.h
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
 PURPOSE:			A link in the linked list student database
 *******************************************************/
#ifndef LINK_H
#define LINK_H
struct Link
{
	Student m_Student;
	Link* m_pNext;
	Link* m_pPrev;
};
#endif
