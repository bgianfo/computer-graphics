/*
** File:	shape.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include "vecmath.h"

class Shape {
public:
  virtual ~Shape();  
  virtual void draw();

protected:
  Shape();
  void addTriangle(const Point3& p1, const Point3& p2, const Point3& p3);

  // Hint:
  // This is not absolutely necessary but, for the cube and the sides of the cylinder and cone, it might be helpful
  // to have an addSquare method that makes two calls to addTriangle.

  vector<Point3> vertices;  
};

class Cube : public Shape {
public:
  Cube(int);
};

class Cylinder : public Shape {
public:
  Cylinder(int, int);
};

class Cone : public Shape {
public:
  Cone(int, int);
};

class Sphere : public Shape {
public:
  Sphere(int);
  Sphere(int, const Point3 &p1, const Point3 &p2, const Point3 &p3);
};

#endif
