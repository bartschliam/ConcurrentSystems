#include "mytour.h"
#include <omp.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#define sqr(a) a * a

void my_tour(const point cities[], int tour[], int ncities)
{
	int i,j;
  	char *visited = calloc(ncities, 1);
  	int ThisPt, ClosePt = 0;
  	float CloseDist, dist;
  	float x, y, thisX, thisY;
  	int endtour = 0;
  	ThisPt = ncities - 1;
  	visited[ncities - 1] = 1;
  	tour[endtour++] = ncities - 1;
	  
	for (i = 1; i < ncities; i++) {
	    CloseDist = DBL_MAX;
	    thisX = cities[ThisPt].x;
	    thisY = cities[ThisPt].y;
	    for (j = 0; j < ncities - 1; j++) {
	      	if (!visited[j]) {
	      		x = thisX - cities[j].x;
	      		y = thisY - cities[j].y;
	      		dist = sqrt(sqr(x) + sqr(y));
	        	if (dist < CloseDist) {
	          		CloseDist = dist;
	          		ClosePt = j;
	        	}
	      	}
	    }
	    tour[endtour++] = ClosePt;
	    visited[ClosePt] = 1;
	    ThisPt = ClosePt;
	}
}