/// \file Transform.cpp
/// \brief Implementation of Transform class and any associated global functions.
/// \author Justin Stevens
/// \version A07

#include "Transform.hpp"

Transform::Transform ()
{
  reset();
}

Transform::Transform (const Matrix3& orientation, const Vector3& position)
: m_rotScale(orientation), m_position(position)
{

}

void
Transform::orthonormalize ()
{
  m_rotScale.orthonormalize();
}

void
Transform::reset ()
{
  m_rotScale.setToIdentity();
  m_position.set(0);
}

Matrix4
Transform::getTransform () const
{
  Vector3 r = m_rotScale.getRight();
  Vector3 u = m_rotScale.getUp();
  Vector3 b = m_rotScale.getBack();
  Matrix4 temp (Vector4 (r.m_x, r.m_y, r.m_z, 0.0f),
                  Vector4 (u.m_x, u.m_y, u.m_z, 0.0f),
                  Vector4 (b.m_x, b.m_y, b.m_z, 0.0f),
                  Vector4 (m_position.m_x, m_position.m_y, m_position.m_z, 1));
  
  return temp;
}

void
Transform::getTransform (float array[16]) const
{
  Vector3 r = m_rotScale.getRight();
  Vector3 u = m_rotScale.getUp();
  Vector3 b = m_rotScale.getBack();

  float temp [] = {r.m_x, r.m_y, r.m_z, 0, 
                  u.m_x, u.m_y, u.m_z, 0, 
                  b.m_x, b.m_y, b.m_z, 0, 
                  m_position.m_x, m_position.m_y, m_position.m_z, 1};
  
  for (int i = 0; i < 16; ++i)
    array[i] = temp[i];
}

Vector3
Transform::getPosition () const
{
  return m_position;
}

void
Transform::setPosition (const Vector3& position)
{
  m_position = position;
}

void
Transform::setPosition (float x, float y, float z)
{
  m_position.set(x, y, z);
}

Vector3
Transform::getRight () const
{
  return m_rotScale.getRight();
}

Vector3
Transform::getUp () const 
{
  return m_rotScale.getUp();
}

Vector3
Transform::getBack () const
{
  return m_rotScale.getBack();
}

Matrix3
Transform::getOrientation () const
{
  return m_rotScale;
}

void
Transform::setOrientation (const Matrix3& orientation)
{
  m_rotScale = orientation;
}

void
Transform::setOrientation (const Vector3& right, const Vector3& up,
    const Vector3& back)
{
  m_rotScale.setRight(right);
  m_rotScale.setUp(up);
  m_rotScale.setBack(back);
}

void
Transform::moveRight (float distance) 
{
  m_position += distance * m_rotScale.getRight();
}

void
Transform::moveUp (float distance)
{
  m_position += distance * m_rotScale.getUp();
}

void
Transform::moveBack (float distance)
{
  m_position += distance * m_rotScale.getBack();
}

void
Transform::moveLocal (float distance, const Vector3& localDirection)
{
  Vector3 r = m_rotScale.getRight();
  Vector3 u = m_rotScale.getUp();
  Vector3 b = m_rotScale.getBack();
  Vector3 d = localDirection * distance;

  m_position.set((r.m_x * d.m_x) + (u.m_x * d.m_y) + (b.m_x * d.m_z) + m_position.m_x,
                (r.m_y * d.m_x) + (u.m_y * d.m_y) + (b.m_y * d.m_z) + m_position.m_y,
                (r.m_z * d.m_x) + (u.m_z * d.m_y) + (b.m_z * d.m_z) + m_position.m_z);
}

void
Transform::moveWorld (float distance, const Vector3& worldDirection)
{
  Vector3 d = worldDirection * distance;
  Vector3 p = m_position;

  m_position.set(p.m_x + d.m_x, p.m_y + d.m_y, p.m_z + d.m_z);
}

void
Transform::pitch (float angleDegrees)
{
  Matrix3 pitchMatrix;
  pitchMatrix.setToRotationX (angleDegrees);
  m_rotScale *= pitchMatrix;
}

