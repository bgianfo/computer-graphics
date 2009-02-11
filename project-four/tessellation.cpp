/*
** File:	tessellation.cpp
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Window.H>
#include <string>
#include "gl_window.h"

void idle_callback(void* data) {
  ((GLWindow*) data)->redraw();
}

void ok_button_callback(Fl_Widget*, void* data) {
  ((Fl_Window*) data)->hide();
}

void about_callback(Fl_Widget*, void* data) {
  Fl_Window* w = new Fl_Window(290, 100, "About");
  w->position(((GLWindow*) data)->parent()->x() + (((GLWindow*) data)->w() - w->w()) / 2, ((GLWindow*) data)->parent()->y() + (((GLWindow*) data)->h() - w->h()) / 2);
  { Fl_Box* o = new Fl_Box(10, 10, 165, 25, "Computer Graphics 1 - Shape Tesselation");
    o->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  }
  { Fl_Box* o = new Fl_Box(10, 40, 165, 25, "Student Name: Brian Gianforcaro");
    o->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  }
  { Fl_Button* o = new Fl_Button(190, 65, 90, 25, "OK");
    o->box(FL_ENGRAVED_BOX);
    o->down_box(FL_DOWN_BOX);
    o->callback(ok_button_callback, w);
  }
  w->end();
  w->set_modal(); 
  w->show();
  while (w->visible())
    Fl::wait();
  delete w;
}

void quit_callback(Fl_Widget*, void*) {
  if (!Fl::event_key(FL_Escape)) // prevent esc from closing main window
    exit(0);
}

void lab_callback(Fl_Widget* w, void* data) {
  // note: 4 is the hard coded index of "shapes" in the menu items array
  // if you make changes to the menu you might need to change this
  // this also assumes that the state numbers are sequential
  ((GLWindow*) data)->setState(((Fl_Menu_Bar*) w)->value() - 4);
}

int main (int argc, char *argv[]) {
  Fl_Window* window = new Fl_Window(640, 505, "Computer Graphics 1 - Shape Tesselation");
  window->position((Fl::w() - window->w()) / 2, (Fl::h() - window->h()) / 2);
  GLWindow* glwindow = new GLWindow(0, 25, 640, 480);
  window->resizable(glwindow);
  Fl_Menu_Bar* m = new Fl_Menu_Bar(0, 0, 640, 25);
  m->add("File/E&xit"         , FL_CTRL + 'x', quit_callback);
  m->add("Lab/Shapes"   , FL_CTRL + '1', lab_callback, glwindow, FL_MENU_RADIO);
  m->add("Help/About", FL_CTRL + 'a', about_callback, glwindow);
  m->box(FL_NO_BOX);
  window->end();
  window->callback(quit_callback);
  window->show();
  Fl::add_idle(idle_callback, glwindow);
  Fl::run();
  delete window;
  return 0;
}
