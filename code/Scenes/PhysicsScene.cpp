/// \file PhysicsScene.cpp
/// \brief Definition of PhysicsScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "PhysicsScene.hpp"

PhysicsScene::PhysicsScene (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram) 
  : Scene::Scene(normalShaderProgram)
{
  Material* brickMaterial = new Material(
    Vector3(0.6f, 0.6f, 0.6f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.01f, 0.01f, 0.01f),
    0.2f
  );

  Material* marbleMaterial = new Material(
    Vector3(0.6f, 0.6f, 0.6f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.01f, 0.01f, 0.01f),
    0.2f
  );

  Material* ceilingMaterial = new Material(
    Vector3(0.6f, 0.6f, 0.6f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.01f, 0.01f, 0.01f),
    0.2f
  );

  Material* sphereMaterial = new Material(
    Vector3(0.3f, 0.3f, 0.3f),
    Vector3(0.4f, 0.4f, 0.4f),
    Vector3(0.1f, 0.1f, 0.1f),
    Vector3(0.1f, 0.1f, 0.1f),
    0.5f
  );

  addMaterial(brickMaterial);
  addMaterial(marbleMaterial);
  addMaterial(ceilingMaterial);
  addMaterial(sphereMaterial);

  addLightSource(
    new PointLightSource(
      Vector3(0.7f, 0.7f, 0.7f), // Diffuse (r, g, b)
      Vector3(0.6f, 0.6f, 0.6f), // Specular (r, g, b)
      Vector3(0.0f, 2.0f, 0.0f), // Position (x, y, z)
      Vector3(0.0015f, 0.0015f, 0.0015f) // AttenuationCoefficients, Higher value makes it dimmer over distance.
    )
  );

  addLightSource(
    new SpotLightSource(
      Vector3(0.9f, 0.9f, 0.9f), // Diffuse (r, g, b)
      Vector3(0.2f, 0.2f, 0.2f), // Specular (r, g, b)
      Vector3(0.0f, 0.0f, 50.0f), // Position (x, y, z)
      Vector3(0.01f, 0.01f, 0.01f), // AttenuationCoefficients 
      Vector3(0.0f, 0.0f, -1.0f), // Direction (x, y, z)
      0.2f, // cutoffCosAngle, lower makes range wider
      0.25f // falloff, higher decreases distance
    )
  );

  Texture* brickTexture = new Texture("Textures/Brick.png");
  addTexture(brickTexture);
  Texture* marbleTexture = new Texture("Textures/Marble.jpeg");
  addTexture(marbleTexture);
  Texture* ceilingTexture = new Texture("Textures/Ceiling.jpeg");
  addTexture(ceilingTexture);
  Texture* soccerballTexture = new Texture("Textures/Soccerball.jpg");
  addTexture(soccerballTexture);
  Texture* paddleTexture = new Texture("Textures/Paddle.jpeg");
  addTexture(paddleTexture);

  std::vector<float> data;
  std::vector<unsigned int> indices;
  std::vector<float> geometry;

  geometry = buildTexturedRect(Vector3(-20.0f, 10.0f, -20.0f), Vector3(40.0f, 30.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), 5.0f);
  std::vector<float> temp = buildTexturedRect(Vector3(20.0f, 10.0f, 20.0f), Vector3(-40.0f, 30.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), 5.0f);
  geometry.insert(std::end(geometry), std::begin(temp), std::end(temp));
  temp.clear();
  temp = buildTexturedRect(Vector3(20.0f, 10.0f, -20.0f), Vector3(20.0f, -20.0f, -20.0f), Vector3(20.0f, -20.0f, 20.0f), Vector3(20.0f, 10.0f, 20.0f), Vector3(-1.0f, 0.0f, 0.0f), 5.0f);
  geometry.insert(std::end(geometry), std::begin(temp), std::end(temp));
  temp.clear();
  temp = buildTexturedRect(Vector3(-20.0f, 10.0f, 20.0f), Vector3(-20.0f, -20.0f, 20.0f), Vector3(-20.0f, -20.0f, -20.0f), Vector3(-20.0f, 10.0f, -20.0f), Vector3(1.0f, 0.0f, 0.0f), 5.0f);
  geometry.insert(std::end(geometry), std::begin(temp), std::end(temp));
  TexturedNormalsMesh* brickMeshWall = new TexturedNormalsMesh(context, normalShaderProgram, brickMaterial, brickTexture);
  indexData(geometry, brickMeshWall->getFloatsPerVertex(), data, indices);
  brickMeshWall->addGeometry(data);
  brickMeshWall->addIndices(indices);
  brickMeshWall->prepareVao();
  add("Wall", brickMeshWall);

  indices.clear();
  data.clear();
  geometry.clear();

  geometry = buildTexturedRect(Vector3(-20.0f, -20.0f, -20.0f), Vector3(40.0f, 0.0f, 40.0f), Vector3(0.0f, 1.0f, 0.0f), 5.0f);
  TexturedNormalsMesh* brickMeshFloor = new TexturedNormalsMesh(context, normalShaderProgram, brickMaterial, marbleTexture);
  indexData(geometry, brickMeshFloor->getFloatsPerVertex(), data, indices);
  brickMeshFloor->addGeometry(data);
  brickMeshFloor->addIndices(indices);
  brickMeshFloor->prepareVao();
  add("Floor", brickMeshFloor);

  indices.clear();
  data.clear();
  geometry.clear();

  geometry = buildTexturedRect(Vector3(-20.0f, 10.0f, 20.0f), Vector3(40.0f, 0.0f, -40.0f), Vector3(0.0f, -1.0f, 0.0f), 5.0f);
  TexturedNormalsMesh* brickMeshRoof = new TexturedNormalsMesh(context, normalShaderProgram, ceilingMaterial, ceilingTexture);
  indexData(geometry, brickMeshRoof->getFloatsPerVertex(), data, indices);
  brickMeshRoof->addGeometry(data);
  brickMeshRoof->addIndices(indices);
  brickMeshRoof->prepareVao();
  add("Ceilling", brickMeshRoof);

  indices.clear();
  data.clear();
  geometry.clear();

  TexturedNormalsMesh* sphere = new TexturedNormalsMesh(context, normalShaderProgram, "models/sphere.obj", 0, sphereMaterial, soccerballTexture, 1.0f);
  //NormalsMesh* sphere = new NormalsMesh(context, normalShaderProgram, "models/sphere.obj", 0, sphereMaterial/*, ceilingTexture*/);
  sphere->scaleLocal(0.2);

  sphere->prepareVao();
  add("Sphere", sphere);


  NormalsMesh* player = new NormalsMesh(context, normalShaderProgram, "models/slime.obj", 0, sphereMaterial);
  player->prepareVao();
  add("Player3D", player);
  player->moveWorld(1.0, Vector3(0.0, -10.0, 18.0));
  player->scaleLocal(6.0, 6.0, 0.5);

  NormalsMesh* opponent = new NormalsMesh(context, normalShaderProgram, "models/slime.obj", 0, sphereMaterial);
  opponent->prepareVao();
  add("Opponent", opponent);
  opponent->moveWorld(1.0, Vector3(0.0, -10.0, -18.0));
  opponent->scaleLocal(6.0, 6.0, 0.5);

  float paddleSpeed = 20.0f;
  m_player = new Player(player, Vector3(6.0, 6.0, 1.0), paddleSpeed);
  m_AI = new AI(opponent, Vector3(6.0, 6.0, 1.0), paddleSpeed);
  m_ball = new Ball(sphere, Vector3(1.5f, 1.5f, 1.5f), Vector3(7.0f, 7.0f, 20.0f));

  m_gamestate = 0;
}

