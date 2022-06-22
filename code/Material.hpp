/// \file Material.hpp
/// \brief Declaration of Mesh class and any associated global functions.
/// \author ustin Stevens & Aaron Katz
/// \version A09

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Vector3.hpp"
#include "ShaderProgram.hpp"

class Material
{
public: 

  Material();

  Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 emmissiveIntensity, float specularPower);

  ~Material ();

  void
  setUniforms(ShaderProgram* shader);

  void
  setToGold();

  Vector3 m_ambient;

  Vector3 m_diffuse;

  Vector3 m_specular;

  Vector3 m_emmissiveIntensity;

  float m_specularPower;

};

#endif//MATERIAL_HPP