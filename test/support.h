/*
** File:	support.h
** Author:	Warren R. Carithers
**
** Prototypes for supporting functions for the test* programs
*/

#ifndef _SUPPORT_H
#define _SUPPORT_H

#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/

/*
** print_poly - print a set of vertices as a line loop
**
** parameters:
**	n	number of vertices
**	v	vertex array
**
*/

void print_poly( GLint n, GLint v[][2] );

#ifdef __cplusplus
extern "C" {
#endif

/*
** Keyboard routine - handle what minimal keyboard input is required
*/

void keyboard( GLubyte key, GLint x, GLint y );

#ifdef __cplusplus
}
#endif

/*
** init - set up the display
*/

void init( int argc, char **argv, const char *title );

#endif
