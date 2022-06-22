/// \file Camera.cpp
/// \brief Definition of Camera class and any associated global functions.
/// \author Justin Stevens
/// \version A07

#include "Camera.hpp"

Camera::Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
  float nearClipPlaneDistance, float farClipPlaneDistance,
  float aspectRatio, float verticalFieldOfViewDegrees)
{
  m_world.setPosition(eyePosition);
  m_startingEyePosition = eyePosition;
  m_startingLocalBackDirection = localBackDirection;

  setProjectionSymmetricPerspective(verticalFieldOfViewDegrees, aspectRatio, nearClipPlaneDistance, farClipPlaneDistance);

  Matrix3 temp(Vector3(0, 0, 0), Vector3(0, 0, 0), localBackDirection);
  m_world.setOrientation(temp);
  m_world.orthonormalize();

  hasCameraMoved = true;
}

Camera::~Camera ()
{

}

void
Camera::setPosition (const Vector3& position)
{
  hasCameraMoved = true;
  m_world.setPosition(position);
}

Vector3
Camera::getPosition ()
{
  return m_world.getPosition();
}

void
Camera::moveRight (float distance)
{
  hasCameraMoved = true;
  m_world.moveRight(distance);
}

void
Camera::moveUp (float distance)
{
  hasCameraMoved = true;
  m_world.moveUp(distance);
}

void
Camera::moveBack (float distance)
{
  hasCameraMoved = true;
  m_world.moveBack(distance);
}

void
Camera::yaw (float degrees)
{
  m_world.yaw(degrees);
  hasCameraMoved = true;
}

void
Camera::pitch (float degrees)
{
  m_world.pitch(degrees);
  hasCameraMoved = true;
}

void
Camera::roll (float degrees)
{
  m_world.roll(degrees);
  hasCameraMoved = true;
}

Transform
Camera::getViewMatrix ()
{
  if (hasCameraMoved) 
  {
    Vector3 t (m_world.getPosition());
    Vector3 u (m_world.getUp());
    Vector3 p (m_world.getPosition() + (m_world.getBack() * -1.0f));
    Vector3 e (m_world.getPosition() - p);
    Vector3 r = m_world.getUp().cross(m_world.getBack());
    Vector3 b = e / e.length();
    m_viewMatrix.setOrientation(r, u, b);
    m_viewMatrix.setPosition(t);
    hasCameraMoved = false;
    m_viewMatrix.invertRt();
  }
  return m_viewMatrix;
}

void
Camera::setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
    double nearZ, double farZ)
{
  m_fov = verticalFovDegrees;
  m_projectionMatrix.setToPerspectiveProjection(verticalFovDegrees, aspectRatio, nearZ, farZ);
}

void
Camera::setProjectionAsymmetricPerspective (double left, double right,
        double bottom, double top,
        double nearPlaneZ, double farPlaneZ)
{
  m_projectionMatrix.setToPerspectiveProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

void
Camera::setProjectionOrthographic (double left, double right,
            double bottom, double top,
            double nearPlaneZ, double farPlaneZ)
{
  m_projectionMatrix.setToOrthographicProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

Matrix4
Camera::getProjectionMatrix ()
{
  return m_projectionMatrix;
}

void
Camera::resetPose ()
{
  setPosition(m_startingEyePosition);
  
  Matrix3 temp(Vector3(0, 0, 0), Vector3(0, 0, 0), m_startingLocalBackDirection);
  m_world.setOrientation(temp);
  m_world.orthonormalize();

  hasCameraMoved = true;
}

double 
Camera::getFOV () {
  return m_fov;
}

void 
Camera::setFOV (double fov)
{
  m_fov = fov;
}

Transform 
Camera::getWorld ()
{
  return m_world;
}