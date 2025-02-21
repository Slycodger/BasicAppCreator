#include "objects.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectDependent(Object* ptr) {
    if (!ptr)
      return 0;
    return ptr->dependent;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectDependent(Object* ptr, Object* val) {
    if (!ptr || !val)
      return;
    ptr->setDependent(val);
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectDependencies(Object* ptr) {
    if (!ptr)
      return 0;
    return &ptr->dependencies;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectMaterial(Object* ptr) {
    if (!ptr)
      return 0;
    return ptr->material;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectMaterial(Object* ptr, Material* val) {
    if (!ptr || !val)
      return;
    ptr->material = val;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectSrcMaterial(Object* ptr) {
    if (!ptr)
      return 0;
    return &ptr->srcMaterial;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectSrcMaterial(Object* ptr, Material* val) {
    if (!ptr || !val)
      return;
    ptr->srcMaterial = *val;
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_objectMesh(Object* ptr) {
    if (!ptr)
      return 0;
    return ptr->mesh;
  }

  //--------------------------------------------------
  __declspec(dllexport) const char* basicApp_objectType(Object* ptr) {
    if (!ptr)
      return "\0";
    return ptr->objType.c_str();
  }

  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_objectUi(Object* ptr) {
    if (!ptr)
      return false;
    return ptr->ui;
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setObjectUi(Object* ptr, bool val) {
    if (!ptr)
      return;
    ptr->ui = val;
  }

#ifdef __cplusplus
}
#endif