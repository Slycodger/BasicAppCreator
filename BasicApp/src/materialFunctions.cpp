#include "material.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialAlbedo(Material* ptr, Vec4 val) {
    ptr->albedo = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_getMaterialAlbedo(Material* ptr) {
    return ptr->albedo;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialMetallic(Material* ptr, float val) {
    ptr->metallic = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_getMaterialMetallic(Material* ptr) {
    return ptr->metallic;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialRoughness(Material* ptr, float val) {
    ptr->roughness = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_getMaterialRoughness(Material* ptr) {
    return ptr->roughness;
  }

#ifdef __cplusplus
}
#endif