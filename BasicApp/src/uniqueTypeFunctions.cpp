#include "transform.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) Transform basicApp_uniqueTypeTransform(UniqueType* ptr) {
    if (!ptr)
      return Transform();
    return ptr->transform;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeTransform(UniqueType* ptr, Transform val) {
    if (!ptr)
      return;
    ptr->transform = val;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeTransformPosition(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->transform.position = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeTransformPosition(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->transform.position;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeTransformScale(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->transform.scale = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeTransformScale(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->transform.scale;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeTransformRotation(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->transform.rotation = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeTransformRotation(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->transform.rotation;
  }
  //--------------------------------------------------



  //--------------------------------------------------
  __declspec(dllexport) Transform basicApp_uniqueTypeRelativeTransform(UniqueType* ptr) {
    if (!ptr)
      return Transform();
    return ptr->relativeTransform;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeRelativeTransform(UniqueType* ptr, Transform val) {
    if (!ptr)
      return;
    ptr->relativeTransform = val;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeRelativeTransformPosition(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->relativeTransform.position = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeRelativeTransformPosition(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->relativeTransform.position;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeRelativeTransformScale(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->relativeTransform.scale = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeRelativeTransformScale(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->relativeTransform.scale;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeRelativeTransformRotation(UniqueType* ptr, Vec3 val) {
    if (!ptr)
      return;
    ptr->relativeTransform.rotation = val;
  }
  __declspec(dllexport) Vec3 basicApp_uniqueTypeRelativeTransformRotation(UniqueType* ptr) {
    if (!ptr)
      return Vec3();
    return ptr->relativeTransform.rotation;
  }
  //--------------------------------------------------



  //--------------------------------------------------
  __declspec(dllexport) UniqueType* basicApp_uniqueTypeParent(UniqueType* ptr) {
    if (!ptr)
      return 0;
    return ptr->parent;
  }
  
  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setUniqueTypeParent(UniqueType* ptr, UniqueType* val) {
    if (!ptr || !val)
      return;
    ptr->setParent(val);
  }
  __declspec(dllexport) void* basicApp_uniqueTypeChildren(UniqueType* ptr) {
    if (!ptr)
      return 0;
    return &ptr->children;
  }
  //--------------------------------------------------



  //--------------------------------------------------
  __declspec(dllexport) bool basicApp_uniqueTypeActive(UniqueType* ptr) {
    if (!ptr)
      return false;
    return ptr->active;
  }
  __declspec(dllexport) void basicApp_setUniqueTypeActive(UniqueType* ptr, bool val) {
    if (!ptr)
      return;
    ptr->active = val;
  }
  //--------------------------------------------------

#ifdef __cplusplus
}
#endif