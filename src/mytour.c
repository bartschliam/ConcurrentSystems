
#include "mytour.h"
#include <omp.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <unistd.h>
#define sqr(a) (a) * (a)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void my_tour(const point cities[], int tour[], int ncities)
{
	int i, j;
  	char *visited = calloc(ncities, 1);
  	int ThisPt, ClosePt = 0;
  	float thisX, thisY, CloseDist;
  	int endtour = 0;
  	ThisPt = ncities - 1;
  	visited[ncities - 1] = 1;
  	tour[endtour++] = ncities - 1;
  	int end = ncities - 1;
	if( ncities > 70){
		int numCores = MIN(floor(cbrt(ncities)),sysconf(_SC_NPROCESSORS_ONLN));
		numCores = MAX(numCores,1);
		for (i = 1; i < ncities; i++) {
		    thisX = cities[ThisPt].x;
		    thisY = cities[ThisPt].y;
		    CloseDist = DBL_MAX;
		    #pragma omp parallel num_threads(numCores)
		    {
		    	float localMin = DBL_MAX;
			int lowestJ = end;
			#pragma omp for nowait
			for (j = 0; j < end; j++) {
				if (!visited[j]) {
			      		float x = thisX - cities[j].x;
			      		float y = thisY - cities[j].y;
			      		float dist = sqrt(sqr(x) + sqr(y));
			    		if (dist < localMin) {
			    			localMin = dist;
			    			lowestJ = j;
			    		}
		    		}
			}
		    	#pragma omp critical
		    	{
			    	if (localMin < CloseDist) {
			    		CloseDist = localMin;
			    		ClosePt = lowestJ;
			    	}
		    	}
			}
		    tour[endtour++] = ClosePt;
		    visited[ClosePt] = 1;
		    ThisPt = ClosePt;
		}
	} else {
		for (i = 1; i < ncities; i++) {
		        thisX = cities[ThisPt].x;
		        thisY = cities[ThisPt].y;
		        float CloseDist = DBL_MAX;
		   	float localCloseDist = CloseDist;
		   	int lowestJ = 0;
			for (int j = 0; j < ncities - 1; j++) {
			      	if (!visited[j]) {
			      		float x = thisX - cities[j].x;
			      		float y = thisY - cities[j].y;
			      		float dist = sqrt(sqr(x) + sqr(y));
			        	if (dist < localCloseDist) {
			          		localCloseDist = dist;
			          		lowestJ = j;
			        	}
			      	}
			}
			if (localCloseDist < CloseDist) {
			    CloseDist = localCloseDist;
			    ClosePt = lowestJ;
			}
		}
	        tour[endtour++] = ClosePt;
	        visited[ClosePt] = 1;
	        ThisPt = ClosePt;
	}
	free(visited);
}

/*

	Single Thread Optimised
	Just Remove the pragmas - some parts can be further optimised

void my_tour(const point cities[], int tour[], int ncities)
{
	int i;
  	char *visited = calloc(ncities, 1);
  	int ThisPt, ClosePt = 0;
  	float CloseDist;
  	float thisX, thisY;
  	int endtour = 0;
  	ThisPt = ncities - 1;
  	visited[ncities - 1] = 1;
  	tour[endtour++] = ncities - 1;
	  
	for (i = 1; i < ncities; i++) {
	    
	    thisX = cities[ThisPt].x;
	    thisY = cities[ThisPt].y;
	    float CloseDist = DBL_MAX;
	    #pragma omp parallel 
	    {
	   		float localCloseDist = CloseDist;
	   		int lowestJ = 0;
	   		#pragma omp for
		    for (int j = 0; j < ncities - 1; j++) {
		      	if (!visited[j]) {
		      		float x = thisX - cities[j].x;
		      		float y = thisY - cities[j].y;
		      		float dist = sqrt(sqr(x) + sqr(y));
		        	if (dist < localCloseDist) {
		          		localCloseDist = dist;
		          		lowestJ = j;
		        	}
		      	}
		    }
		    #pragma omp critical
		    if (localCloseDist < CloseDist) {
		    	CloseDist = localCloseDist;
		    	ClosePt = lowestJ;

		    }
		}
	    tour[endtour++] = ClosePt;
	    visited[ClosePt] = 1;
	    ThisPt = ClosePt;
	}
}

*/
