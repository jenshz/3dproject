#ifndef _NURBS_HH_
#define _NURBS_HH_

#include <vector>
#include "vector.hh"

class Nurbs : public Shape
{
private:
  std::vector<Point2f*> shapes;

public:
  Nurbs();

  void addPoint(Point2f *p);

  void draw();
};


#endif
