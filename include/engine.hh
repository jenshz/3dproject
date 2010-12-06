#ifndef _ENGINE_HH_
#define _ENGINE_HH_

#include "object.hh"
#include "camera.hh"

class Scene {
public:
  Scene() : down(false), dx(0), dy(0), selected(0) {
  }

  std::vector<SceneObject*> objects;
  Camera camera;

  void draw(bool select = false);

  bool motion(int x, int y);
  bool mouseDown(int button, int x, int y);
  bool mouseUp(int button, int x, int y);

  void select(int x, int y);

  bool down;
  int dx, dy;

  void add(SceneObject *obj);
  Camera &getCamera();

  SceneObject *selected;

  luabind::object onDeselect;

  static Scene &get();
};

extern Scene scene;

#endif
