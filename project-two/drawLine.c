/* 
** File:	drawLine.c
** Author: Brian Gianforcaro - bjg1955@rit.edu
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <drawLine.h>

/*
** drawLine
**
** Draw a line from vertex (x0,y0) to vertex (x1,y1) using
** the midpoint line algorithm (as discussed in class).
*/

void drawLine( GLint x0, GLint y0, GLint x1, GLint y1 ) {
    glBegin(GL_POINTS);
    int steep = (abs(y1-y0) > abs(x1 - x0));
    if (steep) {
	int tmp = x0;
	x0 = y0;
	y0 = tmp;
	tmp = x1;
	x1 = y1;
	y1 = tmp;
    }
    if (x0 > x1) {
	int tmp = x0;
	x0 = x1;
	x1 = tmp;
	tmp = y0;
	y0 = y1;
	y1 = tmp;
    }
    int dx = x1 - x0;
    int dy = abs(y1-y0);
    float err = 0.0;
    float derr = (float)dy/(float)dx;
    int ystep;	
    int y = y0;
    if (y0 < y1) {
	ystep = 1;
    } else {
	ystep = -1;
    }
    for (int x = x0; x <= x1; x++) {
	if (steep) {
	    glVertex2i(y,x);
	} else {
	    glVertex2i(x,y);
	}
	err = err + derr;
	if (err >= 0.5) {
	    y = y+ystep;
	    err = err - 1.0;
	}
    }
    glEnd();
}
