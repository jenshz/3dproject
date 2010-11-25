#ifndef _GL_HH_
#define _GL_HH_

#include <vector>
#include "draw.hh"

void initGL();

void reshape(int w, int h);

void display();

void motion(int x, int y);

void mouse(int button, int state, int x, int y);

extern std::vector<Shape*> objects;

#endif
