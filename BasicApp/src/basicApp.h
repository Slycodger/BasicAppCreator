#pragma once


//programControl
#ifdef _PROGRAM_CONTROL

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) int           basicApp_start(const char* title);
  __declspec(dllexport) bool          basicApp_shouldClose();
  __declspec(dllexport) void          basicApp_update();
  __declspec(dllexport) void          basicApp_closeApp();
  __declspec(dllexport) void          basicApp_end();

  __declspec(dllexport) void          basicApp_setVsync(bool tf);
  __declspec(dllexport) bool          basicApp_vsync();

  __declspec(dllexport) void          basicApp_setMouseHide(bool tf);
  __declspec(dllexport) void          basicApp_swapMouseHide();
  __declspec(dllexport) bool          basicApp_mouseHide();

  __declspec(dllexport) float         basicApp_deltaTime();

  __declspec(dllexport) void         basicApp_deleteObj(void* ptr);
  __declspec(dllexport) void         basicApp_deleteObjArray(void* ptr);


#ifdef __cplusplus
}
#endif

#endif



//flowControl
#ifdef _FLOW_CONTROL

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) void          basicApp_setBgColorVec4(Vec4 color);
  __declspec(dllexport) void          basicApp_setBgColorVars(float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif

#endif



//uniqueTypes
#ifdef _UNIQUE_TYPES

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) UniqueType*   basicApp_createUniqueType(Unique::Types type);


#ifdef __cplusplus
}
#endif

#endif



//progBoiler
#ifdef _PROG_BOILER

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) void          basicApp_mainCameraLook();
  __declspec(dllexport) void          basicApp_setLookSpeed(float speed);
  __declspec(dllexport) float         basicApp_lookSpeed();
  __declspec(dllexport) void          basicApp_mainCameraMove();
  __declspec(dllexport) void          basicApp_setMoveSpeed(float speed);
  __declspec(dllexport) float         basicApp_moveSpeed();

#ifdef __cplusplus
}
#endif

#endif



//input
#ifdef _INPUT

#ifdef __cplusplus
extern "C" {
#endif

  __declspec(dllexport) bool          basicApp_keyPressed(int key);
  __declspec(dllexport) bool          basicApp_keyHeld(int key);
  __declspec(dllexport) bool          basicApp_keyReleased(int key);
  __declspec(dllexport) bool          basicApp_scrolling();
  __declspec(dllexport) bool          basicApp_scrollUp();
  __declspec(dllexport) bool          basicApp_scrollDown();
  __declspec(dllexport) bool          basicApp_getNumlock();
  __declspec(dllexport) bool          basicApp_getShift();
  __declspec(dllexport) void          basicApp_keyLatchKeys();

#ifdef __cplusplus
}
#endif

#endif