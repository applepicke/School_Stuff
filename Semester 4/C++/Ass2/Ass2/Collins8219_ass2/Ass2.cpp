#include <iostream>
#include "Student.h"
#include "Link.h"
#include "Registrar.h"

using namespace std;

int main()
{
	char response ;
	Registrar registrar;
	while(1){
		cout<<endl<<"Please select an option:"<<endl;
		cout<<"1. Add a Student"<<endl;
		cout<<"2. Delete a Student"<<endl;
		cout<<"3. Print out Students"<<endl;
		cout<<"4. Print out Students in reverse order"<<endl;
		cout<<"5. Report the Student with the largest fee"<<endl;
		cout<<"6. Report the Student with the smallest fee"<<endl;
		cout<<"q. Quit"<<endl;
		cout<<"CHOICE: ";
		cin>>response;
		switch (response) {
			case '1':
				registrar.AddStudent();
				break;
			case '2':
				registrar.DeleteStudent();
				break;
			case '3':
				registrar.ForwardPrintStudents();
				break;
			case '4':
				registrar.ReversePrintStudents();
				break;
			case '5':
				registrar.Largestfee();
				break;
			case '6':
				registrar.Smallestfee();
				break;
			case 'q':
				return 0;
			default: cout<<"Please enter a valid option"<<endl;
		}
		cout<<endl;
	}
	return 0;
}