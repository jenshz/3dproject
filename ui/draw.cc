#include <GL/glut.h>
#include "draw.hh"

void frameRect(int x1, int y1, int x2, int y2)
{
  glBegin(GL_LINE_LOOP);
  glVertex2i(x1,y1);
  glVertex2i(x2,y1);
  glVertex2i(x2,y2);
  glVertex2i(x1-1,y2);
  glEnd();
}

void fillRect(int x1, int y1, int x2, int y2)
{
  glRecti(x1, y1, x2, y2);
}
