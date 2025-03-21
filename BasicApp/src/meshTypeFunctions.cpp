#include "objects.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_meshVerticeBuffer(Mesh* ptr) {
    if (!ptr)
      return 0;
    return ptr->vertices.data();
  }

  //--------------------------------------------------
  __declspec(dllexport) int64_t basicApp_meshVerticeLength(Mesh* ptr) {
    if (!ptr)
      return 0;
    return ptr->vertices.size();
  }

  //--------------------------------------------------
  __declspec(dllexport) uint basicApp_meshTriCount(Mesh* ptr) {
    if (!ptr)
      return 0;
    return *ptr->triCount;
  }

#ifdef __cplusplus
}
#endif