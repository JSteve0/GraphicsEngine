/// \file Pong2DScene2P.hpp
/// \brief Declaration of Pong2DScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef PONG_2D_SCENE_2D_HPP
#define PONG_2D_SCENE_2D_HPP

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

class Pong2DScene2P : public Scene
{
public:

  /// \brief Constructs a scene to keep main method clean.
  /// \param context A pointer to an object through which the Meshes and Scene will be able
  ///   to make OpenGL calls.
  /// \post A Scene has been created to make meshes.
  Pong2DScene2P (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram);

  ~Pong2DScene2P();

  /// \brief Copy constructor removed because you shouldn't be copying MyScenes.
  Pong2DScene2P (const Pong2DScene2P&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   MyScenes.
  void
  operator= (const Pong2DScene2P&) = delete;

  void 
  update (float deltaTime);

  void 
  processKeys (KeyBuffer* keyBuffer, float deltaTime);

  void 
  resetCamera(Camera* camera);

private:
  unsigned int m_gamestate;
  Player* m_player;
  Player* m_player2;
  Ball* m_ball;
};

#endif//PONG_2D_SCENE_2P_HPP