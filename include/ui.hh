#ifndef _UI_HH_
#define _UI_HH_

#include <vector>
#include <list>
#include <iostream>

#include "draw.hh"
#include "stdafx.h"

#include "components.hh"

namespace app {
	extern int width, height;
}

class Window : public Container {
public:
  bool draggable;

  std::string title;
  luabind::object onMove;

  bool border;

  Window(int mx, int my, std::string mtitle);

  void draw();
  void pack();

  virtual void add(Component *comp);
};

class UI {
private:
  // Dragging:
  Window *drag;
  int dx;
  int dy;

  Component *focused;

public:
  // Width and height
  int w, h;

  std::list<Window*> windows;

  UI() : drag(0), focused(0) {}

  // Initialize the UI
  void init();

  // Draw all visible UI content
  void draw();

  // Mouse
  bool motion(int x, int y);
  bool mouseDown(int button, int x, int y);
  bool mouseUp(int button, int x, int y);

  // Keyboard
  void keyDown(int key);

  // OpenGL window was resized
  void reshape(int w, int h);

  bool hasFocus(Component *comp);
  void setFocus(Component *comp);
};

extern UI ui;

#endif
