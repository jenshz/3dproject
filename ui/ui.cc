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
  : Container(mx, my, 10, 10), title(mtitle), border(true), draggable(true)
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
  Container::draw(0, 0);
}

void Window::layout()
{
}

// *** UI functions ***

void UI::init()
{
	int error = luaL_dofile(lua, "init.lua");

  if (error) {
    std::cerr << std::endl << lua_tostring(lua, -1) << std::endl;
  }

  // Lets create a test window
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
  } else if (focused) {
	  // TODO: Do this right some time.
	  /*if (dx > 2 || dy > 2 || dy < -2 || dx < -2) {
		  ui.setFocus(0);
	      glutPostRedisplay();
	  } */
  }
}


void UI::mouseDown(int button, int cx, int cy)
{
  for (std::list<Window*>::iterator it = windows.begin(); it != windows.end(); it++) {
	Window *w = *it;
    if (w->visible && cx >= w->x && (cx < w->x + w->w) && cy >= w->y && (cy < w->y + w->h)) {
	  // Bring window to front.
	  windows.erase(it);
	  windows.push_front(w);

	  if (w->onClick(cx, cy)) {
	      glutPostRedisplay();
		  return;
	  }

	  // Window is draggable
      if (w->draggable) {
        drag = w;
        dx = cx - drag->x;
        dy = cy - drag->y;
      }

      glutPostRedisplay();
      break;
    }
  }
  ui.setFocus(0);
}


void UI::mouseUp(int button, int x, int y)
{
	drag = 0;
	if (focused) {
		ClickListener *cl = dynamic_cast<ClickListener*>(focused);
		if (cl) {
			cl->click();
			focused = 0;
			glutPostRedisplay();
		}
	}
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

  for (std::list<Window*>::reverse_iterator it = windows.rbegin(); it != windows.rend(); it++) {
	  if ((*it)->visible)
		(*it)->draw();
  }

  glMatrixMode (GL_PROJECTION);
  glPopMatrix();

  glMatrixMode (GL_MODELVIEW);
  glPopMatrix();
}

bool UI::hasFocus(Component *comp)
{
	return (focused == comp);
}

void UI::setFocus(Component *comp)
{
	focused = comp;
}

void UI::keyDown(int key)
{
	KeyListener *kl = dynamic_cast<KeyListener*>(focused);
	if (kl) {
		kl->keyPressed(key);
	}
	glutPostRedisplay();
}
