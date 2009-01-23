/* 
** File:	clipPolygon.c
** Author: Brian Gianforcaro
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>

#include <clipPolygon.h>


 
int inbounds(GLint x, GLint y, GLint *bounds[4]) {
    if ( (x >= *bounds[0] && x <= *bounds[2]) && (y >= *bounds[1] && y <= *bounds[3])) {
	    return 1;
    } else {
	    return 0;
    }
}

void intersection (const int BOUND, GLint X1, GLint Y1,
			      GLint X2, GLint Y2,  
			      GLint *out[2], GLint *bounds[4]) {
    GLfloat m;
    if (X1 != X2) 
	m = (Y1-Y2)/(X1-X2);

    switch (BOUND) {
	case 0:
	    *out[0] = *bounds[0];
	    *out[1] = Y2 + (*bounds[0] - X2) * m;
	    break;
	case 1:
	    *out[0] = *bounds[2];
	    *out[1] = Y2 + (*bounds[2] - X2) * m;
	    break;
	case 2:
	    *out[1] = *bounds[1];
	    if (X1 != X2) {
		*out[0] = X2 + (*bounds[1] - Y2) / m;
	    } else {
		*out[0] = X2;
	    }
	    break;
	case 3:
	    *out[1] = *bounds[2];
	    if (X1 != X2) {
		*out[0] = X2 + (*bounds[2] - Y2) / m;
	    } else {
		*out[0] = X2;
	    }
	    break;
    }
}

void output(GLint x, GLint y, GLint outv[][2], GLint *out ) {
    outv[*out][0] = x;
    outv[*out][1] = y;
    (*out)++;
}


void clip(int BOUND, GLint *bounds[4], GLint in, GLint inv[][2], GLint outv[][2], GLint *outi) {
    int xS = inv[in - 1][0];
    int yS = inv[in - 1][1];
    int xP; int yP;
    for (int j = 0; j < in; j++) {
	xP = inv[j][0];
	yP = inv[j][1];
	if (1 == inbounds(xP,yP,bounds)) { 
	    if (0 == inbounds (xS, yS,bounds)) {
		GLint *out[2];
		intersection(BOUND,xS,yS,xP,yP,out,bounds);
		output(*out[0],*out[1],outv,outi);
	    }
	    output(xP,yP,outv,outi);
	} else if (1 == inbounds(xS,yS,bounds)) {
	    GLint *out[2];
	    intersection(BOUND,xP,yP,xS,yS,out,bounds);
	    output(*out[0],*out[1],outv,outi);
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

    GLint *bounds[4];
    *bounds[0]= x0;
    *bounds[1]= y0;
    *bounds[2]= x1;
    *bounds[3]= y1;

    GLint inv1[50][2], inv2[50][2], inv3[50][2];
    GLint out1 = 0, out2 = 0, out3 = 0;
    
    //LEFT:0 RIGHT:1 TOP:2 BOTTOM:3
    clip(0,bounds,in,  inv, inv1,&out1);
    clip(1,bounds,out1,inv1,inv2,&out2);
    clip(2,bounds,out2,inv2,inv3,&out3);
    clip(3,bounds,out3,inv3,outv,out);
}

