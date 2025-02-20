#define _FLOW_CONTROL
#include "flowControl.h"
#include "basicApp.h"

//App globals
//--------------------------------------------------
Vec4 _bgColor = Vec4(0);
iVec2 _windowPos = iVec2(0);
iVec2 _realMousePos = iVec2(0);

bool _windowScaled = false;

float _mousePosX = 0;
float _mousePosY = 0;
float _pMousePosX = 0;
float _pMousePosY = 0;

bool _lockMouse;
//--------------------------------------------------



//Local globals
//--------------------------------------------------
int Camera::cameraCount = 0;
int Camera::currentCamera = 0;
Camera* Camera::globalCameras[_MAX_CAMERAS] = {};

uint Shader::currentShader = 0;
//--------------------------------------------------



//Extern globals
//--------------------------------------------------
extern unsigned int postFBO;
extern unsigned int UIFBO;
//--------------------------------------------------





//--------------------------------------------------
void basicApp_setBgColorVec4(Vec4 color) {
  _bgColor = color;
}



//--------------------------------------------------
void basicApp_setBgColorVars(float r, float g, float b, float a) {
  _bgColor = Vec4(r, g, b, a);
}







void start() {
  addShader("minShader", "./shaders/Min/MinShader.vert", "./shaders/Min/MinShader.frag");
  addShader("textureShader", "./shaders/Texture/TVertexShader.vert", "./shaders/Texture/TFragmentShader.frag");
  addShader("lightingShader", "./shaders/Lighting/LightingShader.vert", "./shaders/Lighting/LightingShader.frag");
  addShader("cubeMapShader", "./shaders/CubeMap/CubeMapShader.vert", "./shaders/CubeMap/CubeMapShader.frag");
  addShader("noLightingShader", "./shaders/NoLighting/NoLightingShader.vert", "./shaders/NoLighting/NoLightingShader.frag");
  addShader("UIShader", "./shaders/UI/UIShader.vert", "./shaders/UI/UIShader.frag");
  addShader("postProcessingShader", "./shaders/PostProcessing/postProcessingShader.vert", "./shaders/PostProcessing/postProcessingShader.frag");
  addShader("textShader", "./shaders/text/TextVertexShader.vert", "./shaders/text/TextFragmentShader.frag");
  addShader("equirectangularCubemapShader", "./shaders/EquirectangularCubemap/EquirectangularCubemapShader.vert", "./shaders/EquirectangularCubemap/EquirectangularCubemapShader.frag");
  addShader("irradianceShader", "./shaders/Irradiance/IrradianceShader.vert", "./shaders/Irradiance/IrradianceShader.frag");
  addShader("prefilterShader", "./shaders/Prefilter/PrefilterShader.vert", "./shaders/Prefilter/PrefilterShader.frag");
  addShader("brdfShader", "./shaders/BRDF/BRDFShader.vert", "./shaders/BRDF/BRDFShader.frag");

  nUniqueTypes::start();
  nObjects::start();
  nText::start();
  nProgUI::start();
  nSound::start();

  //nModelLoading::start("./models/plane/plane.obj", "airplane", false);
  //nModelLoading::start("./models/backpack/backpack.obj", "backpack", true);
  //nModelLoading::start("./models/smallBackpack.obj", "sBackpack", true);
  //nModelLoading::start("./models/tunnel.obj", "tunnel", false);
  //nModelLoading::start("./models/plane.obj", "plane", false);
  //nModelLoading::start("./models/statue/Statue.fbx", "statue", false);
  //nModelLoading::start("./models/ball/Ball.fbx", "ball", false);
  //nModelLoading::start("./models/ShinyBall.fbx", "shinyBall", false);

  loadFont("./fonts/CascadiaCode.ttf", "CascadiaCode");
  loadFont("./fonts/CascadiaCode-Light.ttf", "CascadiaCodeLight");

  progUI::fps(true);
  //progStart();
}

void update() {
  nSound::update();

  //progUpdate();
  //nObjects::update();
  nProgUI::update();

  glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
  glClearColor(_bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glClearColor(0, 0, 0, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, UIFBO);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Camera* mainCamera = Camera::getCurrentCamera();
  if (mainCamera)
    mainCamera->setViewMatrix();

  updateAllUniques();
  drawSkyMap();
  drawPostProcessing();
  drawUI();

  _windowScaled = false;
}

void end() {
  //progEnd();
  deleteAll();

  nText::end();
  nUniqueTypes::end();
  nIntializeShader::end();
  nSound::end();
  nMaterial::end();
  nObjects::end();

  deleteAllTextures();
}



//-------------------CALLBACKS

void windowScaleCallback(GLFWwindow* window, int width, int height) {
  _screenWidth = width;
  _screenHeight = height;
  _screenRatio = (float)_screenWidth / _screenHeight;
  glViewport(0, 0, width, height);
  _windowScaled = true;
}
void windowMoveCallback(GLFWwindow* window, int xpos, int ypos) {
  _windowPos.x = xpos;
  _windowPos.y = ypos;
}
void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
  if (_lockMouse) {
    SetCursorPos(_windowPos.x + _realMousePos.x, _windowPos.y + _realMousePos.y);
    return;
  }

  _pMousePosX = _mousePosX;
  _pMousePosY = _mousePosY;

  _realMousePos = { xpos, ypos };
  _mousePosX = xpos / _screenHeight * 2 - _screenRatio;
  _mousePosY = (_screenHeight - ypos) / _screenHeight * 2 - 1;
}
void keyPressCallback(GLFWwindow* window, int button, int scancode, int action, int mods) {
  if (action == GLFW_PRESS)
    giveKeyAction::keyPressed(button);
  else if (action == GLFW_RELEASE)
    giveKeyAction::keyReleased(button);
  giveKeyAction::setNumlock(mods & GLFW_MOD_NUM_LOCK);
  giveKeyAction::setShift(mods & GLFW_MOD_SHIFT);
}
void mouseScrollCallback(GLFWwindow* window, double xoff, double yoff) {
  if (yoff > 0)
    giveKeyAction::scrolledUp();
  else if (yoff < 0)
    giveKeyAction::scrolledDown();
}
void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS)
    giveKeyAction::keyPressed(button);
  else if (action == GLFW_RELEASE)
    giveKeyAction::keyReleased(button);
}