/*
** File:	draw_routines.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#include <FL/gl.h>
#include "draw_routines.h"

void DrawRoutines::drawTriangle(const Point3& p1, const Point3& p2, const Point3& p3) {
  glBegin(GL_TRIANGLES);
  glVertex3d(p1.x, p1.y, p1.z);
  glVertex3d(p2.x, p2.y, p2.z);
  glVertex3d(p3.x, p3.y, p3.z);
  glEnd();
}

void DrawRoutines::setBackground(double r, double g, double b) {
  glClearColor((GLfloat) r, (GLfloat) g, (GLfloat) b, 1.0f);
}
