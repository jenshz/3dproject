#ifndef _GL_HH_
#define _GL_HH_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/glut.h>


#include <vector>
#include "draw.hh"

void initGL();

void reshape(int w, int h);

void display();

void motion(int x, int y);

void mouse(int button, int state, int x, int y);

void keyboard(unsigned char key, int x, int y);

extern std::vector<Shape*> objects;


class Screen {
public:
	static void toggleFullScreen();

	static void setSize(int width, int height);

	static int getWidth();
	static int getHeight();
};

#endif
