/* 
** File:	clipPolygon.?
** Author:	?
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>

#include <clipPolygon.h>

/*
** clipPolygon
**
** Clip a polygon using the Sutherland-Hodgman Polygon Clipping algorithm
** discussed in class and in the text. The polygon is specified with vertex
** count in and vertices inv; the clipping region is rectangular, and has
** lower-left corner (x0,y0) and upper-right corner (x1,y1). The resulting
** vertices are placed in outv, with the vertex count placed in out.
*/

void clipPolygon( GLint in, GLint inv[][2], GLint *out, GLint outv[][2],
		  GLint x0, GLint y0, GLint x1, GLint y1 ) {

	/* your implementation here */

}
