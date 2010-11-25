#ifndef _UI_HH_
#define _UI_HH_

#include "draw.hh"
#include <vector>
#include <iostream>

#include <luabind/luabind.hpp>

class Window {
public:
  int x,y;
  int w,h;
  bool draggable;

  std::string title;
  luabind::object onClick;
  luabind::object onMove;

  bool border;

  Window(int mx, int my, std::string mtitle);

  void setTitle(std::string const& title) {
    this->title = title;
  }

  std::string getTitle() {
    return title;
  }

  void draw();

  ~Window() {
    std::cerr << "window " << this << " deleted!" << std::endl;
  }
};

class UI {
private:
  // Dragging:
  Window *drag;
  int dx;
  int dy;

public:
  // Width and height
  int w, h;

  std::vector<Window*> windows;

  UI() : drag(0) {}

  // Initialize the UI
  void init();

  // Draw all visible UI content
  void draw();

  // Mouse
  void motion(int x, int y);
  void mouseDown(int button, int x, int y);
  void mouseUp(int button, int x, int y);

  // OpenGL window was resized
  void reshape(int w, int h);
};

extern UI ui;

#endif
