/* 
** File:	drawFilledPolygon.?
** Author:	?
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>

#include <drawFilledPolygon.h>

typedef struct {
	int ymax;
	int x; 
	int dx;
	int dy;
	int sum;
	struct Bucket *next;
} Bucket;

void deleteAfter (Bucket *q) {
	Bucket * p = q->next;
	q->next = p->next;
	free (p);
}

void insertEdge (Bucket *list, Bucket *edge) {
	Bucket * p, * q = list;
	p = q->next;
	while (p != NULL) {
		if (edge->xIntersect < p->xIntersect) {
			p = NULL;
		} else {
			q = p;
			p = p->next;
		}
	}
	edge->next = q->next;
	q->next = edge;
}

void update (int scan, Bucket * active) {
	Bucket * q = active, * p = active->next;
	while (p) {
		if (scan >= p->yUpper) f
			p = p->next;
			deleteAfter(q);
		} else {
			p->xIntersect = p->xIntersect + p->dxPerScan;
			q = p;
			p = p->next;
		}
	}
}

void fill (int scan, Bucket *active) {
	Bucket * p1, * p2;
	p1 = active->next;
	glBegin(GL_POINTS);
	while (p1) {
		p2 = p1->next;
		for (int i = p1->xIntersect; i < p2->xIntersect; i++) {
			glVertex2i((int)i,scan);
			p1 = p2->next;
		}
	}
	glEnd();
}

void build (int scan, Bucket *active, Bucket *edges[]) {
	Bucket *p, *q;
	p = edges[scan]->next;
	while (p) {
		q = p->next;
		insertEdge (active, p);
		p = q;
	}
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

	Bucket * edges[WINDOW_HEIGHT], * active;
	for (int i = 0; i < WINDOW_HEIGHT; i++) {
		edges[i] = (Edge *) malloc (sizeof (Edge));
		edges[i]->next = NULL;
	}
	buildEdgeList (cnt, pts, edges);
	active = (Bucket *) malloc (sizeof (Bucket));
	active->next = NULL;
	/* your implementation here */
	for (int scanl = 0; scan < WINDOW_HEIGHT; scan++) {
		build (scan, active, edges);
		if (active->next) {
			fill(scan, active);
			update(scan, active);
			resort(active);
		}
	}
		/* Free edge records that have been malloc’ed ... */

}

