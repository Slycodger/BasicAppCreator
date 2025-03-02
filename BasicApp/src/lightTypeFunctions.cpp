#include "light.h"

#ifdef __cplusplus
extern "C" {
#endif

  //----------------------------------------------------------------------------------------------------POINT-LIGHTS
  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_pointLightColor(PointLight* ptr) {
    if (!ptr)
      return Vec4(0);
    return ptr->activeLight.color;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setPointLightColor(PointLight* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->activeLight.color = val;
  }





  //----------------------------------------------------------------------------------------------------DIRECTIONAL-LIGHTS
  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_directionalLightDirection(DirectionalLight* ptr) {
    if (!ptr)
      return Vec4(0);
    return ptr->activeLight.direction;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setDirectionalLightDirection(DirectionalLight* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->activeLight.direction = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_directionalLightColor(DirectionalLight* ptr) {
    if (!ptr)
      return Vec4(0);
    return ptr->activeLight.color;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setDirectionalLightColor(DirectionalLight* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->activeLight.color = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_directionalLightFollowRotations(DirectionalLight* ptr) {
    if (!ptr)
      return 0;
    return ptr->followRotations;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setDirectionalLightFollowRotations(DirectionalLight* ptr, bool val) {
    if (!ptr)
      return;
    ptr->followRotations = val;
  }





  //----------------------------------------------------------------------------------------------------SPOT-LIGHTS
  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_spotLightDirection(SpotLight* ptr) {
    if (!ptr)
      return Vec4(0);
    return ptr->activeLight.direction;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setSpotLightDirection(SpotLight* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->activeLight.direction = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_spotLightColor(SpotLight* ptr) {
    if (!ptr)
      return Vec4(0);
    return ptr->activeLight.color;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setSpotLightColor(SpotLight* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->activeLight.color = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_spotLightFollowRotations(SpotLight* ptr) {
    if (!ptr)
      return 0;
    return ptr->followRotations;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setSpotLightFollowRotations(SpotLight* ptr, bool val) {
    if (!ptr)
      return;
    ptr->followRotations = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) float basicApp_spotLightInnerCutoff(SpotLight* ptr) {
    if (!ptr)
      return 0;
    return ptr->activeLight.innerCutoff;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setSpotLightInnerCutoff(SpotLight* ptr, float val) {
    if (!ptr)
      return;
    ptr->activeLight.innerCutoff = val;
  }


  //--------------------------------------------------
  __declspec(dllexport) float basicApp_spotLightOuterCutoff(SpotLight* ptr) {
    if (!ptr)
      return 0;
    return ptr->activeLight.outerCutoff;
  }
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setSpotLightOuterCutoff(SpotLight* ptr, float val) {
    if (!ptr)
      return;
    ptr->activeLight.outerCutoff = val;
  }
#ifdef __cplusplus
}
#endif