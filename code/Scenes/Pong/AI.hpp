/// \file AI.hpp
/// \brief Declaration of AI class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"
#include "Ball.hpp"
#include <algorithm>

class AI : public Player
{
public:
  AI(Mesh* mesh, Vector3 size, float speed);

  ~AI();

  void
  update(Ball* ball, float deltaTime, float bottomBound, float topBound, float centerBoardX, float centerBoardY);

  void
  update3D(Ball* ball, float deltaTime, float bottomBound, float topBound, float leftBound, float rightBound);

  void
  moveUp3D(float deltaTime, float topBound, Ball* ball);

  void
  moveDown3D(float deltaTime, float bottomBound, Ball* ball);

  void
  moveLeft3D(float deltaTime, float leftBound, Ball* ball);

  void
  moveRight3D(float deltaTime, float rightBound, Ball* ball);
};


#endif //AI_HPP