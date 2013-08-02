#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mcp3008read.h"


int
main()
{
	int             ret;
	mcp3008read_attr_t attr;
	uint10_t        data[7];
	ret =
	    mcp3008read_attr_init(&attr, "/dev/spidev0.1", 3000000, 8, CH0, CH1,
				  CH2, CH3, CH4, CH5, CH6, CH7);
	if (ret < 0) {
		pmcp3008error("mcp3008read_attr_init failed!");
		exit(EXIT_FAILURE);
	}

	while (true) {
		ret = mcp3008read(&attr, data);
		if (ret < 0) {
			fprintf(stderr, "ERROR read! return: %d\n", ret);
			exit(EXIT_FAILURE);
		}
		printf("CH0: %hu \n", data[CH0]);
		printf("CH1: %hu \n", data[CH1]);
		printf("CH2: %hu \n", data[CH2]);
		printf("CH3: %hu \n", data[CH3]);
		printf("CH4: %hu \n", data[CH4]);
		printf("CH5: %hu \n", data[CH5]);
		printf("CH6: %hu \n", data[CH6]);
		printf("CH7: %hu \n", data[CH7]);

		system("clear");
	}
	ret = mcp3008read_attr_destroy(&attr);
	if (ret < 0) {
		fprintf(stderr, "ERROR destroy! return: %d\n", ret);
		exit(EXIT_FAILURE);
	}

}
