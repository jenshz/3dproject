#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <iostream>
#define RAD2DEG (180.0 / M_PI)
#define DEG2RAD (M_PI / 180.0)

// A represents a point in 2D space
struct Vector2f {
  float v[2];

  Vector2f() { v[0] = 0; v[1] = 0;}
  Vector2f(float mx, float my) {v[0] = mx; v[1] = my;}

  Vector2f& operator=(const Vector2f &p) {
    v[0] = p.v[0];
    v[1] = p.v[1];
    return *this;
  }

  Vector2f operator+(const Vector2f &p) {
    return Vector2f(v[0] + p.v[0], v[1] + p.v[1]);
  }

  Vector2f operator*(const float m) {
    return Vector2f(v[0] * m, v[1] * m);
  }

  Vector2f operator/(const float m) {
    return Vector2f(v[0] / m, v[1] / m);
  }
};


class Vector3f {
public:
	float v[3];

  Vector3f() {
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
  }

	Vector3f(float x, float y, float z) {
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}

	Vector3f cross(Vector3f o) {
		return Vector3f(v[1] * o.v[2] - v[2] * o.v[1],
										v[2] * o.v[0] - v[0] * o.v[2],
										v[0] * o.v[1] - v[1] * o.v[0]);
	}

	float length() {
		return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}

	Vector3f normalize() {
		float l = length();
		return Vector3f(v[0] / l, v[1] / l, v[2] / l);
	}

	float dot(Vector3f o) {
		return v[0] * o.v[0] + v[1] * o.v[1] + v[2] * o.v[2];
	}

	float angle(Vector3f o) {
		float d = dot(o);
		float l = length() * o.length();
		if (l == 0.0)
			return 0.0;
		if (d < 0) d = -d;
		return acos(d/l);
	}

	Vector3f operator-(Vector3f o) {
		return Vector3f(v[0] - o.v[0], v[1] - o.v[1], v[2] - o.v[2]);
	}

	Vector3f operator*(float s) {
		return Vector3f(v[0]*s, v[1]*s, v[2]*s);
	}

	void dump() {
		std::cout << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
	}
};

#endif
