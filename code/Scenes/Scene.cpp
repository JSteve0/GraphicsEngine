/// \file Scene.cpp
/// \brief Definition of Scene class and all associated global functions.
/// \author Justin Stevens
/// \version A09

#include "Scene.hpp"

Scene::Scene (ShaderProgram* shader)
  : m_shaderProgram(shader)
{

}

Scene::~Scene () 
{
  clear();
}

void
Scene::add (const std::string& meshName, Mesh* mesh) 
{
  if (!hasMesh(meshName)) 
    m_meshes.insert( {meshName, mesh} ); 
  if (m_meshes.size() == 1) 
    m_activeMesh = m_meshes.begin();
}

void
Scene::remove (const std::string& meshName) 
{
  if (m_activeMesh->first == meshName) 
    activateNextMesh();
  if (hasMesh(meshName)) {
    delete m_meshes.find(meshName)->second;
    m_meshes.erase(meshName);
  }
}

void
Scene::clear () {
  //Unallocate meshes
  for (auto& it : m_meshes) 
    delete it.second;
  //Unallocate light sources
  for (auto& light : m_lights) 
    delete light;
  for (auto& material : m_materials) 
    delete material;
  for (auto& obj : m_physicsObjects) 
    delete obj;
  for (auto& tex : m_textures)
    delete tex;
}

void
Scene::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPostion) {
  m_shaderProgram->enable();
  m_shaderProgram->setUniformInt("uNumLights", m_lights.size());

  m_shaderProgram->setUniformVector("uAmbientIntensity", Vector3(0.001f, 0.01f, 0.001f));

  for (int i = 0; i < m_lights.size(); ++i)
    m_lights[i]->setUniforms(m_shaderProgram, i);

  for (auto const& it : m_meshes) 
    it.second->draw(viewMatrix, projectionMatrix, cameraPostion);
  
  m_shaderProgram->disable();
}

bool
Scene::hasMesh (const std::string& meshName) {
  auto it = m_meshes.find(meshName);
  if (it == m_meshes.end()) return false;
  return true;
}

Mesh*
Scene::getMesh (const std::string& meshName) {
  auto mesh = m_meshes.find(meshName);
  if (mesh == m_meshes.end()) return nullptr;
  return mesh->second;
}

void
Scene::setActiveMesh (const std::string& meshName)
{
  m_activeMesh = m_meshes.find(meshName);
}

Mesh*
Scene::getActiveMesh ()
{
  return m_activeMesh->second;
}

void
Scene::activateNextMesh ()
{
  ++m_activeMesh;
  if (m_activeMesh == m_meshes.end()) 
    m_activeMesh = m_meshes.begin();
}

void
Scene::activatePreviousMesh ()
{
  if (m_activeMesh == m_meshes.begin()) 
    m_activeMesh = --m_meshes.end();
  else 
    --m_activeMesh;
}

void 
Scene::addLightSource (LightSource* light)
{
  if (m_lights.size() < MAX_LIGHT_SOURCES)
  {
    m_lights.push_back(light);
  } else {
    throw std::invalid_argument( "Number of light sources exceeds" + std::to_string(MAX_LIGHT_SOURCES) );
  }
}

void 
Scene::addMaterial (Material* material)
{
  m_materials.push_back(material);
}

void 
Scene::addPhysicsObject (PhysicsObject* PhysicsObject)
{
  m_physicsObjects.push_back(PhysicsObject);
}

void 
Scene::addTexture (Texture* texture)
{
  m_textures.push_back(texture);
}

void 
Scene::update (float deltaTime)
{

}

void
Scene::processKeys (KeyBuffer* keyBuffer, float deltaTime)
{
  
}

void 
Scene::resetCamera(Camera* camera)
{
  camera->resetPose();
}