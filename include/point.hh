#ifndef _POINT_HH_
#define _POINT_HH_

// A represents a point in 2D space
struct Point2D {
  double x, y;

  Point2D() : x(0), y(0) {}
  Point2D(double mx, double my) : x(mx), y(my) {}

  Point2D operator=(const Point2D &p) {
    x = p.x;
    y = p.y;
  }

  Point2D operator+(const Point2D &p) {
    return Point2D(x + p.x, y + p.y);
  }

  Point2D operator*(const double m) {
    return Point2D(x * m, y * m);
  }

  Point2D operator/(const double m) {
    return Point2D(x / m, y / m);
  }
};

#endif
