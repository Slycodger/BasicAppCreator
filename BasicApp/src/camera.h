#pragma once
#include "openGL.h"
#include "vector.h"
#include "mathConstants.h"
#include "transform.h"
#include "constants.h"
#include "algorithm"

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
      void* newScr = ((ScriptBase*)scrV)->getNew();
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
    transform.rotation.y = 270.f;
    updatePerspectiveView();
    updateOrthographicView();
  }
  Camera(float fov, float N, float F, float R, float W, float H, float D) : UniqueType(), FOV(fov), nearClip(N), farClip(F), ratio(R), width(W), height(H), depth(D), perspectiveView(0), orthographicView(0), viewMatrix(1) {
    if (!addCamera(this))
      index = -1;
    transform.rotation.y = 270.f;
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
    Vec3 lookDir = Vec3(0);
    float pitch = transform.rotation.x * _degToRadF;
    float yaw = transform.rotation.y * _degToRadF;

    lookDir.x = cos(yaw) * cos(pitch);
    lookDir.y = sin(pitch);
    lookDir.z = sin(yaw) * cos(pitch);

    viewMatrix = glm::lookAt(transform.position.toGLM(), (transform.position + lookDir).toGLM(), { 0, 1, 0 });
  }

  Vec3 forwardDirection() {
    Vec3 ret;

    float pitch = transform.rotation.x * _degToRadF;
    float yaw = transform.rotation.y * _degToRadF;

    ret.x = cos(yaw) * cos(pitch);
    ret.y = sin(pitch);
    ret.z = sin(yaw) * cos(pitch);

    return ret;
  }

  Vec3 rightDirection() {
    Vec3 ret;

    float yaw = (transform.rotation.y + 90.f) * _degToRadF;

    ret.x = cos(yaw);
    ret.y = 0;
    ret.z = sin(yaw);

    return ret;
  }

  Vec3 upDirection() {
    return -Vec3::cross(forwardDirection(), rightDirection());
  }

  void setRotation(Vec3 rot) {
    transform.rotation.x = std::clamp(rot.x, -89.f, 89.f);
    transform.rotation.y = glm::mod(rot.y, 360.f);
    transform.rotation.z = glm::mod(rot.z, 360.f);
  }

  void addRotation(Vec3 rot) {
    transform.rotation.x = std::clamp(transform.rotation.x + rot.x, -89.f, 89.f);
    transform.rotation.y = glm::mod(transform.rotation.y + rot.y, 360.f);
    transform.rotation.z = glm::mod(transform.rotation.z + rot.z, 360.f);
  }

  void setRotation(float x, float y, float z) {
    transform.rotation.x = std::clamp(x, -89.f, 89.f);
    transform.rotation.y = glm::mod(y, 360.f);
    transform.rotation.z = glm::mod(z, 360.f);
  }

  void addRotation(float x, float y, float z) {
    transform.rotation.x = std::clamp(transform.rotation.x + x, -89.f, 89.f);
    transform.rotation.y = glm::mod(transform.rotation.y + y, 360.f);
    transform.rotation.z = glm::mod(transform.rotation.z + z, 360.f);
  }
};