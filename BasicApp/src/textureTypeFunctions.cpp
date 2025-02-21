#include "textureLoading.h"

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_textureWidth(Texture* ptr) {
    if (!ptr)
      return 0;
    return ptr->width;
  }

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_textureHeight(Texture* ptr) {
    if (!ptr)
      return 0;
    return ptr->height;
  }

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_textureType(Texture* ptr) {
    if (!ptr)
      return 0;
    return ptr->texType;
  }
#ifdef __cplusplus
}
#endif