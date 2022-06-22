/// \file Ball.cpp
/// \brief Definition of Ball class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "Ball.hpp"

Ball::Ball(Mesh* mesh,  Vector3 size, Vector3 velocity)
  : m_mesh(mesh), m_size(size), m_velocity(velocity)
{

}

Ball::~Ball()
{

}

bool
Ball::update(float deltaTime, float leftBound, float rightBound, float topBound, float bottomBound)
{
  m_mesh->moveWorld(1.0f * deltaTime, m_velocity);
  Vector3 pos = m_mesh->getPosition();
  //Vertical Bounds
  if ((pos.m_y + (m_size.m_y / 2.0f) > topBound && m_velocity.m_y > 0.0f) || (pos.m_y - (m_size.m_y / 2.0f) < bottomBound && m_velocity.m_y < 0.0f)) 
  {
    m_velocity.m_y = -m_velocity.m_y;
  }
  //Horizontal Bounds
  if (pos.m_x + (m_size.m_x / 2.0f) > rightBound || pos.m_x - (m_size.m_x / 2.0f) < leftBound)  
  {
    return true;
  }
  return false;
}

bool
Ball::update3D(float deltaTime, float leftBound, float rightBound, float topBound, float bottomBound, float nearBound, float farBound)
{
  m_mesh->moveWorld(1.0f * deltaTime, m_velocity);
  Vector3 pos = m_mesh->getPosition();
  //Vertical Bounds
  if ((pos.m_y + (m_size.m_y / 2.0f) > topBound && m_velocity.m_y > 0.0f) || (pos.m_y - (m_size.m_y / 2.0f) < bottomBound && m_velocity.m_y < 0.0f)) 
  {
    m_velocity.m_y = -m_velocity.m_y;
  }
  //Horizontal Bounds
  if (pos.m_x + (m_size.m_x / 2.0f) > rightBound || pos.m_x - (m_size.m_x / 2.0f) < leftBound)  
  {
    m_velocity.m_x = -m_velocity.m_x;
  }
  //Z Bounds
  if (pos.m_z + (m_size.m_z / 2.0f) > nearBound || pos.m_z - (m_size.m_z / 2.0f) < farBound)  
  {
    //m_velocity.m_z = -m_velocity.m_z;
    return true;
  }
  return false;
}

bool
Ball::collides(Player* paddle)
{
  //aabb collision detection algorithm
  Vector3 rect1 = m_mesh->getPosition();
  Vector3 rect2 = paddle->getPosition();
  Vector3 size1 = m_size;
  Vector3 size2 = paddle->getSize();
  size1 /= 2.0f;
  size2 /= 2.0f;

  return (rect1.m_x - size1.m_x < rect2.m_x + size2.m_x &&
          rect1.m_x + size1.m_x > rect2.m_x - size2.m_x &&
          rect1.m_y - size1.m_y < rect2.m_y + size2.m_y &&
          rect1.m_y + size1.m_y > rect2.m_y - size2.m_y );
}

bool
Ball::collides3D(Player* paddle)
{
  //Sphere aabb collision algorithm
  Vector3 spherePos = m_mesh->getPosition();
  Vector3 sphereSize = m_size / 2;
  Vector3 paddlePos = paddle->getPosition();
  Vector3 paddleSize = paddle->getSize() / 2;
  
  float x = std::max(paddlePos.m_x - paddleSize.m_x, std::min(spherePos.m_x, paddlePos.m_x + paddleSize.m_x));
  float y = std::max(paddlePos.m_y - paddleSize.m_y, std::min(spherePos.m_y, paddlePos.m_y + paddleSize.m_y));
  float z = std::max(paddlePos.m_z - paddleSize.m_z, std::min(spherePos.m_z, paddlePos.m_z + paddleSize.m_z));

  float distance = std::sqrt ((x - spherePos.m_x) * (x - spherePos.m_x) +
                               (y - spherePos.m_y) * (y - spherePos.m_y) + 
                               (z - spherePos.m_z) * (z - spherePos.m_z));

  return distance < sphereSize.m_x;
}

void
Ball::bounce()
{
  m_velocity.m_x = -m_velocity.m_x;
  m_velocity *= 1.025;
}

void
Ball::bounce3D()
{
  m_velocity.m_z = -m_velocity.m_z;
  m_velocity *= 1.01;
}

Vector3
Ball::getPosition() const
{
  return m_mesh->getPosition();
}

Vector3 
Ball::getSize() const
{
  return m_size;
}

void
Ball::reset() {
  Vector3 pos = m_mesh->getPosition();
  m_mesh->moveWorld(1.0f, Vector3(-pos.m_x, -pos.m_y, 0.0f));
}

void
Ball::reset3D() {
  Vector3 pos = m_mesh->getPosition();
  m_mesh->moveWorld(1.0f, Vector3(-pos.m_x, -pos.m_y, -pos.m_z));
}

void
Ball::setVelocity(Vector3 velocity) 
{
  m_velocity = velocity;
}

Vector3
Ball::getVelocity()
{
  return m_velocity;
}