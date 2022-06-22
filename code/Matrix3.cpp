/// \file Matrix3.cpp
/// \brief Implementation of Matrix3 class and any associated global functions.
/// \author Justin Stevens
/// \version A05

#include "Matrix3.hpp"

Matrix3::Matrix3 ()
{
  this->setToIdentity();
}

Matrix3::Matrix3 (float rx, float ry, float rz,
                  float ux, float uy, float uz,
                  float bx, float by, float bz)
{
  m_right.set (rx, ry, rz);
  m_up.set (ux, uy, uz);
  m_back.set (bx, by, bz);
}

Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
                  const Vector3& back)
: m_right(right), m_up(up), m_back(back)
{

}

Matrix3::Matrix3 (const Vector3& up, const Vector3& back,
                  bool makeOrthonormal)
{
  m_up = up;
  m_back = back;
  m_right = up.cross (back);

  if (makeOrthonormal)
  {
    m_up = m_right.cross(back);
    m_right.normalize();
    m_up.normalize();
    m_back.normalize();
  }
}

Matrix3::~Matrix3 ()
{

}

void
Matrix3::setToIdentity ()
{
  m_right.set (1.0f, 0.0f, 0.0f);
  m_up.set    (0.0f, 1.0f, 0.0f);
  m_back.set  (0.0f, 0.0f, 1.0f);
}

void
Matrix3::setToZero ()
{
  m_right.set (0.0f, 0.0f, 0.0f);
  m_up.set    (0.0f, 0.0f, 0.0f);
  m_back.set  (0.0f, 0.0f, 0.0f);
}

float*
Matrix3::data ()
{
  return &m_right.m_x;
}

const float*
Matrix3::data () const
{
  return &m_right.m_x;
}

void
Matrix3::setRight (const Vector3& right)
{
  m_right = right;
}

Vector3
Matrix3::getRight () const
{
 return m_right;
}

void
Matrix3::setUp (const Vector3& up) 
{
  m_up = up;
}

Vector3
Matrix3::getUp () const
{
  return m_up;
}

void
Matrix3::setBack (const Vector3& back)
{
  m_back = back;
}

Vector3
Matrix3::getBack () const
{
  return m_back;
}

void
Matrix3::setForward (const Vector3& forward)
{
  Vector3 copy = forward;
  copy.negate();
  m_back = copy;
}

Vector3
Matrix3::getForward () const
{
  Vector3 forward = m_back;
  forward.negate();
  return forward;
}

void
Matrix3::invertRotation ()
{
  this->transpose();
}

void
Matrix3::invert ()
{
  //Use cramers rule: A^-1 = (1/det A) * (adj A)
  float det = determinant();
  
  // No inverse case, do not find inverse
  if (det == 0) return;

  Vector3 r = m_right;
  Vector3 u = m_up;
  Vector3 b = m_back;

  m_right.set ((u.m_y * b.m_z) - (b.m_y * u.m_z), 
              (b.m_y * r.m_z) - (r.m_y * b.m_z), 
              (r.m_y * u.m_z) - (u.m_y * r.m_z));
  m_up.set    ((b.m_x * u.m_z) - (u.m_x * b.m_z), 
              (r.m_x * b.m_z) - (b.m_x * r.m_z), 
              (u.m_x * r.m_z) - (r.m_x * u.m_z));
  m_back.set  ((u.m_x * b.m_y) - (b.m_x * u.m_y), 
              (b.m_x * r.m_y) - (r.m_x * b.m_y), 
              (r.m_x * u.m_y) - (u.m_x * r.m_y));

  (*this) *= (1 / det);
}

float
Matrix3::determinant () const
{
  // Expand across first row
  float det_i = m_right.m_x * ((m_up.m_y * m_back.m_z) - (m_up.m_z * m_back.m_y));
  float det_j = m_up.m_x * ((m_right.m_y * m_back.m_z) - (m_right.m_z * m_back.m_y));
  float det_k = m_back.m_x * ((m_right.m_y * m_up.m_z) - (m_right.m_z * m_up.m_y));

  return det_i - det_j + det_k;
}

void
Matrix3::transpose ()
{
  Vector3 r = m_right;
  Vector3 u = m_up;
  Vector3 b = m_back;

  m_right.set (r.m_x, u.m_x, b.m_x);
  m_up.set    (r.m_y, u.m_y, b.m_y);
  m_back.set  (r.m_z, u.m_z, b.m_z);
}

void
Matrix3::orthonormalize ()
{
  // Make vectors orthogonal
  m_up.set (0, 1, 0);
  m_right = m_up.cross (m_back);
  m_up = m_back.cross (m_right);

  // Normalize vectors to make them orthonormal
  m_back.normalize();
  m_right.normalize();
  m_up.normalize();
}

void
Matrix3::setToScale (float scale)
{
  this->setToScale (scale, scale, scale);
}

void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ)
{
  m_right.set (scaleX, 0.0f, 0.0f);
  m_up.set    (0.0f, scaleY, 0.0f);
  m_back.set  (0.0f, 0.0f, scaleZ);
}

void
Matrix3::setToShearXByYz (float shearY, float shearZ)
{
  m_right.set (1.0f, 0.0f, 0.0f);
  m_up.set    (shearY, 1.0f, 0.0f);
  m_back.set  (shearZ, 0.0f, 1.0f);
}

void
Matrix3::setToShearYByXz (float shearX, float shearZ)
{
  m_right.set (1.0f, shearX, 0.0f);
  m_up.set    (0.0f, 1.0f, 0.0f);
  m_back.set  (0.0f, shearZ, 1.0f);
}

