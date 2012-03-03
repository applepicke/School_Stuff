/******************************************************
 FILENAME:			Registrar.cpp
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
 PURPOSE:			The handler of students within the database
 *******************************************************/
#include <iostream>
#include <stdio.h>
#include "Course.h"
#include "FullTimeCourse.h"
#include "PartTimeCourse.h"
#include "Student.h"
#include "Link.h"
#include "Registrar.h"

using namespace std;

int Registrar::Length(){
	Link *link = m_pStudents;
	int len;

	for (len = 0; link != NULL ; len++){
		link = link->m_pNext;
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
	Link *current = m_pStudents;
	Link *next;
	unsigned int len = Length();

	/*Follow the linked list deleting the Students and Links*/
	for (unsigned int i = 0; i < len; i++, current = next){
		next = current->m_pNext;
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
	char* name;

	cout<<"ADDING A Student"<<endl;

	/* Get the first name*/
	cout<<"Please enter the Student first name: ";
	cin>>fName;

	/*Get the last name*/
	cout<<"Please enter the Student last name: ";
	cin>>lName;

	/*Compress the names into a single packed array*/
	name = new char[strlen(fName) + strlen(lName) + 2];
	strcpy(name, fName);
	strcat(name, " ");
	strcat(name, lName);

	/*Add A link for the student*/
	Link *newLink = new Link();
	newLink->m_Student.GetName() = name;
	newLink->m_pNext = NULL;
	newLink->m_pPrev = NULL;

	/*If we don't have any students yet*/
	if (m_pStudents == NULL){
		m_pStudents = newLink;
		return true;
	}

	/*Add the new student to the beginning of the list*/
	newLink->m_pNext = m_pStudents;	
	m_pStudents->m_pPrev = newLink;
	m_pStudents = newLink;

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
	Link *tempLink = m_pStudents;
	while (tempLink != NULL){
		if (!strcmp(tempLink->m_Student.GetName(), tempName)){
			cout << "Student found" << endl;

			/*We found the student, now remove any connection to it*/
			if (tempLink->m_pNext != NULL){
				tempLink->m_pNext->m_pPrev = tempLink->m_pPrev;
			}
			if (tempLink->m_pPrev != NULL){
				tempLink->m_pPrev->m_pNext = tempLink->m_pNext;
			}

			/*If the one we are deleting is pStudents then we need to do somethign special*/
			if (tempLink == m_pStudents){
				m_pStudents = m_pStudents->m_pNext;
			}

			/*Now finally delete it*/
			delete tempLink;

			cout << "Student " << tempName << " deleted" << endl;

			delete []tempName;
			return true;
		}
		tempLink = tempLink->m_pNext;
	}
	delete []tempName;

	cout << "Could not find student with that name" << endl;
	
	return false;
}

/*****************************************************
 FUNCTION NAME:	AddCourse
 PURPOSE:		Adds a course to a particular student
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
bool Registrar::AddCourse(){
	char fName[100];
	char lName[100];
	char *tempName;

	double fee;
	int courseType;
	char course_id[15];

	Course* newCourse;
	Course** newCourseArray;

	/*Get the name of the student to add a course to*/
	cout << endl << "Please enter the name of the Student to add an Course to :";
	cin >> fName >> lName;

	tempName = new char[strlen(fName) + strlen(lName) + 2];
	strcpy(tempName, fName);
	strcat(tempName, " ");
	strcat(tempName, lName);

	/*Now search the linked list for the student*/
	Link *tempLink = m_pStudents;

	while (tempLink != NULL){
		/*We found the student*/
		if (!strcmp(tempLink->m_Student.GetName(), tempName)){
			cout << endl << "Student found" << endl;

			/*Now that we have found the student, we need to add a course to it*/
			cout << endl << "Please enter the fee: ";
			cin >> fee;

			/*Now get the type of course*/
			cout << endl << "Please enter the type of Course (Full Time = 1; Part Time = 2): ";
			cin >> courseType;	

			/*Now the name of the course*/
			cout << "Please enter the Part Time Course ID ( < 16 characters): ";
			cin >> course_id;

			/*Determine what type of course we will add*/
			if (courseType == 1){
				newCourse = new FullTimeCourse(fee, course_id);
			}
			else if (courseType == 2){
				newCourse = new PartTimeCourse(fee, course_id);
			}
			else {
				return false;
			}

			/*We need to make a new pointer that can hold the new number of courses*/
			int numCourses = ++tempLink->m_Student.GetNumCourses();		
			newCourseArray = new Course*[numCourses];

			for (int i = 0; i < numCourses - 1; i++){
				newCourseArray[i] = tempLink->m_Student.GetppCourses()[i];
			}
			delete tempLink->m_Student.GetppCourses();
			tempLink->m_Student.GetppCourses() = newCourseArray;

			/*Now we can finally add the course*/
			tempLink->m_Student.GetppCourses()[numCourses - 1] = newCourse;
			
			delete []tempName;

			return true;
		}

		tempLink = tempLink->m_pNext;

	}

	/*If the student doesn't exist, let's tell the user*/
	cout << "Student does not exist!" << endl;

	return true;
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
	cout << "FORWARD PRINTING STUDENTS" << endl << endl;
	for (unsigned int i = 0; i < len; i++) {

		/*Print out the student*/
		cout << "Student " << i << endl;
		(*this)[i].Report();

		/*Now print out all the courses the student is in*/
		for (unsigned int j = 0; j < (*this)[i].GetNumCourses(); j++){
			(*this)[i].GetppCourses()[j]->Report();
		}
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
	cout << "REVERSE PRINTING STUDENTS" << endl << endl;
	for (unsigned int i = len - 1; i < len; i--){

		/*Print out the student*/
		cout << "Student " << i << endl;
		(*this)[i].Report();

		/*Now print all the courses the student is in*/
		for (unsigned int j = 0; j < (*this)[i].GetNumCourses(); j++){
			(*this)[i].GetppCourses()[j]->Report();
		}
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
	Student *largestStudent = &m_pStudents->m_Student;
	Course *largestCourse = NULL;
	
	/*Loop through the students*/
	for (unsigned int i = 0; i < len; i++){
	
		/*Loop through the students courses*/
		for (unsigned int j = 0; j < (*this)[i].GetNumCourses(); j++){
			
			/*copmpare courses, if we just started, make sure to assign a largest*/
			if (largestCourse == NULL || *( (*this)[i].GetppCourses()[j] ) > *largestCourse){
				largestStudent = &(*this)[i];
				largestCourse = (*this)[i].GetppCourses()[j];
			}
		}
	}

	/*Print out the largest student and course*/
	cout << endl << "Course with the largest fee is: " << endl;
	cout << largestStudent->GetName() << endl;
	largestCourse->Report();

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
	Student *smallestStudent = &(m_pStudents->m_Student);
	Course *smallestCourse = NULL;
	
	/*Loop through the students*/
	for (unsigned int i = 0; i < len; i++){

		/*Loop through the courses belonging to each student*/
		for (unsigned int j = 0; j < (*this)[i].GetNumCourses(); j++){

			/*Compare courses. If we don't have a smallest yet, then make this one the smallest*/
			if (smallestCourse == NULL || *( (*this)[i].GetppCourses()[j] ) < *smallestCourse) {
				smallestStudent = &(*this)[i];
				smallestCourse = (*this)[i].GetppCourses()[j];
			}
		}
	}

	/*Print out the smallest student and course*/
	cout << endl << "Course with the smallest fee is: " << endl;
	cout << smallestStudent->GetName() << endl;
	smallestCourse->Report();

	return true;
}

/*****************************************************
 FUNCTION NAME:	operator[]
 PURPOSE:		Accesses the linked list with array notation
 VERSION:		1.0
 AUTHOR:		William Collins
 *****************************************************/
Student& Registrar::operator[](unsigned int location){
	Link *current = m_pStudents;

	/*Let's cycle through the linked list*/
	for (unsigned int i = 0; i < location && current != NULL; i++){
		current = current->m_pNext;
	}

	return current->m_Student;
}