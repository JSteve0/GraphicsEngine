/// \file Texture.cpp
/// \brief Declaration of texture class and any associated global functions.
/// \author Aaron Katz & Justin Stevens
/// \version A09

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "OpenGLContext.hpp"
#include <FreeImagePlus.h>
#include <string>

class Texture
{
public:

  Texture(std::string filename);

  void
  loadTextureID(GLuint &textureID);

  ~Texture();

private: 
  BYTE* m_data;
  GLuint m_height;
  GLuint m_width;
};

#endif//TEXTURE_HPP