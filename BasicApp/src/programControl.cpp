#define _PROGRAM_CONTROL
#include "ProgramControl.h"
#include "Windows.h"
#include <chrono>
#include "basicApp.h"


/*
* Make everything about 'TreeTransform' virtual in this class
* Remove 'TreeTransform'
* 'UniqueType' should include all the basic functions that
* a type should have
* Each type then should override, mostly will be copy paste with changed types
* That's fine since it should work
*
*
* 12:12AM
* 1/17/2025
*/



/*
* Make camera part of the 'globalUniqueTypes' group
* Pointerify it
* Make drawing happen in all objects 'update' function
* Because of how drawing is currently, nothing should change heavily
* Move matrix calculations into gpu to try and speed stuff up
*
*
* 3:35PM
* 1/17/2025
*/



/*
* Figure out why camera rotation overrides parenting rotation
* Make UI show to FBO and drawn over
* Make wrapper class to allow lights to use unique type stuff
* optimize I guess
*
*
* 3:55PM
* 1/18/2025
*/



/*
* Finish light to unique type stuff
*
*
* 2:21PM
* 1/20/2025
*/



/*
* I think the normals are backwards for lighting, fix it
*
*
* 8:25PM
* 1/21/2025
*/



/*
* Change shader lights to include all lights inside of UBO
* Max uniform blocks is 14 for vertex and fragment shaders
* It will create more overhead, no way around though
* Add directionalLights to UniqueTypes
* Test them
*
*
* 3:46PM
* 1/24/2025
*/



/*
* Data is being passed wrong for spot lights
* Fix it
*
*
* 1:17AM
* 1/25/2025
*/



/*
* Make model loading be able to get material values without textures
* Finish up HDR once that is done
*
*
* 1:29AM
* 1/25/2025
*/





//App globals
//--------------------------------------------------
uint _screenWidth = 1280;
uint _screenHeight = 720;
float _screenRatio = (float)_screenWidth / _screenHeight;
double _deltaTime = 0;
bool _closeApp = false;
bool _hideMouse = false;
bool _vsync = false;
bool _zeroMouse = false;
//--------------------------------------------------



//Local globals
//--------------------------------------------------
std::string _windowTitle = "My window";
size_t delay = 0;
GLFWwindow* mainWindow = nullptr;
//--------------------------------------------------




//--------------------------------------------------
int basicApp_start(const char* title) {
  if (!glfwInit()) {
    std::cout << "Failed to load glfw\n";
    return 1;
  }

  mainWindow = glfwCreateWindow(_screenWidth, _screenHeight, _windowTitle.c_str(), nullptr, nullptr);
  if (!mainWindow) {
    std::cout << "Failed to load window\n";
    return 2;
  }
  glfwMakeContextCurrent(mainWindow);
  glfwSetWindowSizeCallback(mainWindow, windowScaleCallback);
  glfwSetCursorPosCallback(mainWindow, mouseMoveCallback);
  glfwSetMouseButtonCallback(mainWindow, mouseClickCallback);
  glfwSetKeyCallback(mainWindow, keyPressCallback);
  glfwSetScrollCallback(mainWindow, mouseScrollCallback);
  glfwSetWindowPosCallback(mainWindow, windowMoveCallback);


  glfwSetInputMode(mainWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

  if (!gladLoadGL()) {
    std::cout << "Failed to load GL\n";
    return 3;
  }
  start();

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSwapInterval(0);
  return 0;
}



//--------------------------------------------------
bool basicApp_shouldClose() {
  if (!mainWindow)
    return true;

  return glfwWindowShouldClose(mainWindow);
}



//--------------------------------------------------
void basicApp_update() {
  std::chrono::time_point timePoint = std::chrono::steady_clock().now();
  glfwPollEvents();
  update();
  glfwSwapBuffers(mainWindow);

  delay = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock().now() - timePoint).count();
  _deltaTime = (double)delay / 1000000;
}



//--------------------------------------------------
void basicApp_closeApp() {
  glfwSetWindowShouldClose(mainWindow, 1);
}



//--------------------------------------------------
void basicApp_end() {
  end();
}



//--------------------------------------------------
void basicApp_setVsync(bool tf) {
  if (tf)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);
  _vsync = tf;
}



//--------------------------------------------------
bool basicApp_vsync() {
  return _vsync;
}



//--------------------------------------------------
void basicApp_setMouseHide(bool tf) {
  if (tf) {
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  } else
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  _hideMouse = tf;
}



//--------------------------------------------------
void basicApp_swapMouseHide() {
  _hideMouse = !_hideMouse;

  if (_hideMouse) {
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  } else
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}



//--------------------------------------------------
bool basicApp_mouseHide() {
  return _hideMouse;
}



//--------------------------------------------------
float basicApp_deltaTime() {
  return _deltaTime;
}



//--------------------------------------------------
void basicApp_deleteObj(void* ptr) {
  delete(ptr);
}



//--------------------------------------------------
void basicApp_deleteObjArray(void* ptr) {
  delete[](ptr);
}












//DO NOT USE
int run() {
  if (!glfwInit()) {
    std::cout << "Failed to load glfw\n";
    return 0;
  }

  mainWindow = glfwCreateWindow(_screenWidth, _screenHeight, _windowTitle.c_str(), nullptr, nullptr);
  if (!mainWindow) {
    std::cout << "Failed to load window\n";
    return 0;
  }
  glfwMakeContextCurrent(mainWindow);
  glfwSetWindowSizeCallback(mainWindow, windowScaleCallback);
  glfwSetCursorPosCallback(mainWindow, mouseMoveCallback);
  glfwSetMouseButtonCallback(mainWindow, mouseClickCallback);
  glfwSetKeyCallback(mainWindow, keyPressCallback);
  glfwSetScrollCallback(mainWindow, mouseScrollCallback);
  glfwSetWindowPosCallback(mainWindow, windowMoveCallback);


  glfwSetInputMode(mainWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

  if (!gladLoadGL()) {
    std::cout << "Failed to load GL\n";
    return 0;
  }

  start();

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSwapInterval(0);

  while (!glfwWindowShouldClose(mainWindow)) {
    if (_hideMouse) {
      glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else
      glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    std::chrono::time_point timePoint = std::chrono::steady_clock().now();
    glfwPollEvents();
    update();
    glfwSwapBuffers(mainWindow);

    if (_closeApp)
      glfwSetWindowShouldClose(mainWindow, 1);
    if (_vsync)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);


    delay = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock().now() - timePoint).count();
    _deltaTime = (double)delay / 1000000;
  }

  end();

  return 1;
}



//Windows only
//static int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nCmdShow) {
//				main();
//}

//Class operators
std::ostream& operator <<(std::ostream& stream, const Vec2& val) {
  stream << val.x << ", " << val.y;
  return stream;
}

std::ostream& operator <<(std::ostream& stream, const Vec3& val) {
  stream << val.x << ", " << val.y << ", " << val.z;
  return stream;
}

std::ostream& operator <<(std::ostream& stream, const Vec4& val) {
  stream << val.x << ", " << val.y << ", " << val.z << ", " << val.w;
  return stream;
}