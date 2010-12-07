#ifdef _WIN32
#include <Windows.h>
#endif


#include <GL/glut.h>
#include "platform.hh"
#include "lua.hh"
#include "gl.hh"
#include "engine.hh"

static void test_main()
{
  /*
  SceneObject *o = new SceneObject(MQuad);
  o->vertices.push_back(Point3f(-3.,  0,   3));
  o->vertices.push_back(Point3f( 3.,  0.,  3));
  o->vertices.push_back(Point3f( 3.,  0., -3));
  o->vertices.push_back(Point3f(-3.,  0., -3));

  scene.objects.push_back(o);
  Texture *tex = Texture::loadTexture("jens.png");

  o->texcoords.push_back(Point2f(0, 1));
  o->texcoords.push_back(Point2f(1, 1));
  o->texcoords.push_back(Point2f(1, 0));
  o->texcoords.push_back(Point2f(0, 0));

  o->texture = tex;
  o->textured = true;
  */
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
 
  glut_init(argc, argv);

  cleanup_lua();
  return 0;
}





