#ifndef _TEXTURE_HH_
#define _TEXTURE_HH_

#include <string>
#include "gl.hh"

class TextureDatabase {
public:
  
};

class Texture {
protected:
  Texture() {}
public:
  static Texture *loadTexture(const std::string &filename, bool mipmap = true);

  long unsigned int w, h;

  bool alpha;
  GLuint texid;

  void use();
};

#endif
