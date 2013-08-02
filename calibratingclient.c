#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mcp3008read.h"

#define V_REF 5.06

int
main()
{
	int             ret;
	uint10_t        ch0, ch1, ch2, ch3, ch4;
	mcp3008read_attr_t attr;
	uint10_t        data[7];
	double		res_mul, perc;

	res_mul = V_REF/MCP3008_RESOLUTION;
 
	ret =
	    mcp3008read_attr_init(&attr, "/dev/spidev0.1", 3000000, 5, CH0, CH1,
				  CH2, CH3, CH4);
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
		ch0 = data[CH0];
		ch1 = data[CH1];
		ch2 = data[CH2];
		ch3 = data[CH3];
		ch4 = data[CH4];

		printf("----------------------------------------\n");
		printf("CH0 AD Converter Value:\t\t%hu \n", ch0);
		printf("CH0 Voltage Value:\t\t%.3f V\n",  ch0*res_mul);	
		perc= (((double)ch0)/((double)MCP3008_RESOLUTION))*100.0;
		printf("CH0 Percentage Value:\t\t%.0f %\n", perc);

		printf("----------------------------------------\n");
		printf("CH1 AD Converter Value:\t\t%hu \n", ch1);
		printf("CH1 Voltage Value:\t\t%.3f V\n",  ch1*res_mul);	
		perc= (((double)ch1)/((double)MCP3008_RESOLUTION))*100.0;
		printf("CH1 Percentage Value:\t\t%.0f %\n", perc);

		printf("----------------------------------------\n");
		printf("CH2 AD Converter Value:\t\t%hu \n", ch2);
		printf("CH2 Voltage Value:\t\t%.3f V\n",  ch2*res_mul);	
		perc= (((double)ch2)/((double)MCP3008_RESOLUTION))*100.0;
		printf("CH2 Percentage Value:\t\t%.0f %\n", perc);

		printf("----------------------------------------\n");
		printf("CH3 AD Converter Value:\t\t%hu \n", ch3);
		printf("CH3 Voltage Value:\t\t%.3f V\n",  ch3*res_mul);	
		perc= (((double)ch3)/((double)MCP3008_RESOLUTION))*100.0;
		printf("CH3 Percentage Value:\t\t%.0f %\n", perc);

		printf("----------------------------------------\n");
		printf("CH4 AD Converter Value:\t\t%hu \n", ch4);
		printf("CH4 Voltage Value:\t\t%.3f V\n",  ch4*res_mul);	
		perc= (((double)ch4)/((double)MCP3008_RESOLUTION))*100.0;
		printf("CH4 Percentage Value:\t\t%.0f %\n", perc);
		
		sleep(1);
	}
	ret = mcp3008read_attr_destroy(&attr);
	if (ret < 0) {
		fprintf(stderr, "ERROR destroy! return: %d\n", ret);
		exit(EXIT_FAILURE);
	}

}
