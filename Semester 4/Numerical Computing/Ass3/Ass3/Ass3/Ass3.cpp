#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_INPUT 10			/*The maximum input characters*/
#define START_HEIGHT 100.0		/*The starting height of the lander*/
#define NUMBER_OF_LEADERS 10	/*size of the leaderboard*/

/*User Information structure: A Linked List*/
struct User{
	char *name;
	double speed;
	int minutes;
	int seconds;
	int milliseconds;
	User *next;
	User *prev;
};

/*Function Prototypes*/
void simulate(User*);
void add_to_leaderboard(User* user);
void save_results();
void print_results();
void safe_free(void*);

/*Global array of users holding the leaders*/
User *leaderboard = NULL;

int main()
{
	char *start = new char[MAX_INPUT];

	/*Infinite loop that is broken when the user wishes to exit*/
	printf("MARTIAN LANDER SIMULATION\n");
	printf("*************************\n");

	while (1){
		User* currentUser = new User;
		currentUser->name = new char[MAX_INPUT];
		currentUser->next = NULL;
		currentUser->prev = NULL;

		/*Confirm simulation*/
		printf("Type \"start\" to begin the simulation, or press \"quit\" to quit: ");
		scanf("%s", start);

		/*start the simulation, or quit the program*/
		if (!strncmp(start, "start", MAX_INPUT)){
				
			/*Obtain User information*/
			printf("Please enter your username: ");
			scanf("%s", currentUser->name);
			
			simulate(currentUser);
			print_results();

		}
		if (!strncmp(start, "quit", MAX_INPUT)){
			break;
		}

		
	}

	/*Safely Free up the leaderboard elements*/
	while (leaderboard != NULL){

		/*we are at the end of the list*/
		if (leaderboard->next == NULL){
			break;
		}
		delete []leaderboard->name;

		if (leaderboard->prev != NULL) {
			delete leaderboard->prev;
		}
	}

	delete []start;
	return 0;

}

void simulate(User *currentUser){

	double g = 4.0, c = 12.5, m = 68.1, a = 8.3, b = 2.2, vmax = 46;
	double v = 0.0, t = 0.0, s = START_HEIGHT;	/*speed, time, and distance*/
	double B = 0, reserve = 100.0;				/*Burn and the burn reserve tank*/
	int minute = 0, second = 0;			/*timer values*/
	clock_t elapsed = 0, time;

	time = clock();

	/*Continue the simulation until the lander reaches the ground*/
	while (1){
	
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

		/*Make sure we don't do any division by zero*/
		if (t == 0.00) { continue; }

		/*Make sure time is in seconds*/
		t /= 1000;

		/*Calculate the speed and distance of descent*/
		v = v + (g - c/m*(v + a* pow(v/vmax, b)) - B)*t;
		s = (s - v * t);

		/*Print out all relevant values*/
		printf("Burn = %.3lf  Burn Reserve = %.3lf\n", B, reserve);
		printf("Minutes = %d  Seconds = %d  Milliseconds = %.d\n", minute, second, elapsed);
		printf("Speed = %.3lf m/s\n", v);
		printf("Height = %.3lf metres\n", s);

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
	
	/*Assign the user stats*/
	currentUser->speed = v;
	currentUser->minutes = minute;
	currentUser->seconds = second;
	currentUser->milliseconds = elapsed;

	add_to_leaderboard(currentUser);
}

void print_results(){
	int i = 0;
	User *user = leaderboard;

	system("cls");
	printf("   LEADERBOARD\n");
	printf("********************\n\n");

	while (user != NULL && i < NUMBER_OF_LEADERS){
		printf("%d. %s: Speed = %.2lf  Time = %d:%d:%d\n", i+1, user->name, user->speed, user->minutes, user->seconds, user->milliseconds); 
		i++;
		user = user->next;
	}
}

void save_results(){

}

void add_to_leaderboard(User* user){
	User *leader = leaderboard;
	
	/*First on the board is special*/
	if (leaderboard == NULL){
		leaderboard = user;
	}

	/*Search the leaderboard for where to place the new entry*/
	while (leader != NULL){

		/*This user is better, so squeeze him/her in*/
		if (user->speed < leader->speed && user->minutes < leader->minutes && user->seconds < leader->seconds && user->milliseconds < leader->milliseconds){
			user->next = leader;
			user->prev =  leader->prev;
			leader->prev = user;	
			return;
		}

		leaderboard = leaderboard->next;		
	}
}
