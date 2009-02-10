/*
** File:	shapes_ui.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _SHAPES_UI_H_
#define _SHAPES_UI_H_

#include <FL/Fl_Window.H>
#include "user_interface.h"
#include "my_shapes.h"

class ShapesUI : public UserInterface {
public:
  ShapesUI(int, int);
  ~ShapesUI();
  void resize(int, int);
  void draw();
  int handle(int);
// here are some methods that might be usefull
  enum Shapes {
    SHAPE_CUBE,
    SHAPE_CYLINDER,
    SHAPE_CONE,
    SHAPE_SPHERE
  };

//
private:
  void displayUI();
  
  friend void display_style_callback(Fl_Widget*, void*);
  friend void shape_type_callback(Fl_Widget*, void*);
  friend void rotation_callback(Fl_Widget*, void*);
  friend void tess_x_callback(Fl_Widget*, void*);
  friend void tess_y_callback(Fl_Widget*, void*);
  friend void tessellate_callback(Fl_Widget*, void*);
  
  float xRot, yRot;
  int tessX, tessY, type, display;
  Fl_Window* w;
  MyShapes* myShapes;
};

#endif
