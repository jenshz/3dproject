#ifndef _FONT_HH_
#define _FONT_HH_

#ifdef _WIN32
#include <Windows.h>
#endif


#include <GL/gl.h>

void buildFont();
void glPrint(const char *fmt, ... );

extern GLuint  font_base;


#endif
