/// \file PhysicsObject.cpp
/// \brief Definition of PhysicsObject class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(Vector3 velocity, Mesh* mesh, float radius)
  : m_mesh(mesh), m_velocity(velocity), m_radius(radius)
{

}

PhysicsObject::~PhysicsObject()
{

}

void
PhysicsObject::update(float deltaTime)
{
  //Move
  m_mesh->moveWorld(1.0f * deltaTime, m_velocity);

  //CheckBounds
  Vector3 pos = m_mesh->getPosition();
  //ZBounds
  if (pos.m_z - m_radius < m_zBound.m_y) 
  {
    m_velocity.m_z = -m_velocity.m_z;
  }
  else if (pos.m_z + m_radius > m_zBound.m_x) 
  {
    m_velocity.m_z = -m_velocity.m_z;
  }
  //XBounds
  if (pos.m_x - m_radius < m_xBound.m_x) 
  {
    m_velocity.m_x = -m_velocity.m_x;
  }
  else if (pos.m_x + m_radius > m_xBound.m_y) 
  {
    m_velocity.m_x = -m_velocity.m_x;
  }
  //YBounds
  if (pos.m_y - m_radius < m_yBound.m_y) 
  {
    m_velocity.m_y = -m_velocity.m_y;
  }
  else if (pos.m_y + m_radius > m_yBound.m_x) 
  {
    m_velocity.m_y = -m_velocity.m_y;
  }
}

void 
PhysicsObject::setBounds(float left, float right, float up, float down, float near, float far)
{
  m_xBound = Vector3(left, right, 0.0f);
  m_yBound = Vector3(up, down, 0.0f);
  m_zBound = Vector3(near, far, 0.0f);
}