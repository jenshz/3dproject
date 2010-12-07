#include "gl.hh"
#include "engine.hh"

Scene scene;

void Scene::draw(bool select)
{
  // Set camera position
  camera.look();

  // Enable lights, etc.
  if (!select) {
    glColor3f(1., 1., 1.);

  }

  // Draw all scene objects
  for (std::vector<SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
    (*it)->draw(select);
  }
}

#define BUFSIZE 512

void Scene::select(int x, int y)
{
  GLuint selectBuf[BUFSIZE];
  GLint hits;
  GLint viewport[4];

  glGetIntegerv (GL_VIEWPORT, viewport);

  glSelectBuffer (BUFSIZE, selectBuf);
  (void) glRenderMode (GL_SELECT);

  glInitNames();
  glPushName(0);

  glMatrixMode (GL_PROJECTION);
  glPushMatrix ();
  glLoadIdentity ();
  /*  create 2x2 pixel picking region near cursor location        */
  gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                 5.0, 5.0, viewport);

	gluPerspective(45.0f,(GLfloat)viewport[2]/(GLfloat)viewport[3],0.1f,100.0f);

  //  glMatrixMode(GL_MODELVIEW);
  //  gluOrtho2D (0.0, 3.0, 0.0, 3.0);
  draw(true);

  glMatrixMode (GL_PROJECTION);
  glPopMatrix ();
  glFlush ();

  hits = glRenderMode (GL_RENDER);

  GLuint hit = 0;
  
  if (hits > 0) {
    GLuint *ptr = (GLuint*)selectBuf;
    GLuint names = ptr[0];
    if (names > 0) {
      hit = ptr[3];
    }
  }

  glMatrixMode(GL_MODELVIEW);
  
  selected = 0;
  if (hit > 0) {
    // Find the one that was selected (this may be optimized)
    for (std::vector<SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
      if ((*it)->id == hit) {
        selected = *it;
        break;
      }
    }
  }

  try {
    if (selected) {
      if (selected->onClick && luabind::type(selected->onClick) == LUA_TFUNCTION) {
        selected->onClick(boost::ref(*selected));
      }
    } else {
      if (onDeselect && luabind::type(onDeselect) == LUA_TFUNCTION) {
        onDeselect();
      }
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << ":" << std::endl << lua_tostring(lua, -1) << std::endl;
  }
}

bool Scene::motion(int x, int y)
{
  if (down) {
    camera.rotX += (x - dx) / 10.0;
    camera.rotY -= (y - dy) / 10.0;
    if (camera.rotY >= 90) {
      camera.rotY = 90.;
    }
    if (camera.rotY <= -90) {
      camera.rotY = -90.;
    }
    dx = x;
    dy = y;
    glutPostRedisplay();
  }

  return false;
}

bool Scene::mouseDown(int button, int x, int y)
{
  dx = x;
  dy = y;
  if (button == 2) {
    down = true;
  } else if (button == 0) {
    select(x,y);
    glutPostRedisplay();
  }

  return false;
}

bool Scene::mouseUp(int button, int x, int y)
{
  down = false;
  return false;
}

void Scene::add(SceneObject *obj)
{
  objects.push_back(obj);
}

Camera &Scene::getCamera()
{
  return camera;
}

Scene &Scene::get()
{
  return scene;
}
