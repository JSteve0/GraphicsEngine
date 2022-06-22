/// \file NormalsMesh.cpp
/// \brief Definition of NormalsMesh class and any associated global functions.
/// \author Chad Hogg & Justin Stevens
/// \version A08

#include "NormalsMesh.hpp"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

NormalsMesh::NormalsMesh (OpenGLContext* context, ShaderProgram* shaderProgram, Material* material)
  : Mesh(context, shaderProgram, material)
{

}

NormalsMesh::NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum, Material* material)
  : Mesh (context, shader, material)
{
  Assimp::Importer importer;
  unsigned int flags =
    aiProcess_Triangulate              // convert all shapes to triangles
    | aiProcess_GenSmoothNormals       // create vertex normals if not there
    | aiProcess_JoinIdenticalVertices; // combine vertices for indexing
  const aiScene* scene = importer.ReadFile (filename, flags);
  if (scene == nullptr)
  {
    auto error = importer.GetErrorString ();
    std::cerr << "Failed to load model " << filename << " with error " << error << std::endl;
  }
  else
  {
    if(meshNum >= scene->mNumMeshes)
    {
      std::cerr << "Could not read mesh " << meshNum << " from " << filename << " because it only has " << scene->mNumMeshes << " meshes." << std::endl;
    }
    else
    {
      const aiMesh* mesh = scene->mMeshes[meshNum];
      std::vector<float> vertexData;
      std::vector<unsigned int> indexes;
      for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
      {
        vertexData.push_back (mesh->mVertices[vertexNum].x);
        vertexData.push_back (mesh->mVertices[vertexNum].y);
        vertexData.push_back (mesh->mVertices[vertexNum].z);
        vertexData.push_back (mesh->mNormals[vertexNum].x);
        vertexData.push_back (mesh->mNormals[vertexNum].y);
        vertexData.push_back (mesh->mNormals[vertexNum].z);
      }
      for (unsigned int faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
      {
        const aiFace& face = mesh->mFaces[faceNum];
        for (unsigned int indexNum = 0; indexNum < 3; ++indexNum)
        {
          unsigned int vertexNum = face.mIndices[indexNum];
          indexes.push_back (vertexNum);
        }
      }
      addGeometry (vertexData);
      addIndices (indexes);

      //Set material
      const aiMaterial* material = scene->mMaterials[meshNum];
      aiColor3D color;

      if (material->Get (AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS && !color.IsBlack()) 
      {
        m_material->m_ambient.set(color.r, color.g, color.b);
      }
      if (material->Get (AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS && !color.IsBlack()) 
      {
        m_material->m_diffuse.set(color.r, color.g, color.b);
      }
      if (material->Get (AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS && !color.IsBlack()) 
      {
        m_material->m_specular.set(color.r, color.g, color.b);
      }
      if (material->Get (AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS && !color.IsBlack()) 
      {
        m_material->m_emmissiveIntensity = Vector3(color.r, color.g, color.b);
      }
      float shininess;
      if (material->Get (AI_MATKEY_SHININESS, shininess) == AI_SUCCESS && shininess != 0.0f) 
      {
        m_material->m_specularPower = shininess;
      }
    }
  }
}

NormalsMesh::~NormalsMesh ()
{

}

void
NormalsMesh::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition) 
{
  // Iterate over each object in scene and draw it
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  m_shaderProgram->enable ();

  m_shaderProgram->setUniformMatrix ("uWorld", m_world.getTransform());
  m_shaderProgram->setUniformMatrix ("uView", viewMatrix.getTransform());
  m_shaderProgram->setUniformMatrix ("uProjection", projectionMatrix);

  //m_shaderProgram->setUniformVector ("uEyePosition", cameraPosition);
  m_shaderProgram->setUniformVector ("uEyePosition", Vector3(0.0f, 0.0f, 0.0f));
  m_shaderProgram->setUniformInt("uHasTexture", 0);

  m_material->setUniforms(m_shaderProgram);

  // Draw geometry
  m_context->bindVertexArray (m_vao);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT,
    reinterpret_cast<void*> (0));
  m_context->bindVertexArray (0);

  m_shaderProgram->disable ();
}

unsigned int
NormalsMesh::getFloatsPerVertex () const
{
  return 6;
}

void
NormalsMesh::enableAttributes()
{
  // These control how our C++ program communicates with the shaders
  const GLint POSITION_ATTRIB_INDEX = 0;
  const GLint NORMALS_ATTRIB_INDEX = 2;
  
  // Tell the shaders how the data in the array is laid out
  m_context->enableVertexAttribArray (POSITION_ATTRIB_INDEX);
  // Positions have 3 parts, each are floats, start at beginning of array, stride is 6
  m_context->vertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
          reinterpret_cast<void*> (0));
  m_context->enableVertexAttribArray (NORMALS_ATTRIB_INDEX);
  // Normals have 3 parts, each are floats, start at 3rd position in array, stride is 6
  m_context->vertexAttribPointer (NORMALS_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
          reinterpret_cast<void*> (3 * sizeof(float)));
}