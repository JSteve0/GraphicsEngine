/// \file PhysicsObject.hpp
/// \brief Declaration of PhysicsObject class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "Vector3.hpp"
#include "Mesh.hpp"

class PhysicsObject 
{
public:
  PhysicsObject(Vector3 velocity, Mesh* mesh, float radius);

  ~PhysicsObject();

  void
  update(float deltaTime);

  void 
  setBounds(float left, float right, float up, float down, float near, float far);

private:
  Mesh* m_mesh;
  Vector3 m_velocity;
  Vector3 m_xBound;
  Vector3 m_yBound;
  Vector3 m_zBound;
  float m_radius;
};


#endif //PHYSICS_OBJECT_HPP
