#define _PROG_BOILER
#include "progBoiler.h"
#include "basicApp.h"
#include <iostream>


//Local globals
//--------------------------------------------------
float lookSpeed = 25.f;
float moveSpeed = 5.f;
//--------------------------------------------------





//--------------------------------------------------
void basicApp_mainCameraLook() {
  Camera* cam = Camera::getCurrentCamera();

  if (!cam)
    return;

  if (!_hideMouse)
    return;
  cam->setRotation(_mousePosY * lookSpeed, _mousePosX * lookSpeed, 0);
}



//--------------------------------------------------
void basicApp_setLookSpeed(float speed) {
  lookSpeed = speed;
}



//--------------------------------------------------
float basicApp_lookSpeed() {
  return lookSpeed;
}



//--------------------------------------------------
void basicApp_mainCameraMove() {
  Camera* cam = Camera::getCurrentCamera();

  if (!cam)
    return;

  if (keyAction::keyHeld(GLFW_KEY_SPACE))
    cam->transform.position.y += moveSpeed * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_LEFT_CONTROL))
    cam->transform.position.y += -moveSpeed * _deltaTime;


  if (keyAction::keyHeld(GLFW_KEY_W))
    cam->transform.position += cam->forwardDirection() * moveSpeed * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_S))
    cam->transform.position += cam->forwardDirection() * -moveSpeed * _deltaTime;

  if (keyAction::keyHeld(GLFW_KEY_A))
    cam->transform.position += cam->rightDirection() * -moveSpeed * _deltaTime;
  if (keyAction::keyHeld(GLFW_KEY_D))
    cam->transform.position += cam->rightDirection() * moveSpeed * _deltaTime;
}



//--------------------------------------------------
void basicApp_setMoveSpeed(float speed) {
  moveSpeed = speed;
}



//--------------------------------------------------
float basicApp_moveSpeed() {
  return moveSpeed;
}










namespace Movement {
  void camera(Camera* cam, float speed) {
    if (!cam)
      return;

    if (!_hideMouse)
      return;
    cam->setRotation(-_mousePosY * speed, -(_mousePosX)*speed, 0);
  }

  void freeMove(Camera* cam, float speed) {
    if (!cam)
      return;

    if (keyAction::keyHeld(GLFW_KEY_SPACE))
      cam->transform.position.y += speed * _deltaTime;
    if (keyAction::keyHeld(GLFW_KEY_LEFT_CONTROL))
      cam->transform.position.y += -speed * _deltaTime;


    if (keyAction::keyHeld(GLFW_KEY_W))
      cam->transform.position += cam->forwardDirection() * speed * _deltaTime;
    if (keyAction::keyHeld(GLFW_KEY_S))
      cam->transform.position += cam->forwardDirection() * -speed * _deltaTime;

    if (keyAction::keyHeld(GLFW_KEY_A))
      cam->transform.position += cam->rightDirection() * -speed * _deltaTime;
    if (keyAction::keyHeld(GLFW_KEY_D))
      cam->transform.position += cam->rightDirection() * speed * _deltaTime;
  }
}