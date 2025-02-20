/*
#include "flowControl.h"
#include "globalVars.h"
#include "objects.h"
#include "camera.h"
#include "input.h"
#include "globalScripts.h"
#include "progUI.h"
#include "textureLoading.h"
#include "progBoiler.h"
#include "light.h"
#include "graphicsSettings.h"


Material* mat1;

Camera* cam = nullptr;

Object* plane;
Object* statue;
Object* ball;

PointLight* redLight = nullptr;
PointLight* greenLight = nullptr;
PointLight* blueLight = nullptr;
UniqueType* lightOrigin = nullptr;

void progStart() {
  progUI::fps(true);

  _hideMouse = true;

  setBgColor(Vec4(1, 0, 0, 1));
  _windowTitle = "Light Testing";


  cam = (Camera*)createUniqueType(Unique::CAMERA);
  cam->setOrthographicView(_screenRatio, 1, 1);

  
  //redLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  //greenLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  //blueLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  //lightOrigin = createUniqueType(Unique::UNIQUE);
  //
  //redLight->activeLight = ShaderPointLight({}, { 5, 0, 0, 0});
  //greenLight->activeLight = ShaderPointLight({}, { 0, 5, 0, 0});
  //blueLight->activeLight = ShaderPointLight({}, { 0, 0, 5, 0});
  //
  //redLight->transform.position = {0, 0, -1};
  //greenLight->transform.position = {0, 0, -1};
  //blueLight->transform.position = {0, 0, -1};

  //redLight->setParent(lightOrigin);
  //lightOrigin->transform.rotation = { 0, 120, 0 };

  //greenLight->setParent(lightOrigin);
  //lightOrigin->transform.rotation = { 0, 240, 0 };

  //blueLight->setParent(lightOrigin);

  //lightOrigin->transform.position = { 0, 1, -3};


  Texture* pDiffuse = nullptr;
  Texture* pNormal = nullptr;

  loadTexture("pDiffuse.jpg", &pDiffuse, Texture::ALBEDO, false, false, false);
  loadTexture("pNormal.jpg", &pNormal, Texture::NORMAL, false, false, false);

  //setSkymapTexture({ "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" }, false, false);
  //toggleSkymap();

  //plane = (Object*)instantiateUniqueType("plane");
  //statue = (Object*)instantiateUniqueType("statue");
  ball = (Object*)instantiateUniqueType("shinyBall");

  ball->transform.scale = 0.25f;
  ball->transform.position = { 0, 0, -1};

  //statue->transform.scale = 0.05f;
  //statue->transform.position = { 0, 0, -3};
  //statue->transform.rotation = { -90, 0, 0};

  //((Object*)plane->children[0]->children[0])->srcMaterial.albedoMap = pDiffuse;
  //((Object*)plane->children[0]->children[0])->srcMaterial.normalMap = pNormal;
  //plane->transform.position = { 0, 0, -5 };
  //plane->transform.rotation = { 0, 0, 0 };
  //plane->transform.scale = 0.5f;
}

void progUpdate() {
  if (keyAction::keyPressed(GLFW_KEY_ESCAPE)) {
    _closeApp = true;
  }
  if (keyAction::keyPressed(GLFW_KEY_Q)) {
    _hideMouse = !_hideMouse;
  }

  if (keyAction::scrollUp()) {
    graphicsSettings::exposure += 0.1f;
    std::cout << graphicsSettings::exposure << "\n";
  }
  if (keyAction::scrollDown()) {
    graphicsSettings::exposure = 0.0001f;
    std::cout << graphicsSettings::exposure << "\n";
  }

  if (keyAction::keyHeld(GLFW_KEY_UP))
    ball->transform.rotation.x += 30 * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_DOWN))
    ball->transform.rotation.x -= 30 * _deltaTime;

  if (keyAction::keyHeld(GLFW_KEY_LEFT))
    ball->transform.rotation.y += 30 * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_RIGHT))
    ball->transform.rotation.y -= 30 * _deltaTime;

  //lightOrigin->transform.rotation.y += 30 * _deltaTime;

    Movement::camera(cam, 25);

  if (keyAction::keyHeld(GLFW_KEY_LEFT_SHIFT))
    Movement::freeMove(cam, 1);
  else
    Movement::freeMove(cam, 0.05);

}

void progEnd() {

}






* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* #include "flowControl.h"
#include "globalVars.h"
#include "objects.h"
#include "camera.h"
#include "input.h"
#include "globalScripts.h"
#include "progUI.h"
#include "textureLoading.h"
#include "progBoiler.h"
#include "light.h"
#include "graphicsSettings.h"

Object* backpack = nullptr;
Object* backpack1 = nullptr;
Object* backpack2 = nullptr;
Object* plane = nullptr;

TextBox* textTest = nullptr;

uint textObjTexture = 0;
int width = 0;
int height = 0;

Object* obj1 = nullptr;

Object* redCube = nullptr;
Object* greenCube = nullptr;
Object* blueCube = nullptr;

Material* mat1;

Material* redMaterial;
Material* greenMaterial;
Material* blueMaterial;

Camera* cam = nullptr;

PointLight* redLight = nullptr;
PointLight* greenLight = nullptr;
PointLight* blueLight = nullptr;

DirectionalLight* bigLight = nullptr;

SpotLight* batSignal = nullptr;

void progStart() {
  progUI::fps();

  _hideMouse = true;

  //setBgColor(Vec4(0.24705f, 0.24705f, 0.24705f, 1));
  //setBgColor(Vec4(0.2, 0.3, 0.3, 1));
  setBgColor(Vec4(0, 0, 0, 1));
  _windowTitle = "Light Testing";

  backpack = (Object*)instantiateUniqueType("plane");
  if (backpack) {
    backpack->transform.scale = { 0.0002f };
    backpack->transform.rotation = { -90, 0, -90 };
  }

  cam = (Camera*)createUniqueType(Unique::CAMERA);
  cam->setOrthographicView(_screenRatio, 1, 1);

  cam->transform.position = { 0, 0, 3 };
  //cam->setParent(backpack);

  backpack1 = (Object*)instantiateUniqueType("plane");
  if (backpack1) {
    backpack1->transform.position.x = 1;
    backpack1->transform.scale = { 0.0002f };
    backpack1->transform.rotation = { -90, 0, -90 };
  }

  backpack2 = (Object*)instantiateUniqueType("plane");
  if (backpack2) {
    backpack2->transform.position.x = 2;
    backpack2->transform.scale = { 0.0002f };
    backpack2->transform.rotation = { -90, 0, -90 };
  }

  //plane = instantiateObj("plane");
  //if (plane) {
  //				plane->transform.scale = { 0.0005f };
  //				plane->transform.position = { 1.5, 0, 0 };
  //				plane->transform.rotation = { 0, 0, 90 };
  //}

  obj1 = (Object*)createUniqueType(Unique::OBJECT);
  setObjMesh(obj1, "cube");
  //obj1->active = false;
  //obj1->color = { 1, 0.5, 0.3 };
  obj1->transform.position = { 4, 0, 0 };

  loadTexture("cube_diff.png", nullptr, Texture::DIFFUSE, false, true);
  loadTexture("cube_spec.png", nullptr, Texture::SPECULAR, false, false);
  loadTexture("cube_emmision.jpg", nullptr, Texture::EMISSION, false, true);

  //lightPos = { 10, 20, -30 };

  setSkymapTexture({ "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" });
  toggleSkymap();

  mat1 = createMaterial("basicCube");

  obj1->material = mat1;


  mat1->diffuse = Vec4(1);
  mat1->shininess = 128;
  mat1->diffuseTex = getTexture("cube_diff.png");
  mat1->specularTex = getTexture("cube_spec.png");
  mat1->emissionTex = getTexture("cube_emmision.jpg");




  redMaterial = createMaterial("redMaterial");
  redMaterial->diffuse = Vec4(0);
  redMaterial->specular = 0;
  redMaterial->emission = { 1, 0, 0, 0};
  redMaterial->shininess = 1;

  greenMaterial = createMaterial("greenMaterial");
  greenMaterial->diffuse = Vec4(0);
  greenMaterial->specular = 0;
  greenMaterial->emission = { 0, 1, 0, 0 };
  greenMaterial->shininess = 1;

  blueMaterial = createMaterial("blueMaterial");
  blueMaterial->diffuse = Vec4(0);
  blueMaterial->specular = 0;
  blueMaterial->emission = { 0, 0, 1, 0 };
  blueMaterial->shininess = 1;


  redLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  greenLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  blueLight = (PointLight*)createUniqueType(Unique::POINTLIGHT);
  bigLight = (DirectionalLight*)createUniqueType(Unique::DIRECTIONALLIGHT);
  batSignal = (SpotLight*)createUniqueType(Unique::SPOTLIGHT);

  redLight->activeLight = ShaderPointLight({ 0, 0, 2, 0 }, { 1, 0, 0, 0 }, 1, 2.2, 2, 0.0068);
  greenLight->activeLight = ShaderPointLight({ 1, 0, 2, 0 }, { 0, 1, 0, 0 }, 1, 2.2, 2, 0.0068);
  blueLight->activeLight = ShaderPointLight({ 2, 0, 2, 0 }, { 0, 0, 1, 0 }, 1, 2.2, 2, 0.0068);
  bigLight->activeLight.color = { 0.3, 0.3, 0.3, 1 };
  bigLight->activeLight.direction = { 0, 1, 0, 0 };
  batSignal->activeLight = ShaderSpotLight({ 1, 0, 2, 0 }, { 0, 0, -1, 0 }, { 0, 1, 1, 0 }, cos(5.f * _degToRadF), cos(12.5f * _degToRadF));
  batSignal->transform.position = { 1, 0, 2 };

  redLight->transform.position = { 0, 0, 2 };
  greenLight->transform.position = { 1, 0, 2 };
  blueLight->transform.position = { 2, 0, 2 };


  redCube = (Object*)createUniqueType(Unique::OBJECT);
  setObjMesh(redCube, "cube");
  redCube->transform.scale = { 0.02f };
  redCube->material = redMaterial;

  greenCube = (Object*)createUniqueType(Unique::OBJECT);
  setObjMesh(greenCube, "cube");
  greenCube->transform.scale = { 0.02f };
  greenCube->material = greenMaterial;

  blueCube = (Object*)createUniqueType(Unique::OBJECT);
  setObjMesh(blueCube, "cube");
  blueCube->transform.scale = { 0.02f };
  blueCube->material = blueMaterial;

  redCube->transform.position = redLight->transform.position;
  redCube->setParent(redLight);
  greenCube->transform.position = greenLight->transform.position;
  greenCube->setParent(greenLight);
  blueCube->transform.position = blueLight->transform.position;
  blueCube->setParent(blueLight);
}

float rotAmp = 30.0f;
float rotSpeed = 1000;
float frame = 0;

void progUpdate() {
  if (keyAction::keyPressed(GLFW_KEY_ESCAPE)) {
    _closeApp = true;
  }
  if (keyAction::keyPressed(GLFW_KEY_Q)) {
    _hideMouse = !_hideMouse;
  }

  batSignal->transform.position = cam->transform.position;
  batSignal->activeLight.direction = cam->forwardDirection();

  if (keyAction::scrollUp())
    graphicsSettings::gamma += 0.2f;
  if (keyAction::scrollDown())
    graphicsSettings::gamma -= 0.2f;

  if (keyAction::keyHeld(GLFW_KEY_UP))
    redLight->transform.position.z -= 1 * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_DOWN))
    redLight->transform.position.z += 1 * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_LEFT))
    redLight->transform.position.x -= 1 * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_RIGHT))
    redLight->transform.position.x += 1 * _deltaTime;

  if (keyAction::keyHeld(GLFW_KEY_T))
    backpack->transform.rotation.y += 60 * _deltaTime;

  if (keyAction::keyHeld(GLFW_KEY_KP_2)) {
    backpack->transform.position.z += 1 * _deltaTime;
    backpack1->transform.position.z += 1 * _deltaTime;
    backpack2->transform.position.z += 1 * _deltaTime;
  }
  if (keyAction::keyHeld(GLFW_KEY_KP_8)) {
    backpack->transform.position.z -= 1 * _deltaTime;
    backpack1->transform.position.z -= 1 * _deltaTime;
    backpack2->transform.position.z -= 1 * _deltaTime;
  }

  Movement::camera(cam, 25);
  Movement::freeMove(cam, 1);
}

void progEnd() {

}
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*/