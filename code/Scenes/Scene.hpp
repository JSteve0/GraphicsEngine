/// \file Scene.hpp
/// \brief Declaration of Scene class and any associated global functions.
/// \author Chad Hogg and Justin Stevens
/// \version A09

#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <map>
#include <stdexcept>

#include "../Mesh.hpp"
#include "../ShaderProgram.hpp"
#include "../Matrix4.hpp"
#include "../Vector3.hpp"
#include "../LightSource.hpp"
#include "../Material.hpp"
#include "../PhysicsObject.hpp"
#include "../Texture.hpp"
#include "../KeyBuffer.hpp"
#include "../Camera.hpp"

/// \brief A collection of all the objects that exist in the world.
class Scene
{
public:
  
  /// \brief Constructs an empty Scene.
  Scene (ShaderProgram* shader);

  /// \brief Destructs a Scene, freeing the memory used by any Meshes in it.
  /// \post Any Meshes that were part of the Scene have been freed.
  virtual
  ~Scene ();

  /// \brief Copy constructor removed because you shouldn't be copying Scenes.
  Scene (const Scene&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   Scenes.
  void
  operator= (const Scene&) = delete;

  /// \brief Adds a new Mesh to this Scene.
  /// \param[in] meshName The name of the Mesh.  Unique names should be used so
  ///   that you can access it in the future.
  /// \param[in] mesh A pointer to the Mesh that should be added.  This Mesh
  ///   must have been dynamically allocated.  The Scene will now own this Mesh
  ///   and be responsible for de-allocating it.
  /// \pre The Scene does not contain any Mesh associated with meshName.
  /// \post The Scene contains the mesh, associated with the meshName.
  void
  add (const std::string& meshName, Mesh* mesh);

  /// \brief Removes a Mesh from this Scene.
  /// \param[in] meshName The name of the Mesh that should be removed.
  /// \pre This Scene contains a Mesh associated with meshName.
  /// \post This Scene no longer associates meshName with anything.
  /// \post The Mesh that had been associated with meshName has been freed.
  void
  remove (const std::string& meshName);

  /// \brief Removes all Meshes from this Scene.
  /// \post This Scene is empty.
  /// \post All Meshes that had been part of this Scene have been freed.
  void
  clear ();

  /// \brief Draws all of the elements in this Scene.
  /// \param[in] viewMatrix The view matrix that should be used when drawing
  ///   the Scene.
  /// \param[in] projectionMatrix The projection matrix that should be used when drawing
  ///   the Scene.
  void
  draw (const Transform& viewMatrix, const Matrix4& projectionMatrix, const Vector3& cameraPostion);

  /// \brief Tests whether or not this Scene contains a Mesh associated with a
  ///   name.
  /// \param[in] meshName The name of the requested Mesh.
  /// \return Whether or not this Scene contains a Mesh associated with
  ///   meshName.
  bool
  hasMesh (const std::string& meshName);

  /// \brief Gets the Mesh associated with a name.
  /// \param[in] meshName The name of the requested Mesh.
  /// \return A pointer to the Mesh associated with meshName.  This pointer
  ///   should not be permanently stored, as the Mesh it points to will be
  ///   deallocated with this Scene.
  /// \pre This Scene has a Mesh assocated with meshName.
  Mesh*
  getMesh (const std::string& meshName);

  /// \brief Sets the active mesh to the mesh named "meshName".
  /// The active mesh is the one affected by transforms.
  /// \param[in] meshName The name of the mesh that should be active.
  /// \pre The scene contains a mesh with that name.
  /// \post The mesh with that name becomes the active mesh.
  void
  setActiveMesh (const std::string& meshName);

  /// \brief Gets the active mesh.
  /// \pre The scene has at least one mesh.
  /// \return The active mesh.
  Mesh*
  getActiveMesh ();

  /// \brief Switches active meshes in the forward direction.
  /// \pre The scene has at least one mesh.
  /// \post The next mesh becomes active.  If the last mesh was active, the
  ///   first mesh becomes active.
  void
  activateNextMesh ();

  /// \brief Switches active meshes in the backward direction.
  /// \pre The scene has at least one mesh.
  /// \post The previous mesh becomes active.  If the first mesh was active,
  ///   the last mesh becomes active.
  void
  activatePreviousMesh ();

  void 
  addLightSource (LightSource* light);

  void 
  addMaterial (Material* material);

  void 
  addPhysicsObject (PhysicsObject* PhysicsObject);

  void 
  addTexture (Texture* texture);

  virtual void 
  update (float deltaTime);
  
  virtual void 
  processKeys (KeyBuffer* keyBuffer, float deltaTime);

  virtual void 
  resetCamera(Camera* camera);

protected:
  /// Keep track of the light sources in the scene.
  std::vector <LightSource*> m_lights;
  ///
  const int MAX_LIGHT_SOURCES = 8;

  std::vector <PhysicsObject*> m_physicsObjects;

  ShaderProgram* m_shaderProgram;
private:
  /// Keeps track of all the meshes in the scene with an associated name.
  std::map <std::string, Mesh*> m_meshes;
  /// Keeps track of the active mesh in the scene.
  std::map <std::string, Mesh*>::iterator m_activeMesh;
  /// Keeps track of all the materials.
  std::vector <Material*> m_materials;
  /// Keeps track of all the textures
  std::vector <Texture*> m_textures;
};

#endif//SCENE_HPP
