#include "mytour.h"
#include <omp.h>
#include <alloca.h>
#include <math.h>
#include <float.h>


void my_tour(const point cities[], int tour[], int ncities)
{
	int i, j;
	char *visited = alloca(ncities);
	int ThisPt, ClosePt = 0;
	float CloseDist;
	int endtour = 0;
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