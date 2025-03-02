#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

  //----------------------------------------------------------------------------------------------------VARIABLE-FUNCTIONS
  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraFOV(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->FOV;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraFOV(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->FOV = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraNearClip(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->nearClip;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraNearClip(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->nearClip = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraFarClip(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->farClip;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraFarClip(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->farClip = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraRatio(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->ratio;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraRatio(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->ratio = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraWidth(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->width;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraWidth(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->width = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraHeight(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->height;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraHeight(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->height = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_cameraDepth(Camera* ptr) {
    if (!ptr)
      return 0;
    return ptr->depth;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraDepth(Camera* ptr, float val) {
    if (!ptr)
      return;
    ptr->depth = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraRotation(Camera* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->setRotation(val);
  }
  
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_cameraUpdatePerspective(Camera* ptr) {
    if (!ptr)
      return;
    ptr->updatePerspectiveView();
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_cameraUpdateOrthographic(Camera* ptr) {
    if (!ptr)
      return;
    ptr->updateOrthographicView();
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraPerspective(Camera* ptr, float fov, float ratio, float nearClip, float farClip) {
    if (!ptr)
      return;
    ptr->setPerspectiveView(fov, ratio, nearClip, farClip);
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setCameraOrthographic(Camera* ptr, float width, float height, float depth) {
    if (!ptr)
      return;
    ptr->setOrthographicView(width, height, depth);
  }

  //--------------------------------------------------
  __declspec(dllexport) Vec3 basicApp_cameraForwardDirection(Camera* ptr) {
    if (!ptr)
      return Vec3(0);
    return ptr->forwardDirection();
  }
  //--------------------------------------------------
  __declspec(dllexport) Vec3 basicApp_cameraRightDirection(Camera* ptr) {
    if (!ptr)
      return Vec3(0);
    return ptr->rightDirection();
  }
  //--------------------------------------------------
  __declspec(dllexport) Vec3 basicApp_cameraUpDirection(Camera* ptr) {
    if (!ptr)
      return Vec3(0);
    return ptr->upDirection();
  }

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_cameraIndex(Camera* ptr) {
    return ptr->getCameraIndex();
  }





  //----------------------------------------------------------------------------------------------------VARIABLE-FUNCTIONS
  //--------------------------------------------------
  __declspec(dllexport) int basicApp_cameraCameraCount() {
    return Camera::cameraCount;
  }

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_cameraCurrentCameraIndex() {
    return Camera::currentCamera;
  }

  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_setCameraCurrentCameraIndex(int val) {
    return Camera::setCurrentCamera(val);
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_cameraCurrentCamera() {
    return Camera::getCurrentCamera();
  }

#ifdef __cplusplus
}
#endif