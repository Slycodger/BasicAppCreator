#include "objects.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectDependent(Object* obj) {
    return obj->dependent;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectDependencies(Object* obj) {
    return &obj->dependencies;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectMaterial(Object* obj) {
    return obj->material;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectMaterial(Object* obj, Material* val) {
    obj->material = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectSrcMaterial(Object* obj) {
    return &obj->srcMaterial;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectSrcMaterial(Object* obj, Material* val) {
    obj->srcMaterial = *val;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectMesh(Object* obj) {
    return obj->mesh;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectMesh(Object* obj, Mesh* val) {
    obj->mesh = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) const char* basicApp_objectType(Object* obj) {
    return obj->objType.c_str();
  }

  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_objectUi(Object* obj) {
    return obj->ui;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectUi(Object* obj, bool val) {
    obj->ui = val;
  }

#ifdef __cplusplus
}
#endif