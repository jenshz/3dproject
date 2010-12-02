#ifdef _WIN32
#include <Windows.h>
#endif


#include <GL/glut.h>
#include "platform.hh"
#include "lua.hh"
#include "gl.hh"

void myExit()
{
  cleanup_lua();
}
	
void glut_init(int argc, char*argv[])
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
  glutKeyboardFunc(keyboard);

  initGL();

  glutMainLoop ();
}

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main(int argc, char *argv[])
{
/*  int argc = 1;
  char *argv[] = {""}; */

  register_lua(argc, argv);
 
  atexit(myExit);

  glut_init(argc, argv);

  return 0;
}





