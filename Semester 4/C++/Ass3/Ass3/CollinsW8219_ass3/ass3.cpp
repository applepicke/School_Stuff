#include <iostream>
#include "Course.h"
#include "PartTimeCourse.h"
#include "FullTimeCourse.h"
#include "Student.h"
#include "Link.h"
#include "Registrar.h"

using namespace std;

int main()
{
	char response;
	Registrar Registrar;

	while(true){
		cout<<endl<<"Please select an option:"<<endl;
		cout<<"1. Add a Student"<<endl;
		cout<<"2. Delete a Student"<<endl;
		cout<<"3. Add a Course to a Student"<<endl;
		cout<<"4. Print out Students and their courses"<<endl;
		cout<<"5. Print out Students and their courses in reverse order"<<endl;
		cout<<"6. Report the Course with the largest fee"<<endl;
		cout<<"7. Report the Course with the smallest fee"<<endl;
		cout<<"q. Quit"<<endl;
		cout<<"CHOICE: ";
		cin>>response;

		switch(response)
		{
			case '1':
				if(!Registrar.AddStudent())
					exit(1);
				break;
			case '2':
				Registrar.DeleteStudent();
				break;
			case '3':
				Registrar.AddCourse();
				break;
			case '4':
				Registrar.ForwardPrintStudents();
				break;
			case '5':
				Registrar.ReversePrintStudents();
				break;
			case '6':
				Registrar.Largestfee();
				break;
			case '7':
				Registrar.Smallestfee();
				break;
			case 'q':
				return 0;
			default:cout<<"Please enter a valid option"<<endl;
		}
		cout<<endl;
	}

	return 0;
}