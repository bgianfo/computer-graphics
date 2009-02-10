/*
** File:	gl_window.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <FL/Fl_Image.H>
#include <FL/Fl_Gl_Window.H>
#include "user_interface.h"
#include "draw_routines.h"

#ifdef _MSC_VER 
  // turn off symbol length warnings 
  #pragma warning (disable: 4786) 
  #pragma warning (disable: 4503) 
#endif 

class GLWindow : public Fl_Gl_Window {
public:
  GLWindow(int, int, int, int);
  ~GLWindow();
  
  void setState(int);
 
  enum Labs {
    LAB_NONE = -1, 
    LAB_SHAPES
  };

private:  
  void init();
  void draw();
  void resize(int, int);
  int handle(int);  
  
  bool glInit;
  bool isDrawing;
  int state;
  UserInterface* currentUI;
};

#endif
