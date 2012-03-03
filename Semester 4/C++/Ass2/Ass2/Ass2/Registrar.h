/******************************************************
 FILENAME:			Registrar.h
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
 PURPOSE:			Handles a database of students
 *******************************************************/
#ifndef REGISTRAR_H
#define REGISTRAR_H
class Registrar
{
	Link* pStudents;
	int Length();	//number of Links
public:
	Registrar(){pStudents = 0;}
	~Registrar();
	bool AddStudent();
	bool DeleteStudent();
	bool ForwardPrintStudents();
	bool ReversePrintStudents();
	bool Largestfee();
	bool Smallestfee();
	//think of the list as an array
	Student& operator[](unsigned int);
};
#endif
