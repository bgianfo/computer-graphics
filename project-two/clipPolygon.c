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

    int inbounds(x,y) {
        if ( (x >= x0 && x <= x1) && (y >= y0 && y <= y1)) {
                return 1;
        } else {
                return 0;
        }
    }

    void intersection (int BOUND, GLint X1, GLint Y1, GLint X2, GLint Y2, Glint out[2]) {
        GLfloat m;
        if (X1 != X2) 
            m = (Y1-Y2)/(X1-X2);

        switch (BOUND) {
            case LEFT:
                out[0] = x0;
                out[1] = Y2 + (x0 - X2) * m;
                break;
            case RIGHT:
                out[0] = x1;
                out[1] = Y2 + (x1 - X2) * m;
                break;
            case BOTTOM:
                out[1] = y0;
                if (X1 != X2) {
                    out[0] = X2 + (y0 - Y2) / m;
                } else {
                    out[0] = X2;
                }
                break;
            case TOP:
                out[1] = x1;
                if (X1 != X2) {
                    out[0] = X2 + (x1 - Y2) / m;
                } else {
                    out[0] = X2;
                }
                break;
        }
    }

    void output(GLint x, GLint y) {
        outv[out][0] = x;
        outv[out][1] = y;
        out++;
    }

    void clip(int BOUND) {
        int xS = inv[n - 1][0];
        int yS = inv[n - 1][1];
        int xP; int yP;
        for (int j = 0; j < in; j++) {
            xP = inv[j][0];
            yP = inv[j][1];
            if (1 == inbounds(xP,yP)) { 
                if (0 == inbounds (xS, yS)) {
                    GLint out[2];
                    intersection(xS,yS,xP,yP,out);
                    output(out[0],out[1]);
                }
                output(xP,yP);
            } else if (1 == inbounds(xS,yS)) {
                GLint out[2];
                intersection(xP,yP,xS,yS,out);
                output(out[0],out[1]);
            }
            xS = xP;
            yS = yP;
        }
    }
    
    int LEFT = 0; int RIGHT = 1;
    int TOP = 2;  int BOTTOM = 3;
    clip(LEFT);
    clip(RIGHT);
    clip(TOP);
    clip(BOTTOM);
}

