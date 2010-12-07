#include "gl.hh"
#include "point.hh"
#include "nurbs.hh"

#include <iostream>

Nurbs::Nurbs()
{
  //  objects.push_back(this);
}

Vector2f deBoor(int k,int degree, int i, double x, std::vector<double> &knots, std::vector<Vector2f> &ctrlPoints)
{
	if ((i < 0) || (i >= ctrlPoints.size()))
		return Vector2f();
	if( k == 0) {
		return ctrlPoints[i];
	} else
	{
		float alpha = (x-knots[i])/(knots[i+degree+1-k]-knots[i]);
		return (deBoor(k-1,degree, i-1, x, knots, ctrlPoints)*(1-alpha )+deBoor(k-1,degree, i, x, knots, ctrlPoints)*alpha);
	}
}

static int WhichInterval(double x, std::vector<double> &knot, int ti)
{
  for(unsigned int i=1;i<knot.size()-1;i++) {
    if(x<knot[i])
      return(i-1);
    else if(x == knot[ti-1])
      return(ti-1);
  }
  return -1;
}

  /*
    bezier curves:
  for (int i = 1; i <= 100; i++) {
    float t0 = (i-1)/100.0;
    float t1 = i/100.0;

    glBegin(GL_LINES);
    glVertex2f((1-t0)*(1-t0)*(1-t0)*p[0].x + 3*(1-t0)*(1-t0)*t0*p[1].x + 3*(1-t0)*t0*t0*p[2].x 
               + t0*t0*t0*p[3].x,
               (1-t0)*(1-t0)*(1-t0)*p[0].v[1] + 3*(1-t0)*(1-t0)*t0*p[1].v[1] + 3*(1-t0)*t0*t0*p[2].v[1] 
               + t0*t0*t0*p[3].v[1]);
    glVertex2f((1-t1)*(1-t1)*(1-t1)*p[0].x + 3*(1-t1)*(1-t1)*t1*p[1].x + 3*(1-t1)*t1*t1*p[2].x 
               + t1*t1*t1*p[3].x,
               (1-t1)*(1-t1)*(1-t1)*p[0].v[1] + 3*(1-t1)*(1-t1)*t1*p[1].v[1] + 3*(1-t1)*t1*t1*p[2].v[1] 
               + t1*t1*t1*p[3].v[1]);
    glEnd();
  }
  */


void Nurbs::draw()
{
  int deg = 4;
 
  std::vector<Vector2f> p(shapes.size()+deg*2-2);

  for (unsigned int i = 0; i < shapes.size(); i++) {
    p[deg+i-1].v[0] = shapes[i]->v[0];
    p[deg+i-1].v[1] = shapes[i]->v[1];
  }

  std::vector<double> knots(shapes.size() + deg*2-1);

  for (int i = 0; i < deg-1; i++) {
    p[deg-2-i] = p[3];
    p[deg+shapes.size()+i-1] = p[deg+shapes.size()+i-2];
  }

  for (int i = 0; i < deg-1; i++) {
    knots[i] = 0;
    knots[deg+shapes.size()+i] = shapes.size();
  }

  for (unsigned int i = 0; i < shapes.size(); i++) {
    knots[deg+i] = i;
  }

  Vector2f last;
  int cnt = 100;

  for (int i = 0; i <= cnt; i++) {
    float t = (double)i/cnt * shapes.size();

	Vector2f now = deBoor(deg, deg, WhichInterval(t, knots, shapes.size() + deg*2-2), t, knots, p);

    if (i > 0) {
      glBegin(GL_LINES);
      glVertex2d(last.v[0], last.v[1]);
      glVertex2d(now.v[0], now.v[1]);
      glEnd();
    }

    last = now;
  }

}

void Nurbs::addPoint(Point2f *w)
{
  shapes.push_back(w);
}


