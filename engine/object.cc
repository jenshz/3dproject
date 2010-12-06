#include "gl.hh"
#include "object.hh"
#include <iostream>


static void draw_quad(SceneObject *o)
{
  glColor3fv(o->color.v);

  glBegin(GL_QUADS);
  for (std::vector<Point3f>::iterator it = o->vertices.begin(); it != o->vertices.end(); it++) {
    glVertex3fv(it->v);
  }
  glEnd();
}

static void draw_cube(SceneObject *o)
{
  
}

static void draw_sphere(SceneObject *o)
{
  
}

static void draw_object(SceneObject *o)
{
  
}

void SceneObject::draw(bool select)
{
  // Translate to the correct position
  glPushMatrix();
  glTranslatef(pos.v[0], pos.v[1], pos.v[2]);
  glScalef(scale.v[0], scale.v[1], scale.v[2]);

  if (select && id > 0) {
    glLoadName(id);
  }

  // Paint
  switch(type) {
  case MQuad:
    draw_quad(this);
    break;
  case MCube:
    draw_cube(this);
    break;
  case MSphere:
    draw_sphere(this);
    break;
  case MObject:
    draw_object(this);
    break;
  }

  // Restore view
  glPopMatrix();
}

SceneObject *SceneObject::createQuad()
{
  SceneObject *o = new SceneObject(MQuad);
  o->vertices.push_back(Point3f(-1.,  0,   1));
  o->vertices.push_back(Point3f( 1.,  0.,  1));
  o->vertices.push_back(Point3f( 1.,  0., -1));
  o->vertices.push_back(Point3f(-1.,  0., -1));
  return o;
}

