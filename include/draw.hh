#ifndef _DRAW_HH_
#define _DRAW_HH_

#include <vector>

void frameRect(int x1, int y1, int x2, int y2);
void fillRect(int x1, int y1, int x2, int y2);

class Shape {
public:
  virtual void draw() = 0;
};

#endif
