#include <vector>
#include <iostream>

#include "platform.hh"
#include "gl.hh"
#include "ui.hh"
#include "engine.hh"

namespace app {
	int width, height;
	int oldWidth = 0, oldHeight = 0;
	int oldX, oldY;
	bool fullScreen = false;
}

void initGL()
{
	glClearColor (0., 0., 0., 0.);
	glShadeModel (GL_FLAT);
  glEnable(GL_DEPTH_TEST);
	platform_buildFont();
	ui.init();
}


void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  app::width = w;
  app::height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

  ui.reshape(w, h);
}

void display (void) {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f (1.,1.,1.);

	glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();

  scene.draw();

	glMatrixMode(GL_PROJECTION);
  glPushMatrix();
	glLoadIdentity();
  glOrtho(0, ui.w, ui.h, 0, -1, 1);

	glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  ui.draw();

	glMatrixMode (GL_PROJECTION);
  glPopMatrix();

  glutSwapBuffers();
}

void motion(int x, int y)
{
  if (!ui.motion(x,y)) {
    scene.motion(x, y);
  }
}

void mouse(int button, int state, int x, int y)
{
  switch(state) {
  case GLUT_UP:
    if (!ui.mouseUp(button, x, y)) {
      scene.mouseUp(button, x, y);
    }
    break;
  case GLUT_DOWN:
    if (!ui.mouseDown(button, x, y)) {
      scene.mouseDown(button, x, y);
    }
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
	ui.keyDown(key);
}

int Screen::getWidth()
{
	return app::width;
}

int Screen::getHeight()
{
	return app::height;
}

void Screen::setSize(int w, int h)
{
	glutReshapeWindow(w, h);
}

void Screen::toggleFullScreen()
{
	using namespace app;
	if (fullScreen) {
		glutPositionWindow(oldX, oldY);
		glutReshapeWindow(oldWidth, oldHeight);
	} else {
		oldX = glutGet(GLUT_WINDOW_X);
		oldY = glutGet(GLUT_WINDOW_Y);
                    
		oldWidth = width;
		oldHeight = height;
		glutFullScreen();
	}

	fullScreen = !fullScreen;
}
