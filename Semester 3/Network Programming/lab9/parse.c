#include "header.h"

int main(void)
{

	char message[BUF_SIZE] = "This is my message to be parsed";
	char holder[NAME_SIZE];
	char rest[BUF_SIZE];

	parse(message, holder, rest);
	
	printf("First: %s\n", holder);
	printf("Rest: %s\n", rest);

	return 0;
}