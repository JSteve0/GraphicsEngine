/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg, Justin Stevens
/// \version A09
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.  It
///   allows limited movement of a very simple virtual camera.


/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions
#include <glm/mat4x4.hpp>
// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>


/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/MyScene.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "KeyBuffer.hpp"
#include "MouseBuffer.hpp"
#include "Matrix4.hpp"
#include "Transform.hpp"
#include "TexturedNormalsMesh.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "PhysicsObject.hpp"
#include "Scenes/Pong2DScene.hpp"
#include "Scenes/Pong2DScene2P.hpp"
#include <vector>

/******************************************************************/
// Local types

/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

/// \brief A collection of Meshes stored in one scene.
///
/// This will be filled in initScene, and its contents need to be deleted in
///   releaseGlResources.
std::vector<Scene*> g_scene;
std::vector<Scene*>::iterator g_currentScene;

/// \brief The ShaderProgram that transforms and lights the primitives using colors.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_colorShaderProgram;

/// \brief The ShaderProgram that transforms and lights the primitives using normals.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_normalShaderProgram;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

/// \brief The KeyBufffer that tracks what keys are up and down.
///
/// This should be allocated in ::initScene and deallocated in
///   ::releaseGlResources.
KeyBuffer* g_keyBuffer;

/// \brief The MouseBuffer that tracks what keys are up and down 
///   and the x & y position of the mouse.
///
/// This should be allocated in ::initScene and deallocated in
///   ::releaseGlResources.
MouseBuffer* g_mouseBuffer;

/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init (GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw ();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew ();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow (GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to V.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport (GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene ();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders ();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera ();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene (double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene (GLFWwindow* window);

/// \brief Records user input with a keybuffer.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

/// \brief Records user mouse position from mouse.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] xpos The x position of the mouse.
/// \param[in] ypos The y position of the mouse.
void
recordMousePosition (GLFWwindow* window, double xpos, double ypos);

/// \brief Records user mouse position from mouse.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] button The button that was pressed or released.
/// \param[in] action What happened to the button.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordMouseKeys (GLFWwindow* window, int button, int action, int mods);

/// \brief Records users scrollwheel offset
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] xpos The x offest of the scroll wheel.
/// \param[in] ypos The y offset of the scroll wheel.
void
processScrollWheel (GLFWwindow* window, double xoffset, double yoffset);

/// \brief Responds to implemented keys that are pressed down in keybuffer.
void 
processKeys (float deltaTime);

/// \brief Cleans up all resources as program exits.
void
releaseGlResources ();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError (int error, const char* description);


/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main (int argc, char* argv[])
{
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys(deltaTime);
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  g_context = new RealOpenGLContext ();
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (800, 450, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 100, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys);
  glfwSetMouseButtonCallback(window, recordMouseKeys);
  glfwSetScrollCallback(window, processScrollWheel);
  glfwSetCursorPosCallback(window, recordMousePosition);
  glfwSetFramebufferSizeCallback (window, resetViewport);

  // Specify background color
  g_context->clearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace (GL_CCW);
  g_context->cullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  g_context->viewport (0, 0, width, height);
  g_camera->setProjectionSymmetricPerspective(60, ((double) width) / height, 0.01, 90.0);
}

/******************************************************************/

void
initScene ()
{
  // Create new MyScene and assign it to global scene.
  g_scene.push_back (new Pong2DScene(g_context, g_colorShaderProgram, g_normalShaderProgram));
  g_scene.push_back (new Pong2DScene2P(g_context, g_colorShaderProgram, g_normalShaderProgram));  
  g_scene.push_back (new PhysicsScene(g_context, g_colorShaderProgram, g_normalShaderProgram));
  g_scene.push_back (new MyScene(g_context, g_colorShaderProgram, g_normalShaderProgram));
  g_currentScene = g_scene.begin();

  // Create new KeyBuffer and assign it to global keyBuffer.
  g_keyBuffer = new KeyBuffer();

  // Create new MouseBuffer and assign it to global mouseBuffer.
  g_mouseBuffer = new MouseBuffer();
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_colorShaderProgram = new ShaderProgram (g_context);
  g_colorShaderProgram->createVertexShader ("Shaders/Vec3.vert");
  g_colorShaderProgram->createFragmentShader ("Shaders/Vec3.frag");
  g_colorShaderProgram->link ();

  g_normalShaderProgram = new ShaderProgram (g_context);
  g_normalShaderProgram->createVertexShader ("Shaders/PhongShader.vert");
  g_normalShaderProgram->createFragmentShader ("Shaders/PhongShader.frag");
  g_normalShaderProgram->link ();
}

/******************************************************************/

void
initCamera ()
{
  // Define the projection, which will remain constant
  double verticalFov = 60.0;
  double aspectRatio = 16.0 / 9.0;
  // Near plane
  double nearZ = 0.01;
  // Far plane
  double farZ = 90.0;

  // Define the camera's coordinate system
  Vector3 position (0.0f, 0.0f, 12.0f);
  Vector3 back (0.0f, 0.0f, 1.0f);

  // Create camera object given the above variables.
  g_camera = new Camera (position, back, nearZ, farZ, aspectRatio, verticalFov);
}

/******************************************************************/

void
updateScene (double time)
{
  (*g_currentScene)->update(time);
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  g_context->clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Draw everything in the scene.
  (*g_currentScene)->draw(g_camera->getViewMatrix(), g_camera->getProjectionMatrix(), g_camera->getPosition());

  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  glfwSwapBuffers (window);
}


/******************************************************************/

void
processScrollWheel (GLFWwindow* window, double xoffset, double yoffset) 
{
  if (1 < (g_camera->getFOV()) + yoffset && (g_camera->getFOV() + yoffset) < 120)
  {
    g_camera->setFOV(g_camera->getFOV() + yoffset);
    g_camera->setProjectionSymmetricPerspective(g_camera->getFOV(), 16.0 / 9.0, 0.01, 90.0);
  }
}

void
recordMouseKeys (GLFWwindow* window, int button, int action, int mods)
{
  if (action == GLFW_PRESS) 
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      g_mouseBuffer->setRightButton(true);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      g_mouseBuffer->setLeftButton(true);
    }
  }
  if (action == GLFW_RELEASE) 
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      g_mouseBuffer->setRightButton(false);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      g_mouseBuffer->setLeftButton(false);
    }
  }
}

