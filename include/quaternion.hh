#ifndef _QUARTERNION_HH_
#define _QUARTERNION_HH_

/*
 * This code has been borrowed from the NeHe site: nehe.gamedev.net (Vic Hollis)
 */

#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library
#include <math.h>

#define PI			3.14159265358979323846

class Quaternion  
{
public:
	Quaternion operator *(Quaternion q);
	void CreateMatrix(GLfloat *pMatrix);
	void CreateFromAxisAngle(GLfloat x, GLfloat y, GLfloat z, GLfloat degrees);
	Quaternion();
	virtual ~Quaternion();

private:
	GLfloat m_w;
	GLfloat m_z;
	GLfloat m_y;
	GLfloat m_x;
};

#endif
