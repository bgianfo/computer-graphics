/*
** File:	drawLine.h
** Author:	Warren R. Carithers
**
** Prototype for the line drawing routine
*/

#ifndef _DRAWLINE_H
#define _DRAWLINE_H

#include <GL/glut.h>		/* glut.h includes gl.h and glu.h */

/*
** drawLine - draw a line using the midpoint line algorithm
**
** parameters:
**	x0	x coordinate of starting vertex
**	y0	y coordinate of starting vertex
**	x1	x coordinate of ending vertex
**	y1	y coordinate of ending vertex
*/

void drawLine( GLint x0, GLint y0, GLint x1, GLint y1 );

#endif
