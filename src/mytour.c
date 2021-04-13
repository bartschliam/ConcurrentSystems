#include "mytour.h"
#include <omp.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <unistd.h>
#define sqr(a) (a) * (a)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void my_tour(const point cities_arr[], int tour[], int ncities)
{
	int i, j;
  	point *cities = malloc(ncities*sizeof(point));
  	for (i = 0; i < ncities; i++) cities[i] = cities_arr[i];
  	int ThisPt, ClosePt;
  	float thisX, thisY, CloseDist;
  	int endtour = 0;
  	int end = ncities - 1;
  	ThisPt = end;
  	ClosePt = end;
  	tour[endtour++] = end;
	int threadBreak = ncities - 5000;
	for (i = 1; i < threadBreak; i++) {
	    thisX = cities_arr[ClosePt].x;
	    thisY = cities_arr[ClosePt].y;
	    CloseDist = DBL_MAX;
	    #pragma omp parallel num_threads(18)
	    {
	    	float localMin = DBL_MAX;
			int lowestJ = end;
			#pragma omp for schedule(static) nowait
			for (j = 0; j < end; j++) {
	      		float x = thisX - cities[j].x;
	      		float y = thisY - cities[j].y;
	      		float dist = sqr(x) + sqr(y);
	    		if (dist < localMin){
	    			localMin = dist;
	    			lowestJ = j;
	    		}
			}
	    	#pragma omp critical
	    	{
		    	if (localMin < CloseDist) {
		    		CloseDist = localMin;
		    		ClosePt = cities[lowestJ].id;
		    		ThisPt = lowestJ;
		    	}
		    }
		}
		cities[ThisPt] = cities[--end];
	    tour[endtour++] = ClosePt;
	}
	float x, y, dist;
	for (i = MAX(threadBreak, 1); i < ncities; i++) {
	    thisX = cities_arr[ClosePt].x;
	    thisY = cities_arr[ClosePt].y;
	    CloseDist = DBL_MAX;

		for (j = 0; j < end; j++) {
      		x = thisX - cities[j].x;
      		y = thisY - cities[j].y;
      		dist = sqr(x) + sqr(y);
    		if (dist < CloseDist){
    			CloseDist = dist;
    			ClosePt = cities[j].id;
    			ThisPt = j;
    		}
		}
		cities[ThisPt] = cities[--end];
	    tour[endtour++] = ClosePt;
	}
	free(cities);
}
