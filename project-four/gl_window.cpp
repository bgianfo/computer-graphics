/*
** File:	gl_window.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#include <FL/fl_ask.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <cstdio>
#include <string>
#include "gl_window.h"
#include "shapes_ui.h"

GLWindow::GLWindow(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h) {
  mode(FL_RGB8 | FL_DOUBLE | FL_DEPTH);
  glInit = false;
  state = LAB_NONE;
  currentUI = 0;
  isDrawing = false;
}

GLWindow::~GLWindow() {
  if (currentUI != 0)
    delete currentUI;
}

void GLWindow::setState(int s) {
  if (state == s)
    return;
  if (currentUI != 0)
    delete currentUI;
  currentUI = 0; 
  switch (s) {
    case LAB_SHAPES: state = s; break;
    default: state = LAB_NONE; break;
  }
  glInit = false;     
}

void GLWindow::init() {
  switch (state) {
    case LAB_SHAPES:    currentUI = new ShapesUI(w(), h());    break;
    default: DrawRoutines::setBackground(1.0, 1.0, 1.0); break;
  }
}

void GLWindow::draw() {
  // prevent nested calls to draw from creating infinite loops
  if (isDrawing)
    return;
  isDrawing = true;
  // one time only initialization
  if (!glInit) {
    init();
    glInit = true;     
  }
  // if user resized the window  
  if (!valid() && currentUI != 0)
    currentUI->resize(w(), h());
  // display 
  if (currentUI != 0)
    currentUI->draw();  
  else
    glClear(GL_COLOR_BUFFER_BIT);
  isDrawing = false; 
}

int GLWindow::handle(int event) {
  int r = (currentUI != 0) ? currentUI->handle(event) : 0;  
  if (r == 0)
    return Fl_Gl_Window::handle(event);
  return r;
}
