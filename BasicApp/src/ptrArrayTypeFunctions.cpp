#include <stdint.h>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_createArray(int64_t size) {
    return new char[size];
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_deleteArray(void* ptr) {
    if (!ptr)
      return;
    delete[](ptr);
  }

#ifdef __cplusplus
}
#endif