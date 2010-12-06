#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gl.hh"

#include "quaternion.hh"
#include "point.hh"
#include "vector.hh"

class Camera  
{
public:
  float dist;
  float rotX;
  float rotY;

  Vector3f target;

	Camera() : rotX(90), rotY(0), dist(10) {
  }

	virtual ~Camera();

  void look();
};

#endif
