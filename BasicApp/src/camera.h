#pragma once
#include "openGL.h"
#include "vector.h"
#include "mathConstants.h"
#include "transform.h"
#include "constants.h"

class Camera : public UniqueType {
  int cameraIndex;
public:

  const Unique::Types getType() const override { return Unique::CAMERA; }

  UniqueType* copySelf() override {
    Camera* ret = new Camera;

    setToRelative();
    for (auto child : children)
      child->setToRelative();

    void addUniqueTypeScript(UniqueType * obj, void* script, char c);
    for (auto& scrV : scripts) {
      void* newScr = ((scriptBase*)scrV)->getNew();
      addUniqueTypeScript(ret, newScr, 'c');
    }

    for (auto& child : children) {
      if (child->scriptCreated)
        continue;

      UniqueType* temp = nullptr;

      temp = child->copySelf();

      temp->setParent(ret);
    }

    ret->active = this->active;
    ret->node = this->node;
    ret->FOV = this->FOV;
    ret->nearClip = this->nearClip;
    ret->farClip = this->farClip;
    ret->perspectiveView = this->perspectiveView;
    ret->orthographicView = this->orthographicView;
    ret->viewMatrix = this->viewMatrix;

    return ret;
  }

  void end() override {
    if (index < 0)
      return;

    if (cameraCount == 1) {
      globalCameras[index] = nullptr;
      cameraCount == 0;
      return;
    }

    globalCameras[index] = globalCameras[cameraCount - 1];
    globalCameras[index]->index = index;
    globalCameras[cameraCount - 1] = nullptr;
    cameraCount--;
  }





  static int cameraCount;
  static int currentCamera;

  static Camera* globalCameras[_MAX_CAMERAS];

  static bool addCamera(Camera* cam) {
    if (cameraCount >= _MAX_CAMERAS)
      return false;
    globalCameras[cameraCount] = cam;
    cam->cameraIndex = cameraCount;
    cameraCount++;
  }


  static Camera* getCurrentCamera() {
    if (cameraCount == 0)
      return nullptr;
    return globalCameras[currentCamera];
  }

  static bool setCurrentCamera(int cam) {
    if (cam < 0 || cam > cameraCount - 1)
      return false;
    currentCamera = cam;
    return true;
  }

  int getCameraIndex() {
    return cameraIndex;
  }


  Camera() : UniqueType(), FOV(70), nearClip(0.001f), farClip(100.f), width(1), height(1), perspectiveView(0), orthographicView(0), viewMatrix(1) {
    if (!addCamera(this))
      index = -1;
    updatePerspectiveView();
    updateOrthographicView();
  }
  Camera(float fov, float N, float F, float R, float W, float H, float D) : UniqueType(), FOV(fov), nearClip(N), farClip(F), ratio(R), width(W), height(H), depth(D), perspectiveView(0), orthographicView(0), viewMatrix(1) {
    if (!addCamera(this))
      index = -1;
    updatePerspectiveView();
    updateOrthographicView();
  }

  
  float FOV;
  float nearClip;
  float farClip;
  float ratio;

  float width;
  float height;
  float depth;

  glm::mat4 perspectiveView;
  glm::mat4 orthographicView;
  glm::mat4 viewMatrix;

  void setPerspectiveView(float fov, float r, float nC, float fC) {
    FOV = fov;
    ratio = r;
    nearClip = nC;
    farClip = fC;
    updatePerspectiveView();
  }

  void setOrthographicView(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
    updateOrthographicView();
  }

  void updatePerspectiveView() {
    perspectiveView = glm::perspective(FOV, ratio, nearClip, farClip);
  }

  void updateOrthographicView() {
    orthographicView = glm::ortho(-width, width, -height, height, -depth, depth);
  }

  void setViewMatrix() {
    viewMatrix = glm::mat4(1);
    viewMatrix = glm::rotate(viewMatrix, transform.rotation.x * (float)_degToRad, glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, -transform.rotation.y * (float)_degToRad, glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, transform.rotation.z * (float)_degToRad, glm::vec3(0, 0, 1));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-transform.position.x, -transform.position.y, -transform.position.z));
  }

  Vec3 forwardDirection() {
    Vec3 ret;

    ret.x = cos(_degToRad * (transform.rotation.y + 90)) * cos(_degToRad * transform.rotation.x);
    ret.y = sin(_degToRad * -transform.rotation.x);
    ret.z = cos(_degToRad * transform.rotation.x) * sin(_degToRad * (transform.rotation.y - 90));

    return ret;
  }

  Vec3 rightDirection() {
    Vec3 ret;

    ret.x = cos(_degToRad * transform.rotation.y);
    ret.y = 0;
    ret.z = sin(_degToRad * -transform.rotation.y);

    return ret;
  }

  Vec3 upDirection() {
    return Vec3::cross(forwardDirection(), rightDirection());
  }

  void setRotation(Vec3 rot) {
    transform.rotation.x = glm::mod(rot.x, 360.f);
    transform.rotation.y = glm::mod(rot.y, 360.f);
    transform.rotation.z = glm::mod(rot.z, 360.f);
  }

  void addRotation(Vec3 rot) {
    transform.rotation.x = glm::mod(transform.rotation.x + rot.x, 360.f);
    transform.rotation.y = glm::mod(transform.rotation.y + rot.y, 360.f);
    transform.rotation.z = glm::mod(transform.rotation.z + rot.z, 360.f);
  }

  void setRotation(float x, float y, float z) {
    transform.rotation.x = glm::mod(x, 360.f);
    transform.rotation.y = glm::mod(y, 360.f);
    transform.rotation.z = glm::mod(z, 360.f);
  }

  void addRotation(float x, float y, float z) {
    transform.rotation.x = glm::mod(transform.rotation.x + x, 360.f);
    transform.rotation.y = glm::mod(transform.rotation.y + y, 360.f);
    transform.rotation.z = glm::mod(transform.rotation.z + z, 360.f);
  }
};