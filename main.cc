#ifdef _WIN32
#include <Windows.h>
#endif


#include <GL/glut.h>
#include "platform.hh"
#include "lua.hh"
#include "gl.hh"
#include "engine.hh"

void myExit()
{
  cleanup_lua();
}

static void test_main()
{
  /*  SceneObject *o = new SceneObject(MQuad);
  o->vertices.push_back(Point3f(-3.,  0,   3));
  o->vertices.push_back(Point3f( 3.,  0.,  3));
  o->vertices.push_back(Point3f( 3.,  0., -3));
  o->vertices.push_back(Point3f(-3.,  0., -3));

  scene.objects.push_back(o); */
}
	
void glut_init(int argc, char*argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize (640, 480);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Ortho test");

  //  glutIdleFunc(display);
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);

  initGL();

  test_main();

  glutMainLoop ();
}

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main(int argc, char *argv[])
{
  register_lua(argc, argv);
 
  atexit(myExit);

  glut_init(argc, argv);

  return 0;
}





