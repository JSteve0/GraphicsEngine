/// \file MyScene.hpp
/// \brief Declaration of MyScene class and any associated global functions.
/// \author Justin Stevens & Aaron Katz 
/// \version A09

#ifndef MYSCENE_HPP
#define MYSCENE_HPP

#include "Scene.hpp"
#include "../ColorsMesh.hpp"
#include "../NormalsMesh.hpp"
#include "../Geometry.hpp"
#include "../ShaderProgram.hpp"
#include "../LightSource.hpp"
#include "../Material.hpp"
#include "../Texture.hpp"
#include "../TexturedNormalsMesh.hpp"
#include "../KeyBuffer.hpp"
#include "../Camera.hpp"

class MyScene : public Scene
{
public:

  /// \brief Constructs a scene to keep main method clean.
  /// \param context A pointer to an object through which the Meshes and Scene will be able
  ///   to make OpenGL calls.
  /// \post A Scene has been created to make meshes.
  MyScene (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram);

  ~MyScene();

  /// \brief Copy constructor removed because you shouldn't be copying MyScenes.
  MyScene (const MyScene&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   MyScenes.
  void
  operator= (const MyScene&) = delete;

  void 
  update (float deltaTime);

  void 
  processKeys (KeyBuffer* keyBuffer, float deltaTime);

  void 
  resetCamera (Camera* camera);
};

#endif//MYSCENE_HPP