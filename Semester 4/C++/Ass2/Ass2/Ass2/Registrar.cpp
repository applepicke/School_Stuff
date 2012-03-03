/******************************************************
 FILENAME:			Registrar.cpp
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
 PURPOSE:			The handler of students within the database
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include "Student.h"
#include "Link.h"
#include "Registrar.h"

using namespace std;

int Registrar::Length(){
	Link *link = pStudents;
	int len;

	for (len = 0; link != NULL ; len++){
		link = link->pNext;
	}

	return len;
}

/*****************************************************
 FUNCTION NAME:	~Registrar 
 PURPOSE:		Destructs a Registrar object
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Registrar::~Registrar(){
	Link *current = pStudents;
	Link *next;
	unsigned int len = Length();

	/*Follow the linked list deleting the Students and Links*/
	for (unsigned int i = 0; i < len; i++, current = next){
		delete current->pStudent;
		next = current->pNext;
		delete current;
	}
}

/*****************************************************
 FUNCTION NAME:	AddStudent 
 PURPOSE:		Prompts the user for student information
				and adds the student to the database.
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::AddStudent(){
	char fName[100];
	char lName[100];
	float fee;

	cout<<"Adding a Student"<<endl;

	/* Get the first name*/
	cout<<"Please enter the Student's first name: ";
	cin>>fName;

	/*Get the last name*/
	cout<<"Please enter the Student's last name: ";
	cin>>lName;

	/*Get the fee*/
	do {
		cout<<"Please enter the Student's fee: ";
		cin>>fee;
		if (cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			fee = -1;
		}
	} while (fee < 0);

	/*Add A link for the student*/
	Link *newLink = new Link();
	newLink->pStudent = new Student(fName, lName, fee);

	/*If we don't have any students yet*/
	if (pStudents == NULL){
		pStudents = newLink;
		return true;
	}

	/*Add the new student to the beginning of the list*/
	newLink->pNext = pStudents;	
	pStudents->pPrev = newLink;
	pStudents = newLink;

	return true;
}

/*****************************************************
 FUNCTION NAME:	DeleteStudent
 PURPOSE:		Prompts the user to delete a student from the database
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::DeleteStudent(){
	char fName[100];
	char lName[100];
	char *tempName;

	cout << "Please enter Student's full name(firstName lastName) to be deleted: ";
	cin >> fName >> lName;

	tempName = new char[strlen(fName) + strlen(lName) + 2];
	strcpy(tempName, fName);
	strcat(tempName, " ");
	strcat(tempName, lName);

	/*Search the linked list for the name*/
	Link *tempLink = pStudents;
	while (tempLink != NULL){
		if (!strcmp(tempLink->pStudent->GetName(), tempName)){
			cout << "Student found" << endl;

			/*We found the student, now remove any connection to it*/
			if (tempLink->pNext != NULL){
				tempLink->pNext->pPrev = tempLink->pPrev;
			}
			if (tempLink->pPrev != NULL){
				tempLink->pPrev->pNext = tempLink->pNext;
			}

			/*If the one we are deleting is pStudents then we need to do somethign special*/
			if (tempLink == pStudents){
				pStudents = pStudents->pNext;
			}

			/*Now finally delete it*/
			delete tempLink->pStudent;
			delete tempLink;

			cout << "Student " << tempName << " deleted" << endl;

			delete []tempName;
			return true;
		}
		tempLink = tempLink->pNext;
	}
	delete []tempName;

	cout << "Could not find student with that name" << endl;
	
	return false;
}

/*****************************************************
 FUNCTION NAME:	ForwardPrintStudents
 PURPOSE:		Prints the students in the database 
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::ForwardPrintStudents(){
	unsigned int len = Length();

	/* Print out the students */
	cout << "FORWARD PRINTING Students" << endl << endl;
	for (unsigned int i = 0; i < len; i++) {
		cout << "Student " << i << endl;
		(*this)[i].Report();
	}
	return true;
}

/*****************************************************
 FUNCTION NAME:	ReversePrintStudents
 PURPOSE:		Prints the students in the database in reverse
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::ReversePrintStudents(){
	unsigned int len = Length();

	/*Print students in reverse*/
	cout << "REVERSE PRINTING Students" << endl << endl;
	for (unsigned int i = len - 1; i < len; i--){
		cout << "Student " << i << endl;
		(*this)[i].Report();
	}

	return true;
}

/*****************************************************
 FUNCTION NAME:	Largestfee
 PURPOSE:		Determines the student with the highest fee
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::Largestfee(){
	unsigned int len = Length();
	Student *largestStudent = pStudents->pStudent;
	
	/*Find the largest student (Not by weight)*/
	for (unsigned int i = 0; i < len; i++){
		if ((*this)[i] > *largestStudent) {
			largestStudent = &(*this)[i];
		}
	}

	/*Print out the largest student*/
	cout << "Student with the largest fee is: " << endl << endl;
	largestStudent->Report();

	return true;
}

/*****************************************************
 FUNCTION NAME:	Smallestfee
 PURPOSE:		Determines the student with the lowest fee
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::Smallestfee(){
	unsigned int len = Length();
	Student *smallestStudent = pStudents->pStudent;
	
	/*Find the largest student (Not by weight)*/
	for (unsigned int i = 0; i < len; i++){
		if ((*this)[i] < *smallestStudent) {
			smallestStudent = &(*this)[i];
		}
	}

	/*Print out the largest student*/
	cout << "Student with the smallest fee is: " << endl << endl;
	smallestStudent->Report();

	return true;
}

/*****************************************************
 FUNCTION NAME:	operator[]
 PURPOSE:		Accesses the linked list with array notation
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student& Registrar::operator[](unsigned int location){
	Link *current = pStudents;

	/*Let's cycle through the linked list*/
	for (unsigned int i = 0; i < location && current != NULL; i++){
		current = current->pNext;
	}

	return *current->pStudent;
}