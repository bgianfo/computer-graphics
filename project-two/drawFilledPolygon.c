/* 
** File:	drawFilledPolygon.c
** Author:	Brian Gianforcaro
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <drawFilledPolygon.h>

typedef struct {
	int miny;
	int maxy;
	int miny_x;
	float slope;
	struct Edge *next;
} Edge;

/**
 * remove - remove the edge after the specified
 * args:
 * 		q - edge to remove after
 */
void remove (Edge *q) {
	Edge *p = q->next;
	q->next = p->next;
	free (p);
}

/*
 * insertEdge - perform a smart insert on the specified new edge.
 * args:
 * 		list - current scan line
 * 		newedge - edge to insert
 */
void insertEdge (Edge *list, Edge *newedge) {
	Edge *q = list;
	Edge *p = q->next;
	while (p != NULL) {
		if (newedge->miny_x < p->miny_x) {
			p = NULL;
		} else {
			q = p;
			p = p->next;
		}
	}
	newedge->next = q->next;
	q->next = newedge;
}

/*
 * update - prune and update x values in the active edge list
 * args:
 * 		scan - current scan line
 * 		active - current active edge list
 */
void update (int scan, Edge * active) {
	Edge * q = active, * p = active->next;
	while (p) {
		if (scan >= p->maxy) {
			p = p->next;
			remove(q);
		} else {
			p->miny_x = p->miny_x + (1/p->slope);
			q = p;
			p = p->next;
		}
	}
}

/*
 * fill - fill the scan for a specified active edge list
 * args:
 * 		scan - current scan line
 * 		active - current active edge list
 */
void fill (int scan, Edge *active) {
	Edge * p1, * p2;
	p1 = active->next;
	glBegin(GL_POINTS);
	while (p1) {
		p2 = p1->next;
		for (int i = p1->miny_x; i < p2->miny_x; i++) {
			glVertex2i((int)i,scan);
			p1 = p2->next;
		}
	}
	glEnd();
}

/*
** drawFilledPolygon
**
** Draw a filled polygon using the scan-line-based polygon fill algorithm
** discussed in class. The polygon has n distinct vertices. Each vertex is
** a row in the v parameter; for vertex k, v[k][0] is the x coordinate, and
** v[k][1] the y coordinate.
*/

void drawFilledPolygon( GLint n, GLint v[][2] ) {
	const static int WINDOW_HEIGHT = 300; //Detailed in project description

	//Parse our verticies into "all_edges"
	Edge * all_edges[n];
	for (int i = 0; i < n; i++) {
		int rollover;
		if ((i+1) == n) { 
			rollover = 0;
		} else {
			rollover = i+1;
		}

		all_edges[i] = (Edge *) malloc (sizeof (Edge));
		all_edges[i]->miny = v[i][1];

		int max_x;
		if (v[rollover][1] < all_edges[i]->miny) {
			all_edges[i]->miny = v[rollover][1];
			all_edges[i]->maxy = v[i][1];

			all_edges[i]->miny_x = v[rollover][0];
			max_x = v[i][0];
		} else {
			all_edges[i]->maxy = v[rollover][1];
			all_edges[i]->miny_x = v[i][0];
			max_x = v[rollover][0];
		}

		if (max_x == all_edges[i]->miny_x) {
			all_edges[i]->slope = 0;
		} else {
			all_edges[i]->slope = (all_edges[i]->maxy - all_edges[i]->miny) / (max_x - all_edges[i]->miny_x);
		}

		all_edges[i]->next = NULL;
	}

	//Find the starting scan line and top of the polygon
	int start_scanline = WINDOW_HEIGHT;
	int end_scanline = 0;
	for (int i = 0; i < n; i++) {
		if (all_edges[i]->miny < start_scanline) {
			start_scanline = all_edges[i]->miny;
		}
		 
		if (all_edges[i]->maxy > end_scanline) {
			end_scanline = all_edges[i]->maxy;
		}
	}

	//Construct our Global Edge Table
	Edge * glet [WINDOW_HEIGHT];
	for (int i = start_scanline; i <= end_scanline; i++) {
		for (int j = 0; j < n; j++) {
			if ( (all_edges[j]->miny == i) ) { //&& (all_edges[j].slope != 0) ) {
				if (NULL == &glet[i]) {
					glet[i] = all_edges[j];
				} else {
					insertEdge(glet[i], all_edges[j]);
				}
			}
		}
	}

	//Initialize the Active Edge Table	
	Edge * aet;
	int i = start_scanline;
	aet = glet[i];
	//Get along with the the algorithm
	while (i <= end_scanline) {
		fill(i, aet);
		i++;
		update(i,aet);
		if (NULL != &glet[i]) {
			insertEdge(aet, glet[i]);
		}
	}


	//Make sure all memory is free.
	for (int i = 0; i < WINDOW_HEIGHT; i++) {
		if (&glet[i] != NULL) {
			free(glet[i]);
		}
	}
	for (int i = 0; i < n; i++) {
		if (&all_edges[i] != NULL) {
			free(all_edges[i]);
		}
	}

}