void
Matrix3::setToShearZByXy (float shearX, float shearY)
{
  m_right.set (1.0f, 0.0f, shearX);
  m_up.set    (0.0f, 1.0f, shearY);
  m_back.set  (0.0f, 0.0f, 1.0f);
}

void
Matrix3::setToRotationX (float angleDegrees)
{
  double pi = 3.14159265358979323846;
  float angle = (angleDegrees * pi / 180.0);

  m_right.set (1.0f, 0.0f, 0.0f);
  m_up.set    (0.0f, cos (angle), -sin (angle));
  m_back.set  (0.0f, sin (angle), cos (angle));

  this->transpose();
}

void
Matrix3::setToRotationY (float angleDegrees)
{
  double pi = 3.14159265358979323846;
  float angle = (angleDegrees * pi / 180.0);

  m_right.set (cos (angle), 0.0f, sin (angle));
  m_up.set    (0.0f, 1.0f, 0.0f);
  m_back.set  (-sin (angle), 0.0f, cos (angle));
  
  this->transpose();
}

void
Matrix3::setToRotationZ (float angleDegrees)
{
  double pi = 3.14159265358979323846;
  float angle = (angleDegrees * pi / 180.0);

  m_right.set (cos (angle), -sin (angle), 0.0f);
  m_up.set    (sin (angle), cos (angle), 0.0f);
  m_back.set  (0.0f, 0.0f, 1.0f);
  
  this->transpose();
}

void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis)
{
  double pi = 3.14159265358979323846;
  float a = (angleDegrees * pi / 180.0);

  Vector3 copy = axis;
  copy.normalize();

  float x = copy.m_x;
  float y = copy.m_y;
  float z = copy.m_z;

  m_right.set (x * x + cos(a) * (1 - (x * x)), x * y * (1 - cos(a)) - (z * sin(a)), x * z * (1 - cos(a)) + (y * sin(a)));
  m_up.set    (x * y * (1 - cos(a)) + (z * sin(a)), y * y + cos(a) * (1 - (y * y)), y * z * (1 - cos(a) - (x * sin(a))));
  m_back.set  (x * z * (1 - cos(a)) - (y * sin(a)), y * z * (1 - cos(a)) + (x * sin(a)), z * z + cos(a) * (1 - (z * z)));
  
  this->transpose();
}

void
Matrix3::negate ()
{
  m_right.negate();
  m_up.negate();
  m_back.negate();
}

Vector3
Matrix3::transform (const Vector3& v) const
{
  return (*this) * v; 
}

Matrix3&
Matrix3::operator+= (const Matrix3& m)
{
  m_right += m.m_right;
  m_up += m.m_up;
  m_back += m.m_back;
  return *this;
}

Matrix3&
Matrix3::operator-= (const Matrix3& m)
{
  m_right -= m.m_right;
  m_up -= m.m_up;
  m_back -= m.m_back;
  return *this;
}

Matrix3&
Matrix3::operator*= (float scalar)
{
  m_right *= scalar;
  m_up *= scalar;
  m_back *= scalar;
  return *this;
}

Matrix3&
Matrix3::operator*= (const Matrix3& m)
{
  Vector3 row1 (m_right.m_x, m_up.m_x, m_back.m_x);
  Vector3 row2 (m_right.m_y, m_up.m_y, m_back.m_y);
  Vector3 row3 (m_right.m_z, m_up.m_z, m_back.m_z);

  m_right.set (row1.dot(m.m_right), row2.dot(m.m_right), row3.dot(m.m_right));
  m_up.set    (row1.dot(m.m_up), row2.dot(m.m_up), row3.dot(m.m_up));
  m_back.set  (row1.dot(m.m_back), row2.dot(m.m_back), row3.dot(m.m_back));

  return *this;
}

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2)
{
  Matrix3 m1_copy = m1;
  Matrix3 m2_copy = m2;
  m1_copy += m2_copy;
  return m1_copy;
}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2)
{
  Matrix3 m1_copy = m1;
  Matrix3 m2_copy = m2;
  m1_copy -= m2_copy;
  return m1_copy;
}

Matrix3
operator- (const Matrix3& m)
{
  Matrix3 copy = m;
  copy.negate();
  return copy;
}

Matrix3
operator* (const Matrix3& m, float scalar)
{
  Matrix3 copy = m;
  copy *= scalar;
  return copy;
}

Matrix3
operator* (float scalar, const Matrix3& m)
{
  Matrix3 copy = m;
  copy *= scalar;
  return copy;
}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2)
{
  Matrix3 copy = m1;
  copy *= m2;
  return copy;
}

Vector3
operator* (const Matrix3& m, const Vector3& v)
{
  Vector3 row1 (m.getRight().m_x, m.getUp().m_x, m.getBack().m_x);
  Vector3 row2 (m.getRight().m_y, m.getUp().m_y, m.getBack().m_y);
  Vector3 row3 (m.getRight().m_z, m.getUp().m_z, m.getBack().m_z);

  Vector3 result (row1.dot(v), row2.dot(v), row3.dot(v));
  return result;
}

std::ostream&
operator<< (std::ostream& out, const Matrix3& m)
{
  Matrix3 copy = m;
  copy.transpose();

  out << copy.getRight() << "\n";
  out << copy.getUp() << "\n";
  out << copy.getBack() << "\n";

  return out;
}

bool
operator== (const Matrix3& m1, const Matrix3& m2)
{
  if (!(m1.getRight() == m2.getRight())) return false;
  else if (!(m1.getUp() == m2.getUp())) return false;
  else if (!(m1.getBack() == m2.getBack())) return false;
  
  return true;
}