void
Transform::yaw (float angleDegrees)
{
  Matrix3 yawMatrix;
  yawMatrix.setToRotationY (angleDegrees);
  m_rotScale *= yawMatrix;
}

void
Transform::roll (float angleDegrees)
{
  Matrix3 rollMatrix;
  rollMatrix.setToRotationZ (angleDegrees);
  m_rotScale *= rollMatrix;
}

void
Transform::rotateLocal (float angleDegrees, const Vector3& axis)
{
  Matrix3 rotMatrix;
  rotMatrix.setFromAngleAxis (angleDegrees, axis);
  m_rotScale *= rotMatrix;
}

void
Transform::alignWithWorldY ()
{
  m_rotScale.setUp(Vector3 (0.0f, 1.0f, 0.0f));
  m_rotScale.setRight(Vector3 (1.0f, 0.0f, 0.0f));
  m_rotScale.setBack(Vector3 (0.0f, 0.0f, 1.0f));
}

void
Transform::rotateWorld (float angleDegrees, const Vector3& axis)
{
  Matrix3 rotMatrix;
  rotMatrix.setFromAngleAxis (angleDegrees, axis);
  m_rotScale = rotMatrix * m_rotScale;
  m_position = rotMatrix * m_position;
}

void
Transform::scaleLocal (float scale)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);

  m_rotScale *= scaleMatrix;
}

void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);

  m_rotScale *= scaleMatrix;
}
  
void
Transform::scaleWorld (float scale)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);

  m_rotScale = scaleMatrix * m_rotScale;
  m_position = scaleMatrix * m_position;
}

void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);

  m_rotScale = scaleMatrix * m_rotScale;
  m_position = scaleMatrix * m_position;
}

void
Transform::shearLocalXByYz (float shearY, float shearZ)
{
  Matrix3 shear;
  shear.setToShearXByYz(shearY, shearZ);

  m_rotScale *= shear;
}

void
Transform::shearLocalYByXz (float shearX, float shearZ) 
{
  Matrix3 shear;
  shear.setToShearYByXz(shearX, shearZ);

  m_rotScale *= shear;
}

void
Transform::shearLocalZByXy (float shearX, float shearY)
{
  Matrix3 shear;
  shear.setToShearZByXy(shearX, shearY);

  m_rotScale *= shear;
}

void
Transform::invertRt ()
{
  m_rotScale.invertRotation();
  m_position = m_rotScale * -m_position;
}

/// \brief Combines this with "t" in the order this * t.
/// \param[in] t Another transform that should be combined with this.
/// \post This transform consists of itself times t.
void
Transform::combine (const Transform& t)
{
  Vector3 row1 (m_rotScale.getRight().m_x, m_rotScale.getUp().m_x, m_rotScale.getBack().m_x);
  Vector3 row2 (m_rotScale.getRight().m_y, m_rotScale.getUp().m_y, m_rotScale.getBack().m_y);
  Vector3 row3 (m_rotScale.getRight().m_z, m_rotScale.getUp().m_z, m_rotScale.getBack().m_z);
  
  setOrientation(m_rotScale * t.getOrientation());
  setPosition(row1.dot(t.getPosition()) + m_position.m_x, 
              row2.dot(t.getPosition()) + m_position.m_y, 
              row3.dot(t.getPosition()) + m_position.m_z);
}

/// \brief Combines two transforms into their product.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return A new transform that is t1 * t2.
Transform
operator* (const Transform& t1, const Transform& t2)
{
  Transform copy = t1;
  copy.combine(t2);
  return copy;
}

std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
  Matrix3 temp = t.getOrientation();
  temp.transpose();
  out << temp.getRight() << "      " << t.getPosition().m_x << "\n";
  out << temp.getUp() << "      " << t.getPosition().m_y << "\n";
  out << temp.getBack() << "      " << t.getPosition().m_z << "\n";
  out << "      0.00      0.00      0.00      1.00" << "\n";
  return out;
}

bool
operator== (const Transform& t1, const Transform& t2)
{
  if (t1.getRight() == t2.getRight() && t1.getUp() == t2.getUp() && t1.getBack() == t2.getBack() 
      && t1.getPosition() == t2.getPosition()) {
    return true;
  }
  return false;
}