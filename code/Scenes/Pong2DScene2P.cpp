/// \file Pong2DScene2P.hpp
/// \brief Definition of Pong2DScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "Pong2DScene2P.hpp"

Pong2DScene2P::Pong2DScene2P (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram) 
  : Scene::Scene(normalShaderProgram)
{
  Material* material = new Material(
    Vector3(0.01f, 0.01f, 0.01f),
    Vector3(0.01f, 0.01f, 0.01f),
    Vector3(0.01f, 0.01f, 0.01f),
    Vector3(0.1f, 0.1f, 0.1f),
    0.5f
  );

  addMaterial(material);

  Material* backgroundMaterial = new Material(
    Vector3(1.0f, 1.0f, 1.0f),
    Vector3(0.7f, 0.7f, 0.7f),
    Vector3(0.1f, 0.1f, 0.1f),
    Vector3(0.1f, 0.1f, 0.1f),
    0.5f
  );

  addMaterial(backgroundMaterial);

  addLightSource(
    new PointLightSource(
      Vector3(0.7f, 0.7f, 0.7f), // Diffuse (r, g, b)
      Vector3(0.6f, 0.6f, 0.6f), // Specular (r, g, b)
      Vector3(0.0f, 0.0f, 13.0f), // Position (x, y, z)
      Vector3(0.003f, 0.003f, 0.003f) // AttenuationCoefficients, Higher value makes it dimmer over distance.
    )
  );

  Texture* marbleTexture = new Texture("Textures/Marble.jpeg");
  Texture* brickTexture = new Texture("Textures/Brick.png");

  addTexture(marbleTexture);
  addTexture(brickTexture);

  std::vector<float> data;
  std::vector<unsigned int> indices;
  std::vector<float> geometry;


  geometry = buildRect(Vector3(-10.0f, 5.0f, -1.0f), Vector3(20.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
  NormalsMesh* board = new NormalsMesh(context, normalShaderProgram, backgroundMaterial);
  indexData(geometry, board->getFloatsPerVertex(), data, indices);
  board->addGeometry(data);
  board->addIndices(indices);
  board->prepareVao();
  add("Board", board);

  data.clear();
  indices.clear();
  geometry.clear();

  Vector3 size (0.25f, 2.0f, 0.0f);
  Vector3 pos (8.0f, size.m_y / 2.0f, -0.75f);

  geometry = buildRect(Vector3(-(size.m_x / 2.0f), pos.m_y, pos.m_z), size, Vector3(0.0f, 0.0f, 1.0f));
  NormalsMesh* player = new NormalsMesh(context, normalShaderProgram, material);
  indexData(geometry, player->getFloatsPerVertex(), data, indices);
  player->addGeometry(data);
  player->addIndices(indices);
  player->prepareVao();
  add("Player", player);
  player->moveRight(-pos.m_x);

  data.clear();
  indices.clear();
  geometry.clear();

  geometry = buildRect(Vector3(-size.m_x / 2.0f, pos.m_y, pos.m_z), size, Vector3(0.0f, 0.0f, 1.0f));
  NormalsMesh* opponent = new NormalsMesh(context, normalShaderProgram, material);
  indexData(geometry, opponent->getFloatsPerVertex(), data, indices);
  opponent->addGeometry(data);
  opponent->addIndices(indices);
  opponent->prepareVao();
  add("Opponent", opponent);
  opponent->moveRight(pos.m_x);

  data.clear();
  indices.clear();
  geometry.clear();

  geometry = buildRect(Vector3(-0.2f, 0.2f, pos.m_z), Vector3(0.4f, 0.4f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
  NormalsMesh* ball = new NormalsMesh(context, normalShaderProgram, material);
  indexData(geometry, ball->getFloatsPerVertex(), data, indices);
  ball->addGeometry(data);
  ball->addIndices(indices);
  ball->prepareVao();
  add("ball", ball);

  m_player = new Player(player, size, 5.0f);
  m_player2 = new Player(opponent, size, 5.0f);
  m_ball = new Ball(ball, Vector3(0.4f, 0.4f, 0.0f), Vector3(6.0f, 6.0f, 0.0f));

  m_gamestate = 0;
}

void
Pong2DScene2P::update(float deltaTime)
{
  if (m_gamestate != 0)
  {
    if (m_ball->update(deltaTime, -10.0f, 10.0f, 5.0f, -5.0f))
    {
      m_gamestate = 0;
    }
    if (m_ball->collides(m_player) || m_ball->collides(m_player2))
    {
      m_ball->bounce();
    }
  } else {
    m_ball->setVelocity(Vector3(6.0f, 3.0f, 0.0f));
  }
}

void 
Pong2DScene2P::processKeys (KeyBuffer* keyBuffer, float deltaTime)
{
  if(keyBuffer->isKeyDown(GLFW_KEY_UP))
  {
    m_player2->moveUp(deltaTime, 5.0f);
  }
  else if(keyBuffer->isKeyDown(GLFW_KEY_DOWN))
  {
    m_player2->moveDown(deltaTime, -5.0f);
  }
  if(keyBuffer->isKeyDown(GLFW_KEY_I))
  {
    m_player->moveUp(deltaTime, 5.0f);
  }
  else if(keyBuffer->isKeyDown(GLFW_KEY_K))
  {
    m_player->moveDown(deltaTime, -5.0f);
  }
  if(keyBuffer->isKeyDown(GLFW_KEY_Q))
  {
    Vector3 vel = m_ball->getVelocity();
    m_ball->setVelocity(Vector3(vel.m_x * -3.0f, vel.m_y, 0.0f));
    keyBuffer->setKeyUp(GLFW_KEY_Q);
  }
  if(keyBuffer->isKeyDown(GLFW_KEY_SPACE))
  {
    m_gamestate = 1;
    m_ball->reset();
    keyBuffer->setKeyUp(GLFW_KEY_SPACE);
  }
}

Pong2DScene2P::~Pong2DScene2P()
{
  delete m_player;
  delete m_ball;
  delete m_player2;
}

void
Pong2DScene2P::resetCamera(Camera* camera)
{
  Scene::resetCamera(camera);
}