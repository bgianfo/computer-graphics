/*
** File:	drawFilledPolygon.h
** Author:	Warren R. Carithers
**
** Prototype for the polygon fill routine
*/

#ifndef _DRAWFILLEDPOLYGON_H
#define _DRAWFILLEDPOLYGON_H

#include <GL/glut.h>		/* glut.h includes gl.h and glu.h */

/*
** drawFilledPolygon - draw a filled polygon using the edge table method
**
** parameters:
**	n	vertex count
**	v	vertex list
*/

void drawFilledPolygon( GLint n, GLint v[][2] );

#endif
