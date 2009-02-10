/*
** File:	draw_routines.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _DRAW_ROUTINES_H_
#define _DRAW_ROUTINES_H_

#include "color.h"
#include "vecmath.h"

class DrawRoutines {
public:
  static void drawTriangle(const Point3&, const Point3&, const Point3&); 
  static void setBackground(double, double, double);
private:
  DrawRoutines() {}
  ~DrawRoutines() {} 
};

#endif
