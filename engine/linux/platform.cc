#include <stdexcept>

#include "platform.hh"
#include "font.hh"
#include "gl.hh"

void platform_start(int argc, char*argv[])
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Ortho test");

	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  initGL();

	glutMainLoop ();

}

#include <GL/glx.h>     // Header file fot the glx libraries.

/* function to build our font list */
void platform_buildFont()
{
  Display *dpy;          /* Our current X display */
  XFontStruct *fontInfo; /* Our font info */

  font_base = glGenLists( 96 );

  /* Get our current display long enough to get the fonts */
  dpy = XOpenDisplay( NULL );

  /* Get the font information */
  fontInfo = XLoadQueryFont( dpy, "-adobe-helvetica-medium-r-normal--14-*-*-*-p-*-iso8859-1" );

  /* If the above font didn't exist try one that should */
  if (fontInfo == NULL) {
    fontInfo = XLoadQueryFont( dpy, "fixed" );
    /* If that font doesn't exist, something is wrong */
    if ( fontInfo == NULL) {
      throw new std::runtime_error("no X font available?");
    }
  }

  glXUseXFont( fontInfo->fid, 32, 96, font_base );

  XFreeFont( dpy, fontInfo );

  XCloseDisplay( dpy );

  return;
}


