/// \file TexturedNormalsMesh.hpp
/// \brief Declaration of NormalsMesh class and any associated global functions.
/// \author Chad Hogg & Justin Stevens & Aaron
/// \version A09

#ifndef TEXTUREDNORMALSMESH_HPP
#define TEXTUREDNORMALSMESH_HPP

#include "Mesh.hpp"
#include "Material.hpp"
#include "NormalsMesh.hpp"
#include "Texture.hpp"
#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include <FreeImagePlus.h>
#include <string>

class TexturedNormalsMesh : public NormalsMesh 
{
public:
  
  /// \brief Constructs an empty Mesh with no triangles.
  /// \param context A pointer to an object through which the Mesh will be able
  ///   to make OpenGL calls.
  /// \param[in] shaderProgram A pointer to the ShaderProgram that should
  ///   be used.
  /// \post A unique VAO and VBO have been generated for this Mesh and stored
  ///   for later use.
  TexturedNormalsMesh (OpenGLContext* context, ShaderProgram* shaderProgram, Material* material, Texture* texture);

  /// \brief Constructs a NormalsMesh with triangles pulled from a file.
  /// \param[in] context A pointer to an objec tthrough which the Mesh will be
  ///   able to make OpenGL calls.
  /// \param[in] shader A pointer to the shader program that should be used for
  ///   drawing this mesh.
  /// \param[in] fileName The name of the file this mesh's geometry should be
  ///   read from.
  /// \param[in] meshNum The 0-based index of which mesh from that file should
  ///   be used.
  /// \post A unique VAO, VBO, and IBO have been generated for this Mesh and
  ///   stored for later use.
  /// \post If that file exists and contains a mesh of that number, the indexes
  ///   and geometry from it have been pre-populated into this Mesh.  Otherwise
  ///   this Mesh is empty and an error message has been printed.
  TexturedNormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum, Material* material, Texture* texture, float detail);

  /// \brief Destructs this Mesh.
  /// \post The VAO and VBO associated with this Mesh have been deleted.
  ~TexturedNormalsMesh ();

  void
  draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition);

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

private:
  Texture* m_texture;
};

#endif//TEXTUREDNORMALMESH_HPP