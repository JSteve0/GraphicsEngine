/// \file Player.cpp
/// \brief Definition of Player class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "Player.hpp"

Player::Player(Mesh* mesh, Vector3 size, float speed)
  : m_mesh(mesh), m_size(size), m_speed(speed)
{

}

Player::~Player()
{

}

void
Player::moveUp(float deltaTime, float topBound)
{
  if(m_mesh->getPosition().m_y + (m_size.m_y / 2.0f) < topBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(0.0f, m_speed, 0.0f));
  }
}

void
Player::moveDown(float deltaTime, float bottomBound)
{
  if(m_mesh->getPosition().m_y - (m_size.m_y / 2.0f) > bottomBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(0.0f, -m_speed, 0.0f));
  }
}

void
Player::moveLeft(float deltaTime, float leftBound)
{
  if(m_mesh->getPosition().m_x - (m_size.m_x / 2.0f) > leftBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(-m_speed, 0.0f, 0.0f));
  }
}

void
Player::moveRight(float deltaTime, float rightBound)
{
  if(m_mesh->getPosition().m_x + (m_size.m_x / 2.0f) < rightBound)
  {
    m_mesh->moveWorld(1.0f * deltaTime, Vector3(m_speed, 0.0f, 0.0f));
  }
}

Vector3
Player::getPosition() const
{
  return m_mesh->getPosition();
}

Vector3 
Player::getSize() const 
{
  return m_size;
}