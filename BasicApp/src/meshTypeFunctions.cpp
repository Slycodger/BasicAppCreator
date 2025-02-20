#include "objects.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_meshVerticeBuffer(Mesh* ptr) {
    return ptr->vertices.data();
  }

  //--------------------------------------------------
  __declspec(dllexport) uint basicApp_meshTriCount(Mesh* ptr) {
    return *ptr->triCount;
  }

#ifdef __cplusplus
}
#endif