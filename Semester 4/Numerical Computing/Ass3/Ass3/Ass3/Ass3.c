/******************************************************
FILENAME:			ass3.c
VERSION:			1
STUDENT_NAME:		William Curtis Collins
STUDENT_NUMBER:		040652633
COURSE:				CST8233 (Numerical Computing)
LAB_SECTION:		310
ASSIGNMENT#:		3
ASSIGNMENT_NAME:	Least Squares Fit
DUE_DATE:			August 9, 2011
SUBMISSION_DATE:	August 9, 2011
PROFESSOR_NAME:		Andrew Tyler
PURPOSE:			To simulate a martian lander, using integration
					to calulate the fall
*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <conio.h>

#define MAX_INPUT 10			/*The maximum input characters*/
#define START_HEIGHT 1000.0		/*The starting height of the lander*/
#define NUMBER_OF_LEADERS 10	/*size of the leaderboard*/

/*User Information structure: A Linked List*/
struct User{
	char *name;
	double speed;
	int minutes;
	int seconds;
	int milliseconds;
	struct User *next;
	struct User *prev;
};

typedef struct User User;

/*Function Prototypes*/
void simulate(User*);
void add_to_leaderboard(User* user);
void print_results(char);
void clean_up();

/*Global array of users holding the leaders*/
User *leaderboard = NULL;

int main()
{
	char *start = malloc(sizeof(char) * MAX_INPUT);
	User* currentUser;

	/*Infinite loop is exited when user decides to exit*/
	while (1){

		/*Confirm simulation*/
		printf("Type \"start\" to begin the simulation, or press \"quit\" to quit: ");
		if (!scanf("%s", start)){
			while (fgetc(stdin) != '\n');	/*flush the rest of the input buffer*/
		}

		/*start the simulation, or quit the program*/
		if (!strncmp(start, "start", MAX_INPUT)){
				
			/*Set up the User structure*/
			currentUser = malloc(sizeof(User));
			currentUser->name = malloc(sizeof(char) * MAX_INPUT);
			currentUser->next = NULL;
			currentUser->prev = NULL;

			system("cls");

			/*Obtain User information*/
			printf("Please enter your username: ");
			if (!scanf("%s", currentUser->name)){
				while (fgetc(stdin) != '\n');	/*flush the rest of the input buffer*/
			}
			
			simulate(currentUser);
			print_results('p');

		}
		if (!strncmp(start, "quit", MAX_INPUT)){
			break;
		}
	}
	
	/*Print the results to a file*/
	print_results('f');

	/*Clean up the leaderboard*/
	clean_up();
	free(start);

	return 0;
}

/*****************************************************
FUNCTION NAME:	simulate
PURPOSE:		Performs the lander simulation with a user
ARGUMENTS:		currentUser - The user to run the simulation with
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void simulate(User *currentUser){

	double g = 4.0, c = 12.5, m = 68.1, a = 8.3, b = 2.2, vmax = 46;
	double v = 0.0, t = 0.0, s = START_HEIGHT;	/*speed, time, and distance*/
	double B = 0, reserve = 100.0;				/*Burn and the burn reserve tank*/
	int minute = 0, second = 0;					/*timer values*/
	char boost_char = 0;						/*Will hold an input character to check for boost*/
	clock_t elapsed = 0, time;


	time = clock();

	/*Continue the simulation until the lander reaches the ground*/
	while (1){

		/*Special v used for the power function. A negative will cause errors*/
		double vs = v;	
		if (vs < 0.0) vs *= -1.0;

		/*Calculate the new time interval*/
		t = clock() - time;
		time += (clock_t) t;

		/*Now we need a working timer*/
		elapsed += (clock_t) t;
		if (elapsed >= 1000) { 
			elapsed = 0;
			second++;
		}
		if (second >= 60){
			second = 0;
			minute++;
		}

		/*Make sure time is in seconds*/
		t /= 1000;

		/*Calculate the speed and distance of descent*/
		v = v + (g - c/m*(v + a* pow(vs/vmax, b)) - B)*t;
		s = (s - v * t);

		/*Check for a change in the booster*/
		if (_kbhit()) {
			boost_char = (char) _getch();
		}
		if (boost_char == 'w'){
			B++;
		}
		if (boost_char == 'e' && B > 0){
			B--;
		}
		boost_char = 0;

		/*handle the decrease in reserve*/
		reserve = reserve - B * t;
		if (reserve <= 0){
			reserve = 0;
			B = 0;
		}

		/*Print out all relevant values*/
		printf("Burn = %1.0lf  Burn Reserve = %.3lf\n", B, reserve);
		printf("Minutes = %d  Seconds = %d  Milliseconds = %.d\n", minute, second, elapsed);
		printf("Speed = %g m/s\n", v);
		printf("Height = %g metres\n", s);

		/*The lander has hit the ground*/
		if (s <= 0) {
			break;
		}

		system("cls");
	}

	/*The lander has landed*/
	if (v > 1.0) {
		printf("You have crashed!\n");
	}
	else {
		printf("You have landed safely!\n");
	}
	
	system("pause");

	/*Assign the user stats*/
	currentUser->speed = v;
	currentUser->minutes = minute;
	currentUser->seconds = second;
	currentUser->milliseconds = elapsed;

	add_to_leaderboard(currentUser);
}

