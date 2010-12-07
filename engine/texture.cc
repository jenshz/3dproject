#include "texture.hh"
#include <iostream>
#include "gl.hh"
#include "pngload.hh"

Texture *Texture::loadTexture(const std::string &filename, bool mipmap) {
  Texture *tex = new Texture();

  glGenTextures(1, &tex->texid);
  glBindTexture(GL_TEXTURE_2D, tex->texid);

  unsigned char *image_data;

  if (pngLoad(filename.c_str(), &tex->w, &tex->h, &image_data, tex->alpha) == 1 && image_data) {
    if (mipmap) {
      if (tex->alpha)
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tex->w, tex->h, GL_RGBA, GL_UNSIGNED_BYTE, image_data); 
      else
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tex->w, tex->h, GL_RGB, GL_UNSIGNED_BYTE, image_data); 
    } else {
      if (tex->alpha)
        glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
      else
        glTexImage2D(GL_TEXTURE_2D, 0, 3, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    free(image_data);
  } else {
    std::cerr << "Failed to load image" << filename << std::endl;
    free(tex);
    return 0;
  }

  // Should these be configurable?
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (mipmap) {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  } else {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }

  return tex;
}

void Texture::use()
{
  glBindTexture(GL_TEXTURE_2D, texid);
}
