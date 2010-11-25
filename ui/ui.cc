#include <GL/glut.h>
#include "ui.hh"
#include "font.hh"
#include <luabind/luabind.hpp>

// *** Window functions ***

const float ui_text[] = { 0.0, 0.0, 0.8 };
const float ui_front[] = { 0.8, 0.8, 0.8 };
const float ui_border1[] = { 1.0, 1.0, 1.0 };
const float ui_border2[] = { 0.2, 0.2, 0.2 };

UI ui;

extern lua_State *lua;

Window::Window(int mx, int my, std::string mtitle)
  : x(mx), y(my), w(10), h(10), title(mtitle), border(true), draggable(true)
{
  ui.windows.push_back(this);
}


void Window::draw()
{
  glColor3fv(ui_front);
  fillRect(x, y, x+w, y+h);

  if (border) {
    glBegin(GL_LINE_LOOP);
    glColor3fv(ui_border1);
    glVertex2i(x,y);
    glVertex2i(x+w,y);
    glColor3fv(ui_border2);
    glVertex2i(x+w,y+h);
    glVertex2i(x,y+h);
    glEnd();
  }

  glColor3fv(ui_text);
  glRasterPos2i(x+2, y+16);
  glPrint("%s", title.c_str());
}


// *** UI functions ***

void UI::init()
{
	int error = luaL_dofile(lua, "init.lua");

  if (error) {
    std::cerr << std::endl << lua_tostring(lua, -1) << std::endl;
  }
}


void UI::motion(int x, int y)
{
  if (drag) {
    drag->x = x - dx;
    drag->y = y - dy;

    try {
      if (drag->onMove && luabind::type(drag->onMove) == LUA_TFUNCTION) {
        drag->onMove(boost::ref(*drag));
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << ":" << std::endl << lua_tostring(lua, -1) << std::endl;
    }

    glutPostRedisplay();
  }
}


void UI::mouseDown(int button, int x, int y)
{
  for (std::vector<Window*>::reverse_iterator it = windows.rbegin(); it != windows.rend(); it++) {
    if (x >= (*it)->x && (x <= (*it)->x + (*it)->w) && y >= (*it)->y && (y <= (*it)->y + (*it)->h)) {
      if ((*it)->draggable) {
        drag = *it;
        dx = x - drag->x;
        dy = y - drag->y;
      }

      try {
        if ((*it)->onClick && luabind::type((*it)->onClick) == LUA_TFUNCTION) {
          (*it)->onClick(boost::ref(**it));
        }
      } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
      }
      
      glutPostRedisplay();
      break;
    }
  }
}


void UI::mouseUp(int button, int x, int y)
{
	drag = 0;
}


void UI::reshape(int w, int h)
{
  this->w = w;
  this->h = h;
}


void UI::draw()
{
	glMatrixMode(GL_PROJECTION);
  glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);
	glMatrixMode (GL_MODELVIEW);
  glPushMatrix();
	glLoadIdentity();

  glColor3f(0., 1., 0.);

  for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end(); it++) {
    (*it)->draw();
  }

	glMatrixMode (GL_PROJECTION);
  glPopMatrix();

	glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}

