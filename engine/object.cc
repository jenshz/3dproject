#include "gl.hh"
#include "object.hh"
#include <iostream>


static void draw_quad(SceneObject *o)
{
  if (o->textured) {
    // Check if the texture coordinates are there
    if (o->texcoords.size() < 4)
      return;

    glColor4f(1,1,1,1);

    if (o->texture->alpha) {
      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glEnable(GL_TEXTURE_2D);
    o->texture->use();
  } else {

    if (o->color.v[3] < 1) {
      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glColor4fv(o->color.v);
  }

  glBegin(GL_QUADS);
  for (std::vector<Point3f>::iterator it = o->vertices.begin(); it != o->vertices.end(); it++) {
    if (o->textured) {
      Point2f &p = o->texcoords[it - o->vertices.begin()];
      glTexCoord2f(p.v[0], p.v[1]);
    }
    glVertex3fv(it->v);
  }
  glEnd();

  if (o->textured) {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
  }
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
  if (select && id > 0) {
    glPushName(id);
  } else if (select) {
    return;
  }

  // Translate to the correct position
  glPushMatrix();
  glTranslatef(pos.v[0], pos.v[1], pos.v[2]);
  glScalef(scale.v[0], scale.v[1], scale.v[2]);

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

  if (select && id > 0) {
    glPopName();
  }
}

SceneObject *SceneObject::createQuad()
{
  SceneObject *o = new SceneObject(MQuad);
  o->vertices.push_back(Point3f(-1.,  0,   1));
  o->vertices.push_back(Point3f( 1.,  0.,  1));
  o->vertices.push_back(Point3f( 1.,  0., -1));
  o->vertices.push_back(Point3f(-1.,  0., -1));
  o->texcoords.push_back(Point2f(0, 1));
  o->texcoords.push_back(Point2f(1, 1));
  o->texcoords.push_back(Point2f(1, 0));
  o->texcoords.push_back(Point2f(0, 0));
  return o;
}

