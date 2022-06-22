/// \file Player.hpp
/// \brief Declaration of Player class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../../Vector3.hpp"
#include "../../Mesh.hpp"

class Player 
{
public:

  Player(Mesh* mesh, Vector3 size, float speed);

  ~Player();

  void
  moveUp(float deltaTime, float topBound);

  void
  moveDown(float deltaTime, float bottomBound);

  void
  moveLeft(float deltaTime, float leftBound);

  void
  moveRight(float deltaTime, float rightBound);

  Vector3
  getPosition() const;

  Vector3 
  getSize() const;

protected:
  Mesh* m_mesh;
  Vector3 m_size;
  float m_speed;
};

#endif //PLAYER_HPP