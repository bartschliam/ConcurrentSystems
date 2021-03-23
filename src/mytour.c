#include "mytour.h"
#include <omp.h>


void my_tour(const point cities[], int tour[], int ncities)
{
	#pragma omp parallel
 	{
		printf("hello multicore user!\n");
	}
	simple_find_tour(cities, tour, ncities);
}
