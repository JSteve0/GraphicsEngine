/// \file AI.cpp
/// \brief Definition of AI class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "AI.hpp"

AI::AI(Mesh* mesh, Vector3 size, float speed)
  : Player::Player(mesh, size, speed)
{

}

AI::~AI()
{

}

void
AI::update(Ball* ball, float deltaTime, float bottomBound, float topBound, float centerBoardX, float centerBoardY)
{
  float margin = 0.5f;
  //Track ball
  if (ball->getPosition().m_x - margin > centerBoardX)
  {
    if (ball->getPosition().m_y > m_mesh->getPosition().m_y)
    {
      Player::moveUp(deltaTime, topBound);
    } else if (ball->getPosition().m_y + margin < m_mesh->getPosition().m_y)
    {
      Player::moveDown(deltaTime, bottomBound);
    }
  }
  else {
    if (centerBoardY - margin > m_mesh->getPosition().m_y)
    {
      Player::moveUp(deltaTime, topBound);
    } else if (centerBoardY + margin < m_mesh->getPosition().m_y)
    {
      Player::moveDown(deltaTime, bottomBound);
    }
  }
}

void
AI::update3D(Ball* ball, float deltaTime, float bottomBound, float topBound, float leftBound, float rightBound)
{
  float margin = 1.0f;
  //Track ball
  if (ball->getPosition().m_y - margin > m_mesh->getPosition().m_y)
  {
    AI::moveUp3D(deltaTime, topBound, ball);
  } else if (ball->getPosition().m_y + margin < m_mesh->getPosition().m_y)
  {
    AI::moveDown3D(deltaTime, bottomBound, ball);
  }
  if (ball->getPosition().m_x - margin > m_mesh->getPosition().m_x)
  {
    AI::moveRight3D(deltaTime, rightBound, ball);
  } else if (ball->getPosition().m_x + margin < m_mesh->getPosition().m_x)
  {
    AI::moveLeft3D(deltaTime, leftBound, ball);
  }

}

void
AI::moveUp3D(float deltaTime, float topBound, Ball* ball)
{
  if(m_mesh->getPosition().m_y + (m_size.m_y / 2.0f) < topBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(0.0f, std::min(m_speed, 10 + ball->getPosition().m_y - m_mesh->getPosition().m_y), 0.0f));
  }
}

void
AI::moveDown3D(float deltaTime, float bottomBound, Ball* ball)
{
  if(m_mesh->getPosition().m_y - (m_size.m_y / 2.0f) > bottomBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(0.0f, -std::min(m_speed, 10 + m_mesh->getPosition().m_y - ball->getPosition().m_y), 0.0f));
  }
}

void
AI::moveLeft3D(float deltaTime, float leftBound, Ball* ball)
{
  if(m_mesh->getPosition().m_x - (m_size.m_x / 2.0f) > leftBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(-std::min(m_speed, 10 + m_mesh->getPosition().m_x - ball->getPosition().m_x), 0.0f, 0.0f));
  }
}

void
AI::moveRight3D(float deltaTime, float rightBound, Ball* ball)
{
  if(m_mesh->getPosition().m_x + (m_size.m_x / 2.0f) < rightBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(std::min(m_speed, 10 + ball->getPosition().m_x - m_mesh->getPosition().m_x), 0.0f, 0.0f));
  }
}