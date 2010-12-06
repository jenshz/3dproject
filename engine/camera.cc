#include "gl.hh"
#include "camera.hh"
#include <cmath>

void Camera::look()
{
  Vector3f eye;
  Vector3f up(0, 1, 0);

  float pitch = rotX * M_PI / 180.;
  float yaw = rotY * M_PI / 180.;
  

  eye = target - (Vector3f(cos(pitch) * cos(yaw), sin(yaw), sin(pitch) * cos(yaw)) * dist);

  gluLookAt(eye.v[0], eye.v[1], eye.v[2],
            target.v[0], target.v[1], target.v[2],
            up.v[0], up.v[1], up.v[2]);
}


Camera::~Camera()
{
}
