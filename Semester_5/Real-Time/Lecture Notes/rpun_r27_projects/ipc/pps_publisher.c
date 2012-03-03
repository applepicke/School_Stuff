/*
 * pps_publisher.c
 *
 *  Created on: 2010-03-29
 *      Author: dagibbs
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "pps_def.h"

int main(int argc, char *argv[])
{
	int pps_fd;
	int count = 0;
	int ret;
	char buf[128];

	pps_fd = open(PPS_COUNT_NAME, O_WRONLY|O_CREAT, 0666 );
	if( -1 == pps_fd )
	{
		perror( "pps open ");
		exit( 0 );
	}

	while ( 1 )
	{
		sprintf(buf, "count:: %d\n", count);

		ret = write( pps_fd, buf, strlen( buf ));
		if( -1 == ret )
		{
			perror( "pps write " );
			exit( 0 );
		}
		count++;
		sleep(1);
	}

	return 0;
}

