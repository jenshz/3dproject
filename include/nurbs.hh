#ifndef _NURBS_HH_
#define _NURBS_HH_

#include <vector>
#include "draw.hh"
#include "point.hh"

class Nurbs : public Shape
{
private:
  std::vector<Point2D*> shapes;

public:
  Nurbs();

  void addPoint(Point2D *p);

  void draw();
};


#endif
