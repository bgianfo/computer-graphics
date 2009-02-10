/*
** File:	shapes_ui.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/gl.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include "shapes_ui.h"
#include "draw_routines.h"
#include "color.h"


ShapesUI::ShapesUI(int w, int h) : UserInterface() {
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  DrawRoutines::setBackground(1, 1, 1);
  myShapes = new MyShapes(); 
  resize(w, h);
  displayUI();  
}

ShapesUI::~ShapesUI() {
  // restore OpenGL defaults
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT, GL_FILL);
  glShadeModel(GL_SMOOTH);
  // delete resources
  w->hide();
  delete w;
  delete myShapes;
}

void ShapesUI::resize(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat) width /(GLfloat) height, 0.1, 4.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void ShapesUI::draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glDisable(GL_LIGHTING);
  glPolygonMode(GL_FRONT, GL_LINE);
  glColor3f(0.0f, 0.0f, 0.0f);
    
  glPushMatrix();
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
  myShapes->draw();
  glPopMatrix();
}

int ShapesUI::handle(int event) {
  return 0;
}

void shape_type_callback(Fl_Widget* w, void* data) {
  ((ShapesUI*) data)->type = ((Fl_Choice*) w)->value();
}

void rotation_callback(Fl_Widget* w, void* data) {
  switch (w->label()[0]) {
    case 'X': ((ShapesUI*) data)->xRot = ((Fl_Slider*) w)->value(); break;
    case 'Y': ((ShapesUI*) data)->yRot = ((Fl_Slider*) w)->value(); break;
    default: break;
  }
}

void tess_x_callback(Fl_Widget* w, void* data) {
  ((ShapesUI*) data)->tessX = (int) ((Fl_Value_Input*) w)->value();
}

void tess_y_callback(Fl_Widget* w, void* data) {
  ((ShapesUI*) data)->tessY = (int) ((Fl_Value_Input*) w)->value();
}

void tessellate_callback(Fl_Widget*, void* data) {
  ShapesUI* shapesUI = (ShapesUI*) data;
  shapesUI->myShapes->tessellate(shapesUI->type, shapesUI->tessX, shapesUI->tessY);
}

void close_shapes_win_callback(Fl_Widget*, void*) {
  // make it impossible to close the control window
}

void ShapesUI::displayUI() {
// generated with fluid
  w = new Fl_Window(240, 260, "Shapes UI");
  { Fl_Choice* o = new Fl_Choice(15, 25, 210, 25, "Shape Type");
    o->down_box(FL_BORDER_BOX);
    o->align(FL_ALIGN_TOP_LEFT);
    // must be defined in the same order as the SHAPE_* constants
    o->add("Cube",      0, shape_type_callback, this);
    o->add("Cylinder",  0, shape_type_callback, this);
    o->add("Cone",      0, shape_type_callback, this);
    o->add("Sphere",    0, shape_type_callback, this);
    o->value(0);
    shape_type_callback(o, this);
  }
  { Fl_Value_Input* o = new Fl_Value_Input(15, 120, 40, 25);
    o->minimum(1);
    o->maximum(100);
    o->step(1);
    o->value(5);
    o->callback(tess_x_callback, this);
    o->do_callback();
  }
  { Fl_Value_Input* o = new Fl_Value_Input(65, 120, 40, 25);
    o->minimum(1);
    o->maximum(100);
    o->step(1);
    o->value(5);
    o->callback(tess_y_callback, this);
    o->do_callback();
  }
  { Fl_Box* o = new Fl_Box(15, 120, 90, 25, "Parameters");
    o->align(FL_ALIGN_TOP_LEFT);
  }
  { Fl_Slider* o = new Fl_Slider(15, 175, 210, 25, "X Rotation");
    o->type(5);
    o->maximum(360);
    o->step(1);
    o->align(FL_ALIGN_TOP);
    o->callback(rotation_callback, this);
    o->do_callback();
  }
  { Fl_Slider* o = new Fl_Slider(15, 220, 210, 25, "Y Rotation");
    o->type(5);
    o->maximum(360);
    o->step(1);
    o->align(FL_ALIGN_TOP);
    o->callback(rotation_callback, this);
    o->do_callback();
  }
  { Fl_Button* o = new Fl_Button(125, 120, 100, 25, "Tessellate");
    o->box(FL_ENGRAVED_BOX);
    o->down_box(FL_DOWN_BOX);
    o->callback(tessellate_callback, this);
    o->do_callback();
  }
  w->end();
  w->callback(close_shapes_win_callback);
  w->set_non_modal();
  w->show();
}
