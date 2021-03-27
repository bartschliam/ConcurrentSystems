#include "mytour.h"
#include <omp.h>
#include <alloca.h>
#include <math.h>
#include <float.h>


void my_tour(const point cities[], int tour[], int ncities)
{
	/*#pragma omp parallel
	{
		int NCPU,tid,NPR,NTHR;
		get the total number of CPUs/cores available for OpenMP
		NCPU = omp_get_num_procs();
		get the current thread ID in the parallel region
		tid = omp_get_thread_num();
		get the total number of threads available in this parallel region
		NPR = omp_get_num_threads();
		get the total number of threads requested
		NTHR = omp_get_max_threads();
		only execute this on the master thread!
		if (tid == 0) {
	  		printf("%i : NCPU = %i\n",tid,NCPU);
	  		printf("%i : NTHR = %i\n",tid,NTHR);
	  		printf("%i : NPR  = %i\n",tid,NPR);
		}
	}*/
	int i, j;
	char *visited = alloca(ncities);
	int ThisPt, ClosePt = 0;
	float CloseDist;
	int endtour = 0;
	#pragma omp parallel for
	for (i = 0; i < ncities; i++){
    	visited[i] = 0;
	}
	ThisPt = ncities - 1;
	visited[ncities - 1] = 1;
	tour[endtour++] = ncities - 1;
	for (i = 1; i < ncities; i++) {
	    CloseDist = DBL_MAX;
	    for (j = 0; j < ncities-1; j++) {
	      if (!visited[j]) {
	        if (sqrt((cities[ThisPt].x - cities[j].x) * (cities[ThisPt].x - cities[j].x) + (cities[ThisPt].y - cities[j].y) * (cities[ThisPt].y - cities[j].y)) < CloseDist) {
	          CloseDist = sqrt((cities[ThisPt].x - cities[j].x) * (cities[ThisPt].x - cities[j].x) + (cities[ThisPt].y - cities[j].y) * (cities[ThisPt].y - cities[j].y));
	          ClosePt = j;
	        }
	      }
	    }
	    tour[endtour++] = ClosePt;
	    visited[ClosePt] = 1;
	    ThisPt = ClosePt;
	  }
}