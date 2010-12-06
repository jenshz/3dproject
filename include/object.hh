#ifndef _OBJECT_HH_
#define _OBJECT_HH_

#include <vector>
#include <iostream>
#include "lua.hh"
#include "point.hh"

class Texture;

enum ObjectType {
  MQuad = 0,
  MCube = 1,
  MSphere = 2,
  MObject = 3
};


class SceneObject {
private:
  int type;
  bool textured;
public:
  SceneObject(int mtype)
    : type(mtype), color(1,1,1), scale(1,1,1), textured(false), id(0) {}
  virtual ~SceneObject() {
    std::cerr << "~SceneObject()" << std::endl;
  }

  void draw(bool select);

  Texture *texture;
  std::vector<Point2f> texcoords;
  std::vector<Point3f> vertices;

  Point3f pos;
  Point3f color;
  Point3f scale;

  int id;
  static SceneObject *createQuad();

  luabind::object onClick;
};


class Skybox {
public:
  
};

#endif
