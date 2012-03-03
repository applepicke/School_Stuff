#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int     i, j;

    i = 0;
        
    if(argc == 1) {
    	printf("ERROR: Program has to be run with command-line arguments, for example: \n\n");
    	printf("hello This is some text\n");
    	return EXIT_FAILURE;
    }
        
    while (1) {
    	printf("#%d: ", i++);
    	for(j = 1; j < argc; j++) {
    		printf("%s ", argv[j]);
    	}
    	printf("\n");
        sleep (1);
    }
	return EXIT_SUCCESS;
}

