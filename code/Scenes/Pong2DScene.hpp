/// \file Pong2DScene.hpp
/// \brief Declaration of Pong2DScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef PONG_2D_SCENE_HPP
#define PONG_2D_SCENE_HPP

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
#include "Pong/AI.hpp"
#include "Pong/Player.hpp"
#include "Pong/Ball.hpp"

class Pong2DScene : public Scene
{
public:

  /// \brief Constructs a scene to keep main method clean.
  /// \param context A pointer to an object through which the Meshes and Scene will be able
  ///   to make OpenGL calls.
  /// \post A Scene has been created to make meshes.
  Pong2DScene (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram);

  ~Pong2DScene();

  /// \brief Copy constructor removed because you shouldn't be copying MyScenes.
  Pong2DScene (const Pong2DScene&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   MyScenes.
  void
  operator= (const Pong2DScene&) = delete;

  void 
  update (float deltaTime);

  void 
  processKeys (KeyBuffer* keyBuffer, float deltaTime);

  void
  resetCamera (Camera* camera);

private:
  unsigned int m_gamestate;
  Player* m_player;
  AI* m_player2;
  Ball* m_ball;
};

#endif//PONG_2D_SCENE_HPP