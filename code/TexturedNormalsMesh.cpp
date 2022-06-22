#include "TexturedNormalsMesh.hpp"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

TexturedNormalsMesh::TexturedNormalsMesh (OpenGLContext* context, ShaderProgram* shaderProgram, Material* material, Texture* texture)
  : NormalsMesh(context, shaderProgram, material)
{
  m_texture = texture;
  m_texture->loadTextureID(m_tid);
}

TexturedNormalsMesh::TexturedNormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum, Material* material, Texture* texture, float detail)
  : NormalsMesh(context, shader, material)
{
  m_texture = texture;
  m_texture->loadTextureID(m_tid);
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
        //Load uv texture cordinates
        if (mesh->HasTextureCoords(0))
        {
          vertexData.push_back (mesh->mTextureCoords[0][vertexNum].x * detail);
          vertexData.push_back (mesh->mTextureCoords[0][vertexNum].y * detail);
        } else {
          vertexData.push_back (0.0f);
          vertexData.push_back (0.0f);
        }
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

TexturedNormalsMesh::~TexturedNormalsMesh ()
{

}

void
TexturedNormalsMesh::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPosition)
{
  // Iterate over each object in scene and draw it
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  m_shaderProgram->enable ();

  m_shaderProgram->setUniformMatrix ("uWorld", m_world.getTransform());
  m_shaderProgram->setUniformMatrix ("uView", viewMatrix.getTransform());
  m_shaderProgram->setUniformMatrix ("uProjection", projectionMatrix);
  
  m_shaderProgram->setUniformVector ("uEyePosition", Vector3(0.0f, 0.0f, 0.0f));

  m_material->setUniforms(m_shaderProgram);
  m_shaderProgram->setUniformInt("uHasTexture", 1);

  // Draw Texture
  glActiveTexture (GL_TEXTURE0);
  glBindTexture (GL_TEXTURE_2D, m_tid);
  m_shaderProgram->setUniformInt("uDiffuseSampler", 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  // Draw geometry
  m_context->bindVertexArray (m_vao);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT,
    reinterpret_cast<void*> (0));
  m_context->bindVertexArray (0);

  m_shaderProgram->disable ();
}

unsigned int
TexturedNormalsMesh::getFloatsPerVertex () const
{
  return 8;
}

void
TexturedNormalsMesh::enableAttributes()
{
  // These control how our C++ program communicates with the shaders
  const GLint POSITION_ATTRIB_INDEX = 0;
  const GLint NORMALS_ATTRIB_INDEX = 2;
  const GLint TEXTURE_ATTRIB_INDEX = 3;
  
  // Tell the shaders how the data in the array is laid out
  m_context->enableVertexAttribArray (POSITION_ATTRIB_INDEX);
  // Positions have 3 parts, each are floats, start at beginning of array, stride is 8
  m_context->vertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
          reinterpret_cast<void*> (0));
  m_context->enableVertexAttribArray (NORMALS_ATTRIB_INDEX);
  // Normals have 3 parts, each are floats, start at 3rd position in array, stride is 8
  m_context->vertexAttribPointer (NORMALS_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
          reinterpret_cast<void*> (3 * sizeof(float)));
  m_context->enableVertexAttribArray (TEXTURE_ATTRIB_INDEX);
  // Textures have 2 parts, each are floats, start at 6th position in array, stride is 8
  m_context->vertexAttribPointer (TEXTURE_ATTRIB_INDEX, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
          reinterpret_cast<void*> (6 * sizeof(float)));
}