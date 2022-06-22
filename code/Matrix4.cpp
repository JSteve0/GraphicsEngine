/// \file Matrix4.cpp
/// \brief Implementation of Matrix4 class and any associated global functions.
/// \author Justin Steveness
/// \version A07

// Local includes.
#include "Matrix4.hpp"

Matrix4::Matrix4 ()
{
  this->setToIdentity();
}

Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
    const Vector4& back, const Vector4& translation)
{
  m_right = right;
  m_up = up;
  m_back = back;
  m_translation = translation;
}

Vector4
Matrix4::getRight () const
{
  return m_right;
}

Vector4
Matrix4::getUp () const
{
  return m_up;
}

Vector4
Matrix4::getBack () const
{
  return m_back;
}

Vector4
Matrix4::getTranslation () const
{
  return m_translation;
}

void
Matrix4::setToIdentity ()
{
  m_right.set       (1.0f, 0.0f, 0.0f, 0.0f);
  m_up.set        (0.0f, 1.0f, 0.0f, 0.0f);
  m_back.set          (0.0f, 0.0f, 1.0f, 0.0f);
  m_translation.set (0.0f, 0.0f, 0.0f, 1.0f);
}

void
Matrix4::setToZero ()
{
  m_right.set       (0.0f, 0.0f, 0.0f, 0.0f);
  m_up.set        (0.0f, 0.0f, 0.0f, 0.0f);
  m_back.set          (0.0f, 0.0f, 0.0f, 0.0f);
  m_translation.set (0.0f, 0.0f, 0.0f, 0.0f);
}

const float*
Matrix4::data () const
{
  return &(m_right.m_x);
}

void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
          double nearPlaneZ, double farPlaneZ)
{
  this->setToZero();
  double pi = 3.14159265358979323846;
  fovYDegrees /= 2.0;
  double t = tan( fovYDegrees * pi / 180.0 );

  m_right.m_x = 1.0f / ( (float) ( (aspectRatio * t) ) );
  m_up.m_y = 1.0f / ( (float) (t) ) ;
  m_back.m_z = (float) ( (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ) );
  m_back.m_w = -1.0f;
  m_translation.m_z = 2.0f * (float) ( (nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ) );
}

void
Matrix4::setToPerspectiveProjection (double left, double right,
          double bottom, double top,
          double nearPlaneZ, double farPlaneZ)
{
  this->setToZero();

  m_right.m_x = (float) ( (2.0 * nearPlaneZ) / (right - left) );
  m_up.m_y = (float) ( (2.0 * nearPlaneZ) / (top - bottom) );
  m_back.m_x = (float) ( (right + left) / (right - left) );
  m_back.m_y = (float) ( (top + bottom) / (top - bottom) );
  m_back.m_z = (float) ( (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ) );
  m_back.m_w = -1.0f;
  m_translation.m_z = (float) ( (2.0 * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ) );
}

void
Matrix4::setToOrthographicProjection (double left, double right,
            double bottom, double top,
            double nearPlaneZ, double farPlaneZ)
{
  this->setToZero();
  
  m_right.m_x = (float) ( 2.0 / (right - left) );
  m_up.m_y = (float) ( 2.0 / (top - bottom) );
  m_back.m_z = (float) ( 2.0 / (nearPlaneZ - farPlaneZ) );
  m_translation.m_x = (float) -( (right + left) / (right - left) );
  m_translation.m_y = (float) -( (top + bottom) / (top - bottom) );
  m_translation.m_z = (float) ( (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ) );
  m_translation.m_w = 1.0f;
}

std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
  out << Vector4(m.getRight().m_x, m.getUp().m_x, m.getBack().m_x, m.getTranslation().m_x) << "\n"
      << Vector4(m.getRight().m_y, m.getUp().m_y, m.getBack().m_y, m.getTranslation().m_y) << "\n"
      << Vector4(m.getRight().m_z, m.getUp().m_z, m.getBack().m_z, m.getTranslation().m_z) << "\n"
      << Vector4(m.getRight().m_w, m.getUp().m_w, m.getBack().m_w, m.getTranslation().m_w) << "\n";

  return out;
}

bool
operator== (const Matrix4& m1, const Matrix4& m2)
{
  return (((m1.getRight() == m2.getRight())) &&
           (m1.getUp() == m2.getUp()) &&
           (m1.getBack() == m2.getBack()) && 
           (m1.getTranslation() == m2.getTranslation()));
}