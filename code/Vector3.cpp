/// \file Vector3.cpp
/// \brief Definition of Vector class and any associated global functions.
/// \author Justin Stevens
/// \version A04

#include "Vector3.hpp"

Vector3::Vector3 () 
: m_x(0), m_y(0), m_z(0)
{

}

Vector3::Vector3 (float xyz)
: m_x(xyz), m_y(xyz), m_z(xyz)
{

}

Vector3::Vector3 (float x, float y, float z)
: m_x(x), m_y(y), m_z(z)
{

}

void
Vector3::set (float xyz) 
{
  m_x = xyz;
  m_y = xyz;
  m_z = xyz;
}

void
Vector3::set (float x, float y, float z) 
{
  m_x = x;
  m_y = y;
  m_z = z;
}

void
Vector3::negate () 
{
  m_x = -m_x;
  m_y = -m_y;
  m_z = -m_z;
}

float
Vector3::dot (const Vector3& v) const 
{
  return ((this->m_x * v.m_x) + (this->m_y * v.m_y) + (this->m_z * v.m_z));
}

float
Vector3::angleBetween (const Vector3& v) const 
{
  // theta = arccos ((this.v dot v) / (this.length * v.length))
  float dot = this->dot (v);
  float denominator = this->length() * v.length();
  return std::acos(dot / denominator);
}

Vector3
Vector3::cross (const Vector3& v) const 
{
  Vector3 v1 (m_x, m_y, m_z);

  float i = ((v1.m_y * v.m_z) - (v1.m_z * v.m_y));
  float j = ((v1.m_z * v.m_x) - (v1.m_x * v.m_z));
  float k = ((v1.m_x * v.m_y) - (v1.m_y * v.m_x));

  v1.set(i, j, k);
  return v1;
}

float
Vector3::length () const 
{
  // |v| = (x^2 + y^2 + z^2) ^ (1/2)
  return std::sqrt ((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

void
Vector3::normalize () 
{
  float length = this->length();
  m_x /= length;
  m_y /= length;
  m_z /= length;
}

glm::vec3
Vector3::convert () {
  return glm::vec3 (m_x, m_y, m_z);
} 

Vector3&
Vector3::operator= (const glm::vec3& v)
{
  this->set(v.x, v.y, v.z);
  return *this;
}

Vector3&
Vector3::operator+= (const Vector3& v)
{
  this->m_x += v.m_x;
  this->m_y += v.m_y;
  this->m_z += v.m_z;
  return *this;
}

Vector3&
Vector3::operator-= (const Vector3& v)
{
  this->m_x -= v.m_x;
  this->m_y -= v.m_y;
  this->m_z -= v.m_z;
  return *this;
}

Vector3&
Vector3::operator*= (float s)
{
  this->m_x *= s;
  this->m_y *= s;
  this->m_z *= s;
  return *this;
}

Vector3&
Vector3::operator/= (float s)
{
  this->m_x /= s;
  this->m_y /= s;
  this->m_z /= s;
  return *this;
}

Vector3
operator+ (const Vector3& v1, const Vector3& v2) 
{
  Vector3 v = v1;
  v += v2;
  return v;
}

Vector3
operator- (const Vector3& v1, const Vector3& v2)
{
  Vector3 v = v1;
  v -= v2;
  return v;
}

Vector3
operator- (const Vector3& v)
{
  Vector3 v1 = v;
  v1.negate();
  return v1;
}

Vector3
operator* (float s, const Vector3& v)
{
  Vector3 v1 = v;
  v1 *= s;
  return v1;
}

Vector3
operator* (const Vector3& v, float s)
{
  Vector3 v1 = v;
  v1 *= s;
  return v1;
}

Vector3
operator/ (const Vector3& v, float s)
{
  Vector3 v1 = v;
  v1 /= s;
  return v1;
}

std::ostream&
operator<< (std::ostream& out, const Vector3& v)
{
  out << std::fixed << std::setprecision(2);

  out << std::setw(10) << v.m_x;
  out << std::setw(10) << v.m_y;
  out << std::setw(10) << v.m_z;

  return out;
}

/// \brief Checks whether or not two vectors are equal.
/// Vectors are equal if each of their respective components are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] v1 A vector.
/// \param[in] v2 Another vector.
/// \return Whether or not v1 and v2 are equal.
bool
operator== (const Vector3& v1, const Vector3& v2) {
  float tolerance = 0.00001;
  Vector3 v3 = v2 - v1;

  if (std::abs(v3.m_x) > tolerance) return false;
  else if (std::abs(v3.m_y) > tolerance) return false;
  else if (std::abs(v3.m_z) > tolerance) return false;
  return true;
}