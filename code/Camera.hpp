/// \file Camera.hpp
/// \brief Declaration of Camera class and any associated global functions.
/// \author Chad Hogg and Justin Stevens
/// \version A07

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "OpenGLContext.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
#include "Transform.hpp"

///TODO Create method for intializing direction vectors and normalizing them.

/// \brief An eye that is viewing the scene.
class Camera
{
public:

  /// \brief Constructs a new Camera.
  ///
  /// \param eyePosition The location (in world coordinates) where the camera
  ///   is located.
  /// \param localBackDirection A vector pointing backwards from the camera.
  /// \param nearClipPlaneDistance The distance to the closest things the
  ///   camera can "see".
  /// \param farClipPlaneDistance The distance to the farthest things the
  ///   camera can "see".
  /// \param aspectRatio The window's width divided by height.
  /// \param verticalFieldOfViewDegrees The angle determining how much the
  ///   camera "sees".
  /// \post The camera's pose has been set and a projection matrix generated.
  /// \post The three orientation vectors are orthonormal with each other.
  /// \post All of the parameters have been copied into their respective data
  ///   members, and the local right and up have been calculated to be
  ///   orthonormal to the local back.
  Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	  float nearClipPlaneDistance, float farClipPlaneDistance,
	  float aspectRatio, float verticalFieldOfViewDegrees);

  /// \brief Destructs a Camera.
  ~Camera ();
  
  /// \brief Sets the position (eye point) of the camera.
  /// \param[in] position The new position of the camera.
  /// \post The camera's location has been changed.
  void
  setPosition (const Vector3& position);

  Vector3
  getPosition ();

  /// \brief Moves the position (eye point) of the camera right or left.
  /// \param[in] distance How far to move along the right vector.
  /// \post The camera's location has been changed.
  void
  moveRight (float distance);

  /// \brief Moves the position (eye point) of the camera up or down.
  /// \param[in] distance How far to move along the up vector.
  /// \post The camera's location has been changed.
  void
  moveUp (float distance);

  /// \brief Moves the position (eye point) of the camera back or forward.
  /// \param[in] distance How far to move along the back vector.
  /// \post The camera's location has been changed.
  void
  moveBack (float distance);

  /// \brief Rotates the camera counterclockwise around the up vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  yaw (float degrees);

  /// \brief Rotates the camera counterclockwise around the right vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  pitch (float degrees);

  /// \brief Rotates the camera counterclockwise around the back vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  roll (float degrees);

  /// \brief Gets the view matrix, recalculating it only if necessary.
  /// \return A view matrix based on the camera's location and axis vectors.
  Transform
  getViewMatrix ();

  /// \brief Recreates the projection matrix to a symmetric perspective.
  /// \param[in] verticalFovDegrees The viewing angle.
  /// \param[in] aspectRatio The width / height.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
		 double nearZ, double farZ); 

  /// \brief Recreates the projection matrix to a asymmetric perspective.
  /// \param[in] left The left side of the viewing angle.
  /// \param[in] right The right side of the viewing angle.
  /// \param[in] bottom The bottom side of the viewing angle.
  /// \param[in] top The top side of the viewing angle.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  setProjectionAsymmetricPerspective (double left, double right,
          double bottom, double top,
          double nearPlaneZ, double farPlaneZ); 

  /// \brief Recreates the projection matrix to a orthographic perspective.
  /// \param[in] left The left side of the viewing angle.
  /// \param[in] right The right side of the viewing angle.
  /// \param[in] bottom The bottom side of the viewing angle.
  /// \param[in] top The top side of the viewing angle.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  setProjectionOrthographic (double left, double right,
            double bottom, double top,
            double nearPlaneZ, double farPlaneZ);

  /// \brief Gets the projection matrix.
  /// \return The projection matrix.
  Matrix4
  getProjectionMatrix ();

  /// \brief Resets the camera to its original pose.
  /// \post The position (eye point) is the same as what had been specified in
  ///   the constructor.
  /// \post The back vector is the same as what had been specified in the
  ///   constructor.
  /// \post The up and right vectors are computed as they had been in the
  ///   constructor.
  void
  resetPose ();

  /// \brief Returns the fov.
  double 
  getFOV (); 

  Transform 
  getWorld (); 

  /// \brief Sets the fov
  /// \param[in] fov The new fov.
  void 
  setFOV (double fov); 

private:

  /// A 4 by 4 matrix storing the up, back, right and position of the camera.
  Transform m_world;

  /// The projection matrix.
  Matrix4 m_projectionMatrix;
  /// The view matrix.
  Transform m_viewMatrix;

  /// Orginal location of camera
  Vector3 m_startingEyePosition;
  /// Orginal camera orientation
  Vector3 m_startingLocalBackDirection;

  // Stores fov
  double m_fov;

  /// Boolean value to change when camera is moved
  bool hasCameraMoved;
};

#endif//CAMERA_HPP