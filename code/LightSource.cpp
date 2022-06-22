/// \file LightSource.cpp
/// \brief Implementation of classes for light sources.
/// \author Justin Stevens
/// \version A09

#include "LightSource.hpp"

LightSource::LightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity)
  : m_diffuseIntensity(diffuseIntensity), 
    m_specularIntensity(specularIntensity)
{

}

LightSource::~LightSource ()
{

}

void 
LightSource::setUniforms (ShaderProgram* program, int lightNum)
{
  std::string light = "uLights[" + std::to_string(lightNum);
  light += "]";
  program->setUniformVector(light + ".diffuseIntensity", m_diffuseIntensity);
  program->setUniformVector(light + ".specularIntensity", m_specularIntensity);
}


DirectionalLightSource::DirectionalLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& direction)
  : LightSource::LightSource(diffuseIntensity, specularIntensity), 
    m_direction(direction)
{

}

DirectionalLightSource::~DirectionalLightSource ()
{

}

void 
DirectionalLightSource::setUniforms (ShaderProgram* program, int lightNum)
{
  LightSource::setUniforms(program, lightNum);
  std::string light = "uLights[" + std::to_string(lightNum);
  light += "]";
  program->setUniformVector(light + ".direction", m_direction);
  program->setUniformInt(light + ".type", LightType(DIRECTIONAL));
}


LocationLightSource::LocationLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients)
  : LightSource::LightSource(diffuseIntensity, specularIntensity),
    m_position(position),
    m_attenuationCoefficients(attenuationCoefficients)
{

}

LocationLightSource::~LocationLightSource ()
{

}

void 
LocationLightSource::setUniforms (ShaderProgram* program, int lightNum)
{
  LightSource::setUniforms(program, lightNum);
  std::string light = "uLights[" + std::to_string(lightNum);
  light += "]";
  program->setUniformVector(light + ".position", m_position);
  program->setUniformVector(light + ".attenuationCoefficients", m_attenuationCoefficients);
}



PointLightSource::PointLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients)
  : LocationLightSource::LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients)
{

}

PointLightSource::~PointLightSource ()
{

}

void 
PointLightSource::setUniforms (ShaderProgram* program, int lightNum)
{
  LocationLightSource::setUniforms(program, lightNum);
  std::string light = "uLights[" + std::to_string(lightNum);
  light += "]";
  program->setUniformInt(light + ".type", LightType(POINT));
}

SpotLightSource::SpotLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients, const Vector3& direction, float cutoffCosAngle, float falloff)
  : LocationLightSource::LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients),
    m_direction(direction),
    m_cutoffCosAngle(cutoffCosAngle),
    m_falloff(falloff)
{

}

SpotLightSource::~SpotLightSource ()
{

}

void 
SpotLightSource::setUniforms (ShaderProgram* program, int lightNum)
{
  LocationLightSource::setUniforms(program, lightNum);
  std::string light = "uLights[" + std::to_string(lightNum);
  light += "]";
  program->setUniformVector(light + ".direction", m_direction);
  program->setUniformFloat(light + ".cutoffCosAngle", m_cutoffCosAngle);
  program->setUniformFloat(light + ".falloff", m_falloff);
  program->setUniformInt(light + ".type", LightType(SPOT));
}