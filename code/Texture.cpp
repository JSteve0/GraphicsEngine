/// \file Texture.cpp
/// \brief Declaration of texture class and any associated global functions.
/// \author Aaron Katz & Justin Stevens
/// \version A09

#include "Texture.hpp"


Texture::Texture(std::string filename)
{
  FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename.c_str(), 0), filename.c_str());
  FIBITMAP* output = FreeImage_ConvertTo24Bits(image);
  
  m_data = FreeImage_GetBits(output);
  m_width = FreeImage_GetWidth(output);
	m_height = FreeImage_GetHeight(output);
}

void
Texture::loadTextureID(GLuint &textureID)
{
  glGenTextures (1, &textureID);
  glBindTexture (GL_TEXTURE_2D, textureID);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, m_data);
  glGenerateMipmap (GL_TEXTURE_2D);
}

Texture::~Texture()
{
    
}