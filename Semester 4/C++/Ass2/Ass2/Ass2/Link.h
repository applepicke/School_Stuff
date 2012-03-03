/******************************************************
 FILENAME:			Link.h
 VERSION:			1
 STUDENT_NAME:		William Curtis Collins
 STUDENT_NUMBER:	040652633
 COURSE:			CST8219 (C++ Programming)
 LAB_SECTION:		11
 ASSIGNMENT#:		2
 ASSIGNMENT_NAME:	Students Database
 DUE_DATE:			July 14, 2011
 SUBMISSION_DATE:	July 14, 2011
 PROFESSOR_NAME:	Andrew Tyler
 PURPOSE:			A link in the linked list student database
 *******************************************************/
#ifndef LINK_H
#define LINK_H
struct Link
{
	Student* pStudent;
	Link* pNext;		//Link to next
	Link* pPrev;		//Link to previous object
};
#endif
