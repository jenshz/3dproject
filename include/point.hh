#ifndef _POINT_HH_
#define _POINT_HH_

struct Point2f {
public:
  float v[2];

  Point2f() {
    v[0] = 0; v[1] = 0; v[2] = 0;
  }

  Point2f(float x, float y) {
    v[0] = x;
    v[1] = y;
  }
};

struct Point3f {
public:
  float v[3];

  Point3f() {
    v[0] = 0; v[1] = 0; v[2] = 0;
  }

  Point3f(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }
};

#endif
