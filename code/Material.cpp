/// \file Material.cpp
/// \brief Declaration of Mesh class and any associated global functions.
/// \author ustin Stevens & Aaron Katz
/// \version A09

#include "Material.hpp"

Material::Material(){

}

Material::Material (Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 emmissiveIntensity, float specularPower)
    : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_emmissiveIntensity(emmissiveIntensity), m_specularPower(specularPower)
{

}

Material::~Material(){

}

void
Material::setUniforms(ShaderProgram* shader){
    shader->setUniformVector("uAmbientReflection", m_ambient);
    shader->setUniformVector("uDiffuseReflection", m_diffuse);
    shader->setUniformVector("uSpecularReflection", m_specular);
    shader->setUniformFloat("uSpecularPower", m_specularPower);
    shader->setUniformVector("uEmissiveIntensity", m_emmissiveIntensity);
}

void
Material::setToGold()
{
  //gold	0.24725	0.1995	0.0745	0.75164	0.60648	0.22648	0.628281	0.555802	0.366065	0.4
  m_ambient = Vector3(0.24725f, 0.1995f, 0.0745f);
  m_diffuse = Vector3(0.75164f,	0.60648f,	0.22648f);
  m_specular = Vector3(0.628281f,	0.555802f, 0.366065f);
  m_emmissiveIntensity = Vector3(0.1f, 0.1f, 0.1f); //Undefined by website
  m_specularPower = 0.4f;
}
    
