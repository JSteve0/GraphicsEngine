#version 330
/*
  Filename: PhongShader.frag
  Authors: Justin Stevens
  Course: CSCI375
  Assignment: A09Project
  Description: A fragment shader that uses phong shading.
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

// Transformation matrices, provided by C++ code.
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

// Eye position, in world space, provided by C++ code.
uniform vec3 uEyePosition;
uniform sampler2D uDiffuseSampler;
uniform int uHasTexture;

// First, the inputs from earlier in the pipeline
// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
// This color was already computed by interpolating the colors of the vertices
//   that define this fragment. (R, G, B)
in vec3 vColor;
in vec3 positionEye;
in vec3 normalEye;
in vec2 UV;
in mat4 inverseView;

// Second, the outputs the shader produces
// We output a color with an alpha channel (R, G, B, A)
out vec4 fColor;

// **

// Calculate diffuse and specular lighting for a single light.
vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal);

// **

void
main ()
{
  fColor = vec4(vColor, 1);

  // Iterate over all lights and calculate diffuse and specular contributions
  for (int i = 0; i < uNumLights; ++i)
  {
    fColor
        += vec4(calculateLighting (uLights[i], positionEye, normalEye), 1);
  }

  // Stay in bounds [0, 1], Output fragment color, with red, green, blue, and alpha components (RGBA)
  fColor = clamp (fColor, 0.0, 1.0);
}

vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal)
{
  // Light vector points toward the light
  vec3 lightVector;
  if (light.type == 0)
  { // Directional
    light.direction = vec3(inverseView * vec4(light.direction, 1));
    lightVector = normalize (-light.direction);
  }
  else
  { // Point or spot
    light.position = vec3(uView * vec4( light.position, 1));
    lightVector = normalize (light.position - vertexPosition);
  }
  // Light intensity is proportional to angle between light vector
  //   and vertex normal
  float lambertianCoef = max (dot (lightVector, vertexNormal), 0.0);
  vec3 diffuseAndSpecular = vec3 (0.0);
  if (lambertianCoef > 0.0)
  {
    // Light is incident on vertex, not shining on its edge or back
    vec3 diffuseColor;
    if (uHasTexture == 1)
    {
      diffuseColor = texture( uDiffuseSampler, UV ).rgb * light.diffuseIntensity;
    } else {
      diffuseColor = uDiffuseReflection * light.diffuseIntensity;
    }
    diffuseColor *= lambertianCoef;

    vec3 specularColor = uSpecularReflection * light.specularIntensity;
    // See how light reflects off of vertex
    vec3 reflectionVector = reflect (-lightVector, vertexNormal);
    // Compute view vector, which points toward the eye
    vec3 eyeVector = normalize (uEyePosition - vertexPosition);
    // Light intensity is proportional to angle between reflection vector
    //   and eye vector
    float specularCoef = max (dot (eyeVector, reflectionVector), 0.0);
    // Material's specular power determines size of bright spots
    specularColor *= pow (specularCoef, uSpecularPower);

    float attenuation = 1.0;
    if (light.type != 0)
    { // Non-directional, so light attenuates
      float distance = length (vertexPosition - light.position);
      attenuation = 1.0 / (light.attenuationCoefficients.x
          + light.attenuationCoefficients.y * distance
          + light.attenuationCoefficients.z * distance * distance);
    }
    float spotFactor = 1.0f;
    if (light.type == 2)
    { // Spot light
      light.direction = vec3(inverseView * vec4(light.direction, 1));
      float cosTheta = dot (-lightVector, light.direction);
      cosTheta = max (cosTheta, 0.0f);
      spotFactor = (cosTheta >= light.cutoffCosAngle) ? cosTheta : 0.0f;
      spotFactor = pow (spotFactor, light.falloff);
    }
    diffuseAndSpecular = spotFactor * attenuation * (diffuseColor
        + specularColor);
  }

  return diffuseAndSpecular;
}