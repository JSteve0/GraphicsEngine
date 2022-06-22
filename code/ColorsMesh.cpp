/// \file ColorsMesh.cpp
/// \brief Definition of ColorsMesh class and any associated global functions.
/// \author Justin Stevens
/// \version A08

#include "ColorsMesh.hpp"

ColorsMesh::ColorsMesh (OpenGLContext* context, ShaderProgram* shaderProgram)
: Mesh(context, shaderProgram)
{

}

ColorsMesh::~ColorsMesh ()
{

}

unsigned int
ColorsMesh::getFloatsPerVertex () const
{
  return 6;
}

void
ColorsMesh::enableAttributes()
{
  Mesh::enableAttributes();
}

void
ColorsMesh::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition)
{
  // Iterate over each object in scene and draw it
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  m_shaderProgram->enable ();

  Transform modelView = viewMatrix * m_world;
  m_shaderProgram->setUniformMatrix ("uModelView", modelView.getTransform());
  m_shaderProgram->setUniformMatrix ("uProjection", projectionMatrix);
  m_shaderProgram->setUniformInt("uHasTexture", 0);


  // Draw geometry
  m_context->bindVertexArray (m_vao);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT,
    reinterpret_cast<void*> (0));
  m_context->bindVertexArray (0);

  m_shaderProgram->disable ();
}