void 
PhysicsScene::update (float deltaTime)
{
  if (m_gamestate != 0)
  {
    if (m_ball->update3D(deltaTime, -20.0f, 20.0f, 10.0f, -20.0f, 20.0, -20.0))
    {
      m_gamestate = 0;
    }
    m_AI->update3D(m_ball, deltaTime, -20.0f, 10.0f, -20.0f, 20.0f);
    if (m_ball->collides3D(m_player) || m_ball->collides3D(m_AI))
    {
      m_ball->bounce3D();
    }
  } else {
    m_ball->setVelocity(Vector3(7.0f, 7.0f, 20.0f));
  }
}

void
PhysicsScene::processKeys (KeyBuffer* keyBuffer, float deltaTime)
{
  if(keyBuffer->isKeyDown(GLFW_KEY_UP))
  {
    m_player->moveUp(deltaTime, 10.0f);
  }
  else if(keyBuffer->isKeyDown(GLFW_KEY_DOWN))
  {
    m_player->moveDown(deltaTime, -20.0f);
  }
  if(keyBuffer->isKeyDown(GLFW_KEY_LEFT))
  {
    m_player->moveLeft(deltaTime, -20.0f);
  }
  else if(keyBuffer->isKeyDown(GLFW_KEY_RIGHT))
  {
    m_player->moveRight(deltaTime, 20.0f);
  }
  if(keyBuffer->isKeyDown(GLFW_KEY_SPACE))
  {
    m_gamestate = 1;
    m_ball->reset3D();
    keyBuffer->setKeyUp(GLFW_KEY_SPACE);
  }
}

PhysicsScene::~PhysicsScene() 
{
  delete m_player;
  delete m_AI;
  delete m_ball;
}

void
PhysicsScene::resetCamera(Camera* camera)
{
  camera->resetPose();
  camera->moveBack(40.0f);
  camera->moveUp(-5.0f);
}