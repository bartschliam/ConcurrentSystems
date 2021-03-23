#include "mytour.h"
#include <omp.h>


void my_tour(const point cities[], int tour[], int ncities)
{
	#pragma omp parallel
	{
		int NCPU,tid,NPR,NTHR;
		/* get the total number of CPUs/cores available for OpenMP */
		NCPU = omp_get_num_procs();
		/* get the current thread ID in the parallel region */
		tid = omp_get_thread_num();
		/* get the total number of threads available in this parallel region */
		NPR = omp_get_num_threads();
		/* get the total number of threads requested */
		NTHR = omp_get_max_threads();
		/* only execute this on the master thread! */
		if (tid == 0) {
	  		printf("%i : NCPU = %i\n",tid,NCPU);
	  		printf("%i : NTHR = %i\n",tid,NTHR);
	  		printf("%i : NPR  = %i\n",tid,NPR);
		}
	}
	simple_find_tour(cities, tour, ncities);
}
