/// \file Mesh.cpp
/// \brief Definition of Mesh class and all associated global functions.
/// \author Justin Stevens
/// \version A09

#include "Mesh.hpp"
#include "Geometry.hpp"
#include "ShaderProgram.hpp"

Mesh::Mesh (OpenGLContext* context, ShaderProgram* shaderProgram) 
{
  m_context = context;

  m_shaderProgram = shaderProgram;
  // Generate VAO
  m_context->genVertexArrays (1, &m_vao);
  // Generate buffer
  m_context->genBuffers (1, &m_vbo);
  m_context->genBuffers (1, &m_ibo);
}

Mesh::Mesh (OpenGLContext* context, ShaderProgram* shaderProgram, Material* material)
  : m_material(material)
{
  m_context = context;

  m_shaderProgram = shaderProgram;
  // Generate VAO
  m_context->genVertexArrays (1, &m_vao);
  // Generate buffer
  m_context->genBuffers (1, &m_vbo);
  m_context->genBuffers (1, &m_ibo);
}

Mesh::~Mesh () 
{
  // Deletes VAO
  m_context->deleteVertexArrays (1, &m_vao);
  // Deletes VBO & IBO
  m_context->deleteBuffers(1, &m_vbo);
  m_context->deleteBuffers(1, &m_ibo);
}

void
Mesh::addGeometry (const std::vector<float>& geometry) 
{
  m_vertices.insert(std::end(m_vertices), std::begin(geometry), std::end(geometry));
}

void
Mesh::prepareVao () 
{
  m_context->bindBuffer(GL_ARRAY_BUFFER, m_vbo);
  m_context->bindVertexArray (m_vao);
  m_context->bufferData (GL_ARRAY_BUFFER, m_vertices.size () * sizeof (float),
      m_vertices.data (), GL_STATIC_DRAW);

  m_context->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  m_context->bufferData (GL_ELEMENT_ARRAY_BUFFER, m_indices.size () * sizeof (float),
      m_indices.data (), GL_STATIC_DRAW);

  enableAttributes();

  m_context->bindVertexArray (0);
}

void
Mesh::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition) 
{
  // Iterate over each object in scene and draw it
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  m_shaderProgram->enable ();

  Transform modelView = viewMatrix * m_world;
  m_shaderProgram->setUniformMatrix ("uModelView", modelView.getTransform());
  m_shaderProgram->setUniformMatrix ("uProjection", projectionMatrix);
  
  if (m_material != NULL) {
    m_material->setUniforms(m_shaderProgram);
  }
  m_shaderProgram->setUniformInt("uHasTexture", 0);

  // Draw geometry
  m_context->bindVertexArray (m_vao);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT,
    reinterpret_cast<void*> (0));
  m_context->bindVertexArray (0);

  m_shaderProgram->disable ();
}

Transform
Mesh::getWorld () const
{
  return m_world;
}

void
Mesh::moveRight (float distance)
{
  m_world.moveRight(distance);
}

void
Mesh::moveUp (float distance)
{
  m_world.moveUp(distance);
}

void
Mesh::moveBack (float distance)
{
  m_world.moveBack(distance);
}

void
Mesh::moveLocal (float distance, const Vector3& localDirection)
{
  m_world.moveLocal(distance, localDirection);
}

void
Mesh::moveWorld (float distance, const Vector3& worldDirection)
{
  m_world.moveWorld(distance, worldDirection);
}

void
Mesh::pitch (float angleDegrees)
{
  m_world.pitch(angleDegrees);
}

void
Mesh::yaw (float angleDegrees)
{
  m_world.yaw(angleDegrees);
}

void
Mesh::roll (float angleDegrees)
{
  m_world.roll(angleDegrees);
}

void
Mesh::rotateLocal (float angleDegrees, const Vector3& axis)
{
  m_world.rotateLocal(angleDegrees, axis);
}

void
Mesh::alignWithWorldY ()
{
  m_world.alignWithWorldY();
}

void
Mesh::scaleLocal (float scale)
{
  m_world.scaleLocal(scale);
}

void
Mesh::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
  m_world.scaleLocal(scaleX, scaleY, scaleZ);
}
  
void
Mesh::scaleWorld (float scale)
{
  m_world.scaleWorld(scale);
}

void
Mesh::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
  m_world.scaleWorld(scaleX, scaleY, scaleZ);
}

void
Mesh::shearLocalXByYz (float shearY, float shearZ)
{
  m_world.shearLocalXByYz(shearY, shearZ);
}

void
Mesh::shearLocalYByXz (float shearX, float shearZ)
{
  m_world.shearLocalYByXz(shearX, shearZ);
}

void
Mesh::shearLocalZByXy (float shearX, float shearY)
{
  m_world.shearLocalZByXy(shearX, shearY);
}

Vector3
Mesh::getPosition()
{
  return m_world.getPosition();
}

/// \brief Adds additional triangles to this Mesh.
/// \param[in] indices A collection of indices into the vertex buffer for 1
///   or more triangles.  There must be 3 indices per triangle.
/// \pre This Mesh has not yet been prepared.
/// \post The indices have been appended to this Mesh's internal index store
///   for future use.
void
Mesh::addIndices (const std::vector<unsigned int>& indices)
{
  m_indices.insert(std::end(m_indices), std::begin(indices), std::end(indices));
}

/// \brief Gets the number of floats used to represent each vertex.
/// \return The number of floats used for each vertex.
unsigned int
Mesh::getFloatsPerVertex () const
{
  return 6;
}

/// \brief Enables VAO attributes.
/// \pre This Mesh's VAO has been bound.
/// \post Any attributes (positions, colors, normals, texture coordinates)
///   have been enabled and configured.
/// This should only be called from the middle of prepareVao().
void
Mesh::enableAttributes()
{
  // These control how our C++ program communicates with the shaders
  const GLint POSITION_ATTRIB_INDEX = 0;
  const GLint COLOR_ATTRIB_INDEX = 1;

  // Tell the shaders how the data in the array is laid out
  m_context->enableVertexAttribArray (POSITION_ATTRIB_INDEX);
  // Positions have 3 parts, each are floats, start at beginning of array, stride is 6
  m_context->vertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
          reinterpret_cast<void*> (0));
  m_context->enableVertexAttribArray (COLOR_ATTRIB_INDEX);
  // Colors have 3 parts, each are floats, start at 3rd position in array, stride is 6
  m_context->vertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
          reinterpret_cast<void*> (3 * sizeof(float)));
}