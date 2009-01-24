/* 
** File:	clipPolygon.c
** Author: Brian Gianforcaro
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>
#include <clipPolygon.h>
#include <stdlib.h>


/*
 *  inbounds - determine if the given vertex is inbounds   
 *
 *  args: x - x to test
 *  	  y - y to test
 *  	  x0 - bounding bottom-left x
 *  	  y0 - bounding bottom left y
 *  	  x1 - bounding top right x
 *  	  y1 - bounding top right y
 *
 * return: 0 - false
 *         1 - true
 */

int inbounds(GLint x, GLint y, GLint x0, GLint y0, GLint x1, GLint y1) { 
    if ( (x >= x0 && x <= x1) && (y >= y0 && y <= y1) ) {
	    return 1;
    } else {
	    return 0;
    }
}

/*
 *  inbounds - determine if the given vertex is inbounds   
 *
 *  args: 
 *  	  X1 - x for point one 
 *  	  Y1 - y for point one
 *  	  X2 - x for point two
 *  	  Y2 - y for point two
 *
 *  	  x0 - bounding bottom-left x
 *  	  y0 - bounding bottom left y
 *  	  x1 - bounding top right x
 *  	  y1 - bounding top right y
 *
 * return: 0 - false
 *         1 - true
 */


void intersection (const int BOUND, GLint X1, GLint Y1,
			      GLint X2, GLint Y2,  
			      GLint *out, GLint x0, GLint y0, GLint x1, GLint y1) {
    GLfloat m;
    if (X1 != X2) m = (Y1-Y2)/(X1-X2);
    //LEFT:0 RIGHT:1 TOP:2 BOTTOM:3
    switch (BOUND) {
	case 0:
	    out[0] = x0;
	    out[1] = Y2 + (x0 - X2) * m;
	    break;
	case 1:
	    out[0] = x1;
	    out[1] = Y2 + (x1 - X2) * m;
	    break;
	case 2:
	    out[1] = y1;
	    if (X1 != X2) {
			out[0] = X2 + (y1 - Y2) / m;
	    } else {
			out[0] = X2;
	    }
	    break;
	case 3:
	    out[1] = x1;
	    if (X1 != X2) {
			out[0] = X2 + (x1 - Y2) / m;
	    } else {
			out[0] = X2;
	    }
	    break;
    }
}

/*
 *  output - store computed vertex    
 *
 *  args: x - x to store
 *  	  y - y to store
 *		  outv - array to store them in
 *		  out - index to store the x and y at
 */


void output(GLint x, GLint y, GLint outv[][2], GLint *out ) {
    outv[*out][0] = x;
    outv[*out][1] = y;
    (*out)++;
}

/*
 *  clip - Clip the 'in' vertices on the specified edge of the bounds.   
 * 
 *  args: BOUND - Edge  to clip on
 *		  x0 - bottom left bound x
 * 		  y0 - bottom left bound y
 *		  x1 - top right bound x
 *		  y1 - top right bound y		
 *  	  in - number of vertex's in 
 *		  inv - array of vertex's to clip
 *		  outv - array of clip'd vertex's		
 *  	  outi - number of  vertex's out
 */

void clip(int BOUND, GLint x0, GLint y0, GLint x1, GLint y1, GLint in, 
					 GLint inv[][2], GLint outv[][2], GLint *outi) {
    int xS = inv[in - 1][0];
    int yS = inv[in - 1][1];
    int xP; int yP;
	GLint *out;
    for (int j = 0; j < in; j++) {
		xP = inv[j][0];
		yP = inv[j][1];
		if (1 == inbounds(xP,yP,x0,y0,x1,y1)) { 
			if (0 == inbounds (xS, yS,x0,y0,x1,y1)) {
				out = malloc(2* sizeof(GLint));
				intersection(BOUND,xS,yS,xP,yP,out,x0,y0,x1,y1);
				output(out[0],out[1],outv,outi);
				free(out);
			}
			output(xP,yP,outv,outi);
		} else if (1 == inbounds(xS,yS,x0,y0,x1,y1)) {
			out = malloc(2* sizeof(GLint));
			intersection(BOUND,xP,yP,xS,yS,out,x0,y0,x1,y1);
			output(out[0],out[1],outv,outi);
			free(out);
		}
		xS = xP;
		yS = yP;
    }
}


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

    GLint inv1[50][2], inv2[50][2], inv3[50][2];
    GLint out1 = 0, out2 = 0, out3 = 0;
    
    //LEFT:0 RIGHT:1 TOP:2 BOTTOM:3
    clip(0,x0,y0,x1,y1,in,  inv, inv1,&out1);
	me/burny/.gnome2/panel2.d/default/launchers/firefox-bin.desktop' 
    clip(1,x0,y0,x1,y1,out1,inv1,inv2,&out2);
    clip(2,x0,y0,x1,y1,out2,inv2,inv3,&out3);
    clip(3,x0,y0,x1,y1,out3,inv3,outv,out);
}

