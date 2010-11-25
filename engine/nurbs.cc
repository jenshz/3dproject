#include <GL/glut.h>
#include "nurbs.hh"
#include "gl.hh"

Nurbs::Nurbs()
{
  objects.push_back(this);
}

Point2D deBoor(int k,int degree, int i, double x, const double* knots, const Point2D *ctrlPoints)
{
	if( k == 0) {
		return ctrlPoints[i];
	} else
	{
		double alpha = (x-knots[i])/(knots[i+degree+1-k]-knots[i]);
		return (deBoor(k-1,degree, i-1, x, knots, ctrlPoints)*(1-alpha )+deBoor(k-1,degree, i, x, knots, ctrlPoints)*alpha);
	}
}

static int WhichInterval(double x, const double *knot, int ti)
{
  for(int i=1;i<ti-1;i++) {
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
               (1-t0)*(1-t0)*(1-t0)*p[0].y + 3*(1-t0)*(1-t0)*t0*p[1].y + 3*(1-t0)*t0*t0*p[2].y 
               + t0*t0*t0*p[3].y);
    glVertex2f((1-t1)*(1-t1)*(1-t1)*p[0].x + 3*(1-t1)*(1-t1)*t1*p[1].x + 3*(1-t1)*t1*t1*p[2].x 
               + t1*t1*t1*p[3].x,
               (1-t1)*(1-t1)*(1-t1)*p[0].y + 3*(1-t1)*(1-t1)*t1*p[1].y + 3*(1-t1)*t1*t1*p[2].y 
               + t1*t1*t1*p[3].y);
    glEnd();
  }
  */


void Nurbs::draw()
{
  int deg = 4;

  Point2D p[shapes.size()+deg*2-2];

  for (int i = 0; i < shapes.size(); i++) {
    p[deg+i-1].x = shapes[i]->x;
    p[deg+i-1].y = shapes[i]->y;
  }

  double knots[shapes.size() + deg*2-1];

  for (int i = 0; i < deg-1; i++) {
    p[deg-2-i] = p[3];
    p[deg+shapes.size()+i-1] = p[deg+shapes.size()+i-2];
  }

  for (int i = 0; i < deg; i++) {
    knots[i] = 0;
    knots[deg+shapes.size()+i] = shapes.size();
  }

  for (int i = 0; i < shapes.size(); i++) {
    knots[deg+i] = i;
  }

  Point2D last;
  int cnt = 100;

  for (int i = 0; i <= cnt; i++) {
    float t = (double)i/cnt * shapes.size();

    Point2D now = deBoor(deg, deg, WhichInterval(t, knots, shapes.size() + deg*2-2), t, knots, p);

    if (i > 0) {
      glBegin(GL_LINES);
      glVertex2d(last.x, last.y);
      glVertex2d(now.x, now.y);
      glEnd();
    }

    last = now;
  }
}

void Nurbs::addPoint(Point2D *w)
{
  shapes.push_back(w);
}


