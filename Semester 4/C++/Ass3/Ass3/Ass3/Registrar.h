/******************************************************
 FILENAME:			Registrar.h
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
 PURPOSE:			Handles a database of students
 *******************************************************/
#ifndef REGISTRAR_H
#define REGISTRAR_H
class Registrar
{
	Link* m_pStudents;
	int Length();
public:
	Registrar():m_pStudents(0){};
	~Registrar();
	bool AddStudent();
	bool DeleteStudent();
	bool AddCourse();
	bool ForwardPrintStudents();
	bool ReversePrintStudents();
	bool Largestfee();
	bool Smallestfee();
	Student& operator[](unsigned int);
};
#endif
