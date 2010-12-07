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

struct Point4f {
public:
  float v[4];

  Point4f() {
    v[0] = 0; v[1] = 0; v[2] = 0; v[3] = 0;
  }

  Point4f(float x, float y, float z, float t) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = t;
  }

  Point4f(const Point3f &p) {
    v[0] = p.v[0];
    v[1] = p.v[1];
    v[2] = p.v[2];
    v[3] = 1;
  }
};

#endif