/*****************************************************
FUNCTION NAME:	print_results
PURPOSE:		Prints the user results to the screen or to a file
ARGUMENTS:		option - specifies whether to print to screen or a file
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void print_results(char option){
	int i = 0;
	User *user = leaderboard;
	char output_file[] = "ml_leaderboard";
	FILE *output;

	if (option == 'p'){
		output = stdout;
	}
	else if (option == 'f'){
		output = fopen(output_file, "w");
		if (output == NULL){
			printf("Cannot save results!\n");
			return;
		}
	}
	else { return; };

	/*Clear the screen and print the leaderboard header*/
	system("cls");
	fprintf(output, "**************************************************\n");
	fprintf(output, "**                  LEADERBOARD                 **\n");
	fprintf(output, "**************************************************\n");

	/*Loop through each entry in the leaderboard*/
	while (user != NULL && i < NUMBER_OF_LEADERS){
		fprintf(output, " %d. %s: Speed = %.4lf  Time = %d:%d:%d\n", i+1, user->name, user->speed, user->minutes, user->seconds, user->milliseconds); 
		i++;
		user = user->next;
	}
	fprintf(output, "**************************************************\n");

	/*If we are printing to a file no need to wait for the user*/
	if (option == 'f') {
		printf("File has been saved!\n");
		system("pause");
		fclose(output);
		return;
	}

	system("pause");
	system("cls");
}

/*****************************************************
FUNCTION NAME:	add_to_leaderboard
PURPOSE:		Adds a user to the leaderboard
ARGUMENTS:		user - The user to add to the leaderboard
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void add_to_leaderboard(User* user){
	User *leader = leaderboard;
	int total_user_time;
	int total_leader_time;
	
	/*First on the board is special*/
	if (leaderboard == NULL){
		leaderboard = user;
		return;
	}

	/*Search the leaderboard for where to place the new entry*/
	while (leader != NULL){

		/*Find out the total time in milliseconds*/
		total_user_time = (user->minutes * 60000) + (user->seconds * 60) + user->milliseconds;
		total_leader_time = (leader->minutes * 60000) + (leader->seconds * 60) + leader->milliseconds;

		/*A smaller speed is better, but if the speed is equal, the time must be less*/
		if (user->speed < leader->speed || (user->speed == leader->speed && total_user_time < total_leader_time)){

			/*The user belongs first on the leaderboard*/
			if (leader == leaderboard) {
				leaderboard = user;
			}
			/*The user belongs in the middle*/
			else {
				leader->prev->next = user; 
			}

			user->next = leader;
			user->prev =  leader->prev;
			leader->prev = user;	
			return;
		}

		/*No more in the leaderboard, so add to the end*/
		if (leader->next == NULL){
			leader->next = user;
			user->prev = leader;
			return;
		}
		leader = leader->next;		
	}
}

/*****************************************************
FUNCTION NAME:	clean_up
PURPOSE:		frees up the memory allocated by the leaderboard
VERSION:		1.0
AUTHOR:			William Collins
*****************************************************/
void clean_up(){
	User *leader = leaderboard;
	User *temp;

	/*Nothing to delete*/
	if (leader == NULL) {
		return;
	}

	/*Safely Free up the leaderboard elements*/
	while (leader != NULL){

		temp = leader;
		leader = leader->next;

		/*Free the memory occupied by the user*/
		free(temp->name);
		free(temp);
			
	}
}