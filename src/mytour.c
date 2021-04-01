#include "mytour.h"
#include <omp.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#define sqr(a) a * a

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