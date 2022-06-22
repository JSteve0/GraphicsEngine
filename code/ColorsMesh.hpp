/// \file ColorsMesh.hpp
/// \brief Declaration of ColorsMesh class and any associated global functions.
/// \author Justin Stevens
/// \version A08

#ifndef COLORSMESH_HPP
#define COLORSMESH_HPP

#include "Mesh.hpp"

class ColorsMesh : public Mesh
{
public:

  /// \brief Constructs an empty Mesh with no triangles.
  /// \param context A pointer to an object through which the Mesh will be able
  ///   to make OpenGL calls.
  /// \param[in] shaderProgram A pointer to the ShaderProgram that should
  ///   be used.
  /// \post A unique VAO and VBO have been generated for this Mesh and stored
  ///   for later use.
  ColorsMesh (OpenGLContext* context, ShaderProgram* shaderProgram);  

  /// \brief Destructs this Mesh.
  /// \post The VAO and VBO associated with this Mesh have been deleted.
  ~ColorsMesh ();

  /// \brief Gets the number of floats used to represent each vertex.
  /// \return The number of floats used for each vertex.
  unsigned int
  getFloatsPerVertex () const;

  /// \brief Enables VAO attributes.
  /// \pre This Mesh's VAO has been bound.
  /// \post Any attributes (positions, colors, normals, texture coordinates)
  ///   have been enabled and configured.
  /// This should only be called from the middle of prepareVao().
  void
  enableAttributes();

  void
  draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition);

};

#endif//COLORSMESH_HPP