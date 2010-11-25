#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <GL/glut.h>

#include "font.hh"

GLuint  font_base;

void KillFont()
{
    glDeleteLists( font_base, 96 );

    return;
}

// function to release/destroy our resources and restoring the old desktop
static void Quit( int returnCode )
{
    KillFont();

    exit( returnCode );
}

// Print our GL text to the screen
GLvoid glPrint(const char *fmt, ... )
{
  char text[256];
  va_list ap;

  if ( fmt == NULL )
    return;

  va_start( ap, fmt );
  vsprintf( text, fmt, ap );
  va_end( ap );

  glPushAttrib(GL_LIST_BIT);

  glListBase(font_base - 32);

  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text );

  glPopAttrib( );
}
