#include <GL/gl.h>
#include <vector>

#include "platform.hh"
#include "gl.hh"
#include "ui.hh"

std::vector<Shape*> objects;

void initGL()
{
	glClearColor (0., 0., 0., 0.);
	glShadeModel (GL_FLAT);
  platform_buildFont();

  ui.init();
}


void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  ui.reshape(w, h);
}

void display (void) {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f (1.,1.,1.);

	glMatrixMode(GL_PROJECTION);
  glPushMatrix();
	glLoadIdentity();
	glOrtho(0, ui.w, ui.h, 0, -1, 1);

	glMatrixMode (GL_MODELVIEW);

  for (std::vector<Shape*>::iterator it = objects.begin(); it != objects.end(); it++) {
    (*it)->draw();
  }

	glMatrixMode (GL_PROJECTION);
  glPopMatrix();

	glMatrixMode (GL_MODELVIEW);


  ui.draw();

  glutSwapBuffers();
}

void motion(int x, int y)
{
  ui.motion(x,y);
}

void mouse(int button, int state, int x, int y)
{
  switch(state) {
  case GLUT_UP:
    ui.mouseUp(button, x, y);
    break;
  case GLUT_DOWN:
    ui.mouseDown(button, x, y);
    break;
  }
}
