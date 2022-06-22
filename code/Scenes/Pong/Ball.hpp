/// \file Ball.hpp
/// \brief Declaration of Ball class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef BALL_HPP
#define BALL_HPP

#include "../../Vector3.hpp"
#include "../../Mesh.hpp"
#include "Player.hpp"

class Ball 
{
public:

  Ball(Mesh* mesh, Vector3 size, Vector3 velocity);

  ~Ball();

  bool
  update(float deltaTime, float leftBound, float rightBound, float topBound, float bottomBound);

  bool
  update3D(float deltaTime, float leftBound, float rightBound, float topBound, float bottomBound, float nearBound, float farBound);

  bool
  collides(Player* paddle);

  bool
  collides3D(Player* paddle);

  void
  bounce();

  void
  bounce3D();

  Vector3
  getPosition() const;

  Vector3 
  getSize() const;

  void
  reset();

  void
  reset3D();

  void
  setVelocity(Vector3 velocity);

  Vector3
  getVelocity();

private:
  Mesh* m_mesh;
  Vector3 m_size;
  Vector3 m_velocity;
};

#endif //BALL_HPP