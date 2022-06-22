/// \file PhysicsScene.hpp
/// \brief Declaration of PhysicsScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef PHYSICSSCENE_HPP
#define PHYSICSSCENE_HPP

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
#include "Pong/AI.hpp"
#include "Pong/Player.hpp"
#include "Pong/Ball.hpp"

class PhysicsScene : public Scene
{
public:

  /// \brief Constructs a scene to keep main method clean.
  /// \param context A pointer to an object through which the Meshes and Scene will be able
  ///   to make OpenGL calls.
  /// \post A Scene has been created to make meshes.
  PhysicsScene (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram);

  ~PhysicsScene();

  /// \brief Copy constructor removed because you shouldn't be copying MyScenes.
  PhysicsScene (const PhysicsScene&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   MyScenes.
  void
  operator= (const PhysicsScene&) = delete;

  void 
  update (float deltaTime);

  void 
  processKeys (KeyBuffer* keyBuffer, float deltaTime);

  void 
  resetCamera(Camera* camera);

  private:
  unsigned int m_gamestate;
  Player* m_player;
  AI* m_AI;
  Ball* m_ball;
};

#endif//PHYSICSSCENE_HPP