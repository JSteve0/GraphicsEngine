/// \file MyScene.hpp
/// \brief Definition of MyScene class and any associated global functions.
/// \author Justin Stevens
/// \version A09

#include "MyScene.hpp"

MyScene::MyScene (OpenGLContext* context, ShaderProgram* colorShaderProgram, ShaderProgram* normalShaderProgram) 
  : Scene::Scene(normalShaderProgram)
{
  // Top Pyramid
  std::vector<float> pyramid {
    // Light Blue Triangle
    0.0f, 5.0f, -7.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of first vertex (R, G, B)
    -2.5f, 0.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of second vertex (R, G, B)
    2.5f, 0.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,    // color of third vertex (R, G, B)
    
    // Lime Green Triangle
    0.0f, 5.0f, -7.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    0.0f, 0.0f, -10.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    -2.5f, 0.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Purple Triangle
    0.0f, 5.0f, -7.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    2.5f, 0.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    0.0f, 0.0f, -10.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Blue Triangle
    0.0f, 0.0f, -10.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    2.5f, 0.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    -2.5f, 0.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Light Blue Triangle
    -2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of first vertex (R, G, B)
    -5.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of second vertex (R, G, B)
    0.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,    // color of third vertex (R, G, B)

    // Lime Green Triangle
    -2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    -2.5f, -5.0f, -7.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    -5.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Purple Triangle
    -2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    0.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    -2.5f, -5.0f, -7.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Blue Triangle
    -2.5f, -5.0f, -7.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    0.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    -5.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Light Blue Triangle
    0.0f, 0.0f, -10.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of first vertex (R, G, B)
    -2.5f, -5.0f, -7.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of second vertex (R, G, B)
    2.5f, -5.0f, -7.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,    // color of third vertex (R, G, B)

    // Lime Green Triangle
    0.0f, 0.0f, -10.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    0.0f, -5.0f, -12.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    -2.5f, -5.0f, -7.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Purple Triangle
    0.0f, 0.0f, -10.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    2.5f, -5.0f, -7.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    0.0f, -5.0f, -12.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Blue Triangle
    0.0f, -5.0f, -12.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    2.5f, -5.0f, -7.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    -2.5f, -5.0f, -7.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Light Blue Triangle
    2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of first vertex (R, G, B)
    0.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,   // color of second vertex (R, G, B)
    5.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.8f, 1.0f,    // color of third vertex (R, G, B)

    // Lime Green Triangle
    2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    2.5f, -5.0f, -7.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    0.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.25f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Purple Triangle
    2.5f, 0.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    5.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    2.5f, -5.0f, -7.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.5f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Blue Triangle
    2.5f, -5.0f, -7.5f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    5.0f, -5.0f, -2.5f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    0.0f, -5.0f, -2.5f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f    // color of third vertex (R, G, B)
  };

  // Hexagon
  std::vector<float> hexagon2D {
    // Bottom Left Triangle
    6.0f, 6.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    5.0f, 5.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,  // color of second vertex (R, G, B)
    7.0f, 5.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Left Triangle
    4.0f, 6.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    5.0f, 5.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    6.0f, 6.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Top Left Triangle
    5.0f, 7.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    4.0f, 6.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    6.0f, 6.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,    // color of third vertex (R, G, B)

    // Top Right Triangle
    5.0f, 7.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    6.0f, 6.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    7.0f, 7.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Right Triangle
    7.0f, 7.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of first vertex (R, G, B)
    6.0f, 6.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
    8.0f, 6.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,    // color of third vertex (R, G, B)

    // Bottom Left Triangle
    6.0f, 6.0f, -5.0f,   // 3-d coordinates of first vertex (X, Y, Z)
    0.0f, 1.0f, 0.0f,   // color of first vertex (R, G, B)
    7.0f, 5.0f, -5.0f, // 3-d coordinates of second vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f,   // color of second vertex (R, G, B)
    8.0f, 6.0f, -5.0f,  // 3-d coordinates of third vertex (X, Y, Z)
    0.0f, 0.0f, 1.0f    // color of third vertex (R, G, B)
  };

  //std::vector<float> image = buildTexturedRect(-10.0f, 10.0f, -20.0f, 20.0f, 10.0f, 0.0f, 5.0f, Vector3(0.0f, 0.0f, 1.0f));
  std::vector<float> image = buildTexturedRect(Vector3(-10.0f, 10.0f, -20.0f), Vector3(20.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), 5.0f);

  Material* green = new Material(
    Vector3(0.0f, 0.1f, 0.0f),
    Vector3(0.0f, 0.9f, 0.0f),
    Vector3(0.2f, 0.2f, 0.2f),
    Vector3(0.0f, 0.1f, 0.0f),
    0.2f
  );

  Material* blue = new Material(
    Vector3(0.0f, 0.0f, 0.1f),
    Vector3(0.0f, 0.0f, 0.9f),
    Vector3(0.2f, 0.2f, 0.2f),
    Vector3(0.0f, 0.0f, 0.1f),
    0.2f
  );

  Material* gold = new Material();
  gold->setToGold();

  Material* textureMaterial = new Material(
    Vector3(0.2f, 0.2f, 0.2f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.0f, 0.0f, 0.0f),
    Vector3(0.01f, 0.01f, 0.01f),
    0.2f
  );

  addMaterial(gold);
  addMaterial(green);
  addMaterial(blue);
  addMaterial(textureMaterial);

  Texture* brickTexture = new Texture("Textures/Brick.png");
  addTexture(brickTexture);
  Texture* bearTexture = new Texture("Textures/Bear.jpg");
  addTexture(bearTexture);

  TexturedNormalsMesh* brickMesh = new TexturedNormalsMesh(context, normalShaderProgram, textureMaterial, brickTexture);

  addLightSource(
    new DirectionalLightSource(
      Vector3(1.0f, 1.0f, 1.0f), 
      Vector3(0.2f, 0.2f, 0.2f), 
      Vector3(-1.0f, 0.0f, 0.0f) 
    )
  );
  
  addLightSource(
    new PointLightSource(
      Vector3(0.5f, 0.5f, 0.9f), // Diffuse (r, g, b)
      Vector3(0.2f, 0.2f, 0.2f), // Specular (r, g, b)
      Vector3(3.0f, 0.0f, -10.0f), // Position (x, y, z)
      Vector3(0.03f, 0.03f, 0.03f) // AttenuationCoefficients, Higher value makes it dimmer over distance.
    )
  );
  
  addLightSource(
    new SpotLightSource(
      Vector3(0.9f, 0.0f, 0.0f), // Diffuse (r, g, b)
      Vector3(0.2f, 0.2f, 0.2f), // Specular (r, g, b)
      Vector3(0.0f, 0.0f, 0.0f), // Position (x, y, z)
      Vector3(0.01f, 0.01f, 0.01f), // AttenuationCoefficients 
      Vector3(0.4f, 0.0f, -1.0f), // Direction (x, y, z)
      0.2f, // cutoffCosAngle, lower makes range wider
      1.0f // falloff, higher decreases distance
    )
  );
  
  // Create new mesh pointers
  Mesh* pyramidMesh = new ColorsMesh(context, colorShaderProgram);
  Mesh* hexagonMesh1 = new ColorsMesh(context, colorShaderProgram);
  Mesh* hexagonMesh2 = new ColorsMesh(context, colorShaderProgram);

  Mesh* cube1 = new ColorsMesh(context, colorShaderProgram);
  Mesh* cube2 = new ColorsMesh(context, colorShaderProgram);
  Mesh* cube3 = new NormalsMesh(context, normalShaderProgram, blue);
  Mesh* cube4 = new NormalsMesh(context, normalShaderProgram, green);

  Mesh* bear = new TexturedNormalsMesh(context, normalShaderProgram, "models/bear.obj", 0, gold, bearTexture, 5.0f);
  Mesh* bear1 = new NormalsMesh(context, normalShaderProgram, "models/bear.obj", 0, gold);

  std::vector<float> pyramidData;
  std::vector<unsigned> indices;

  indexData(pyramid, 6, pyramidData, indices);
  pyramidMesh->addGeometry(pyramidData);
  pyramidMesh->addIndices(indices);

  indices.clear();

  std::vector<float> hexagon2DData;

  indexData(hexagon2D, 6, hexagon2DData, indices);

  // Add geometry to second mesh
  hexagonMesh1->addGeometry(hexagon2DData);
  hexagonMesh2->addGeometry(hexagon2DData);
  hexagonMesh1->addIndices(indices);
  hexagonMesh2->addIndices(indices);

  hexagonMesh2->moveRight(-10.0f);

  // Prepare vao for all meshes
  pyramidMesh->prepareVao();
  hexagonMesh1->prepareVao();
  hexagonMesh2->prepareVao();
  
  // Add meshes to scene and give them a name
  add("Pyramid", pyramidMesh);
  add("Hexagon1", hexagonMesh1);
  add("Hexagon2", hexagonMesh2);

  std::vector<Triangle> cube = buildCube();
  std::vector<Vector3> colors = generateRandomFaceColors(cube);
  std::vector<float> cubeData = dataWithFaceColors(cube, colors);
  std::vector<float> unique;

  indices.clear();
  indexData(cubeData, 6, unique, indices);
  cube1->addGeometry(unique);
  cube1->addIndices(indices);
  cube1->prepareVao();

  cubeData.clear();
  indices.clear();
  unique.clear();

  cube = buildCube();
  std::vector<Vector3> vertices = generateRandomVertexColors(cube);
  cubeData = dataWithVertexColors(cube, vertices);

  indexData(cubeData, 6, unique, indices);
  cube2->addGeometry(unique);
  cube2->addIndices(indices);
  cube2->prepareVao();

  cube2->moveUp(-1.5);

  cubeData.clear();
  indices.clear();
  unique.clear();

  cube = buildCube();
  std::vector<Vector3> normals = computeFaceNormals(cube);
  cubeData = dataWithFaceNormals(cube, normals);

  indexData(cubeData, 6, unique, indices);
  cube3->addGeometry(unique);
  cube3->addIndices(indices);
  cube3->prepareVao();

  cube3->moveUp(-3.0);

  cubeData.clear();
  indices.clear();
  unique.clear();
  normals.clear();

  cube = buildCube();
  normals = computeFaceNormals(cube);
  std::vector<Vector3> vertexNormals = computeVertexNormals(cube, normals);
  cubeData = dataWithVertexNormals(cube, vertexNormals);

  indexData(cubeData, 6, unique, indices);
  cube4->addGeometry(unique);
  cube4->addIndices(indices);
  cube4->prepareVao();

  cube4->moveUp(-4.5);

  cube1->moveRight(-7.0);
  cube2->moveRight(-7.0);
  cube3->moveRight(-7.0);
  cube4->moveRight(-7.0);

  cube1->moveBack(-10.0);
  cube2->moveBack(-10.0);
  cube3->moveBack(-10.0);
  cube4->moveBack(-10.0);

  add("Cube1", cube1);
  add("Cube2", cube2);
  add("Cube3", cube3);
  add("Cube4", cube4);
  
  bear->scaleWorld(0.25);
  bear->moveUp(-20.0);
  bear->moveRight(35.0);

  bear1->scaleWorld(0.25);
  bear1->moveUp(-20.0);
  bear1->moveRight(-35.0);

  indices.clear();
  unique.clear();

  indexData(image, 8, unique, indices);
  brickMesh->addGeometry(unique);
  brickMesh->addIndices(indices);
  brickMesh->prepareVao();
  add("Brick", brickMesh);

  bear->prepareVao();
  add("Bear", bear);

  bear1->prepareVao();
  add("Bear1", bear1);
}

void 
MyScene::update (float deltaTime)
{

}

void
MyScene::processKeys (KeyBuffer* keyBuffer, float deltaTime)
{
  
}

MyScene::~MyScene()
{
  
}

void
MyScene::resetCamera(Camera* camera)
{
  Scene::resetCamera(camera);
}