#include "material.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialAlbedo(Material* ptr, Vec4 val) {
    if (!ptr)
      return;
    ptr->albedo = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) Vec4 basicApp_materialAlbedo(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->albedo;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialMetallic(Material* ptr, float val) {
    if (!ptr)
      return;
    ptr->metallic = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) float basicApp_materialMetallic(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->metallic;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialRoughness(Material* ptr, float val) {
    if (!ptr)
      return;
    ptr->roughness = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) float basicApp_materialRoughness(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->roughness;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialAlbedoTexture(Material* ptr, Texture* val) {
    if (!ptr || !val)
      return;
    ptr->albedoMap = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_materialAlbedoTexture(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->albedoMap;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialNormalTexture(Material* ptr, Texture* val) {
    if (!ptr || !val)
      return;
    ptr->normalMap = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_materialNormalTexture(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->normalMap;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialMetallicTexture(Material* ptr, Texture* val) {
    if (!ptr || !val)
      return;
    ptr->metallicMap = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_materialMetallicTexture(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->metallicMap;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialRoughnessTexture(Material* ptr, Texture* val) {
    if (!ptr || !val)
      return;
    ptr->roughnessMap = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_materialRoughnessTexture(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->roughnessMap;
  }


  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setMaterialAmbientOcclusionTexture(Material* ptr, Texture* val) {
    if (!ptr || !val)
      return;
    ptr->aoMap = val;
  }
  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_materialAmbientOcclusionTexture(Material* ptr) {
    if (!ptr)
      return 0;
    return ptr->aoMap;
  }

#ifdef __cplusplus
}
#endif