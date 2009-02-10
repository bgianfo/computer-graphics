/*
** File:	my_shapes.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#include "my_shapes.h"
#include "shapes_ui.h"

MyShapes::MyShapes() {
  current = 0;
}

MyShapes::~MyShapes() {
  if (current != 0)
    delete current;
}

void MyShapes::draw() {
  if (current != 0)
    current->draw();
}

void MyShapes::tessellate(int type, int tessX, int tessY) {
  if (current != 0)
    delete current;
  switch (type) {
    case ShapesUI::SHAPE_CUBE: current = new Cube(tessX); break;
    case ShapesUI::SHAPE_CYLINDER: current = new Cylinder(tessX, tessY); break;
    case ShapesUI::SHAPE_CONE: current = new Cone(tessX, tessY); break;
    case ShapesUI::SHAPE_SPHERE: current = new Sphere(tessX); break;
    default: current = 0; break;
  }
}
