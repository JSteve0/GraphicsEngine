#version 330

/*
  Filename: PhongShader.vert
  Authors: Justin Stevens
  Course: CSCI375
  Assignment: A09Project
  Description: A vertex shader that demonstrates how up to 8 light sources of a
    variety of types could be provided.
*/

// By default, all float variables will use high precision.
precision highp float;

// The C++ code will tell us how many light sources there are (maximum 8).
uniform int uNumLights;

// Information about one light source.
// Because different light sources store different information, not every type
//   will use every data member.
struct Light
{
  // 0 if directional, 1 if point, 2 if spot -- other values illegal.
  int type;

  // All lights have these parameters.
  vec3 diffuseIntensity;
  vec3 specularIntensity;

  // Point and spot light parameters.
  vec3 position;
  vec3 attenuationCoefficients;

  // Directional and spot light parameter.
  vec3 direction;

  // Spot light parameters.
  float cutoffCosAngle;
  float falloff;
};

// An array of lights that will be filled by the C++ code.
const int MAX_LIGHTS = 8;
uniform Light uLights[MAX_LIGHTS];

// Single ambient light, provided by the C++ code.
uniform vec3  uAmbientIntensity;

// Material properties, provided by the C++ code.
uniform vec3  uAmbientReflection;
uniform vec3  uDiffuseReflection;
uniform vec3  uSpecularReflection;
uniform float uSpecularPower;
uniform vec3  uEmissiveIntensity;

// Inputs from the VBO.
in vec3 aPosition;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aUV; 

// Output to the fragment shader.
out vec3 vColor;
out vec3 positionEye;
out vec3 normalEye;
out vec2 UV;
out mat4 inverseView;

// Transformation matrices, provided by C++ code.
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

// Eye position, in world space, provided by C++ code.
uniform vec3 uEyePosition;
uniform bool uHasTexture;

void
main (void)
{
  mat4 worldViewProjection = uProjection * uView * uWorld;
  // Transform vertex into clip space
  gl_Position = worldViewProjection * vec4 (aPosition, 1);
  // Transform vertex into eye space for lighting
  positionEye = vec3 (uView * uWorld * vec4 (aPosition, 1));

  // Do calculation in eye space.
  mat3 normalTransform = mat3 (uView * uWorld);
  normalTransform = transpose (inverse (normalTransform));
  // Normal matrix is eye inverse transpose
  normalEye = normalize (normalTransform * aNormal);

  // Handle ambient and emissive light
  //   It's independent of any particular light
  vColor = uAmbientReflection * uAmbientIntensity
      + uEmissiveIntensity;

  // Stay in bounds [0, 1]
  vColor = clamp (vColor, 0.0, 1.0);

  inverseView = transpose (inverse (uView));
  UV = aUV;
}