void
recordMousePosition (GLFWwindow* window, double xpos, double ypos)
{
  double deltaX = xpos - g_mouseBuffer->getX();
  double deltaY = ypos - g_mouseBuffer->getY();
  float sensitivity = 0.2;

  g_mouseBuffer->setPosition(xpos, ypos);

  if (g_mouseBuffer->getLeftButton()) 
  {
    g_camera->yaw(-deltaX * sensitivity);
    g_camera->pitch(-deltaY * sensitivity);
  }
  else if (g_mouseBuffer->getRightButton()) {
    g_camera->roll(deltaX * sensitivity);
  }
}

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }

  // Update key buffer with key that is pressed
  if (action == GLFW_PRESS) 
    g_keyBuffer->setKeyDown(key);
  // Update key buffer with key that is released
  if (action == GLFW_RELEASE) 
    g_keyBuffer->setKeyUp(key);
}

void 
processKeys (float deltaTime)
{
  // Translate camera/eye point using WASD keys
  const float MOVEMENT_DELTA = 0.5f;
  //const float ROTATION_DELTA_DEGREES = 2.0f; //In degrees

  /******************/
  /* Keys to camera */
  /******************/

  // Camera movement on X axis
  // Move camera left if 'A' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_A)) 
    g_camera->moveRight(-MOVEMENT_DELTA);
  // Move camera right if 'D' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_D)) 
    g_camera->moveRight(MOVEMENT_DELTA);

  // Camera movement on Y axis
  // Move camera down if 'C' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_C)) 
    g_camera->moveUp(-MOVEMENT_DELTA);
  // Move camera up if 'F' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_F)) 
    g_camera->moveUp(MOVEMENT_DELTA);

  // Camera movement on Z axis
  // Move camera forward if 'W' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_W)) 
    g_camera->moveBack(-MOVEMENT_DELTA);
  // Move camera backwards if 'S' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_S)) 
    g_camera->moveBack(MOVEMENT_DELTA);

  // Reset camera position if 'R' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_R)) 
    (*g_currentScene)->resetCamera(g_camera);

  /*

  // Set camera projection to symmetric if 'P' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_P)) 
    g_camera->setProjectionSymmetricPerspective(60, 16.0 / 9.0, 0.01, 90.0);
  // Set camera projection to asymmetric camera '[' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_LEFT_BRACKET)) 
    g_camera->setProjectionAsymmetricPerspective(-1.0, 4.0, -7.0, 4.0, 5.0, 50.0);
  // Set camera projection to orthographic camera if 'O' is pressed
  if (g_keyBuffer->isKeyDown(GLFW_KEY_O)) 
    g_camera->setProjectionOrthographic(-20.0, 20.0, -15.0, 15.0, 0.01, 100.0);

  */

  /*******************************************/
  /* Keys to controls and change active mesh */
  /*******************************************/

  /*

  // Change active mesh, '-' for previous, '=' for next
  if (g_keyBuffer->isKeyDown(GLFW_KEY_MINUS)) {
    (*g_currentScene)->activatePreviousMesh();
    g_keyBuffer->setKeyUp(GLFW_KEY_MINUS);
  }
  if (g_keyBuffer->isKeyDown(GLFW_KEY_EQUAL)) {
    (*g_currentScene)->activatePreviousMesh();
    g_keyBuffer->setKeyUp(GLFW_KEY_EQUAL);
  }

  */

  // Change active Scene, '-' for previous, '=' for next
  if (g_keyBuffer->isKeyDown(GLFW_KEY_MINUS)) {
    if (g_currentScene == g_scene.begin())
    {
      g_currentScene = g_scene.end() - 1;
    } else {
      --g_currentScene;
    }
    g_keyBuffer->setKeyUp(GLFW_KEY_MINUS);
    (*g_currentScene)->resetCamera(g_camera);
  }
  if (g_keyBuffer->isKeyDown(GLFW_KEY_EQUAL)) {
    ++g_currentScene;
    if (g_currentScene == g_scene.end())
    {
      g_currentScene = g_scene.begin();
    }
    g_keyBuffer->setKeyUp(GLFW_KEY_EQUAL);
    (*g_currentScene)->resetCamera(g_camera);
  }

  (*g_currentScene)->processKeys(g_keyBuffer, deltaTime);

  /*

  // Yaw the active mesh, + when J is pressed and - for L.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_J)) 
    (*g_currentScene)->getActiveMesh()->yaw(ROTATION_DELTA_DEGREES);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_L)) 
    (*g_currentScene)->getActiveMesh()->yaw(-ROTATION_DELTA_DEGREES);

  // Pitch the active mesh, + when I is pressed and - for K.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_I)) 
    (*g_currentScene)->getActiveMesh()->pitch(ROTATION_DELTA_DEGREES);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_K)) 
    (*g_currentScene)->getActiveMesh()->pitch(-ROTATION_DELTA_DEGREES);

  // Roll the active mesh, + when N is pressed and - for M.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_N)) 
    (*g_currentScene)->getActiveMesh()->roll(ROTATION_DELTA_DEGREES);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_M)) 
    (*g_currentScene)->getActiveMesh()->roll(-ROTATION_DELTA_DEGREES);

  // Moves the active mesh along its x axis, + when 1 is pressed and - for 2.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_1)) 
    (*g_currentScene)->getActiveMesh()->moveRight(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_2)) 
    (*g_currentScene)->getActiveMesh()->moveRight(-MOVEMENT_DELTA);

  // Moves the active mesh along its y axis, + when 3 is pressed and - for 4.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_3)) 
    (*g_currentScene)->getActiveMesh()->moveUp(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_4)) 
    (*g_currentScene)->getActiveMesh()->moveUp(-MOVEMENT_DELTA);

  // Moves the active mesh along its z axis, + when 5 is pressed and - for 6.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_5)) 
    (*g_currentScene)->getActiveMesh()->moveBack(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_6)) 
    (*g_currentScene)->getActiveMesh()->moveBack(-MOVEMENT_DELTA);
  
  // Scales the active mesh by 1.01 when 7 is pressed and 0.99 for 8.
  if (g_keyBuffer->isKeyDown(GLFW_KEY_7)) 
    (*g_currentScene)->getActiveMesh()->scaleWorld(1.01f);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_8)) 
    (*g_currentScene)->getActiveMesh()->scaleWorld(0.99f);

  */
}

/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  
  for (auto& scene : g_scene)
  {
    delete scene;
  }
  delete g_keyBuffer;
  delete g_mouseBuffer;
  delete g_camera;
  delete g_colorShaderProgram;
  delete g_normalShaderProgram;
  delete g_context;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
