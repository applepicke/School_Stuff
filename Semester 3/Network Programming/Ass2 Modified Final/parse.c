#include "header.h"

int main(void)
{

	char *message = "This is my message to be parsed";
	char *holder = malloc(1000000);
	char *rest = malloc(1000000);

	parse(message, holder, rest);
	
	printf("First: %s\n", holder);
	printf("Rest: %s\n", rest);

	return 0;
}