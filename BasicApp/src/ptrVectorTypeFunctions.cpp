#include <Vector>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) int basicApp_ptrVectorLength(void* ptr) {
    if (!ptr)
      return 0;
    return ((std::vector<void*>*)ptr)->size();
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_ptrVectorAt(void* ptr, int64_t val) {
    if (!ptr)
      return 0;
    return (*(std::vector<void*>*)ptr)[val];
  }

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_ptrVectorBegin(void* ptr) {
    if (!ptr)
      return 0;
    return &((std::vector<void*>*)ptr)->front();
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_ptrVectorInsert(void* ptr, void* val) {
    if (!ptr || !val)
      return;
    ((std::vector<void*>*)ptr)->push_back(val);
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_ptrVectorClear(void* ptr) {
    if (!ptr)
      return;
    ((std::vector<void*>*)ptr)->clear();
  }

  //--------------------------------------------------
  __declspec(dllexport) void basicApp_ptrVectorRemove(void* ptr, int64_t val) {
    if (!ptr)
      return;
    ((std::vector<void*>*)ptr)->erase(((std::vector<void*>*)ptr)->begin() + val);
  }


#ifdef __cplusplus
}
#endif