/*
** File:	clipPolygon.h
** Author:	Warren R. Carithers
**
** Prototype for the polygon clip routine
*/

#ifndef _CLIPPOLYGON_H
#define _CLIPPOLYGON_H

#include <GL/glut.h>		/* glut.h includes gl.h and glu.h */

/*
** clipPolygon - clip a polygon to a rectangular clipping region
**
** parameters:
**	in	incoming vertex count
**	inv	incoming vertex list
**	out	outgoing (result) vertex count
**	outv	outgoing (result) vertex list
**	x0	x coordinate of lower left corner of clipping region
**	y0	y coordinate of lower left corner of clipping region
**	x1	x coordinate of upper right corner of clipping region
**	y1	y coordinate of upper right corner of clipping region
*/

void clipPolygon( GLint in, GLint inv[][2],
		  GLint *out, GLint outv[][2],
		  GLint x0, GLint y0, GLint x1, GLint y1 );

#endif
