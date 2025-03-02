using System.Runtime.InteropServices;

public partial class Program {
  //programControl
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern int basicApp_start(string title);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern bool basicApp_shouldClose();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_update();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_closeApp();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_end();

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setVsync(bool tf);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern bool basicApp_vsync();

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setMouseHide(bool tf);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_swapMouseHide();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern bool basicApp_mouseHide();

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern float basicApp_deltaTime();

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_deleteObj(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_deleteObjArray(IntPtr ptr);
  //--------------------------------------------------



  //flowControl
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setBgColorVec4(Vec4 color);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setBgColorVars(float r, float g, float b, float a);
  //--------------------------------------------------



  //uniqueTypes
  //--------------------------------------------------
  public enum Unique {
    INVALID = 0, 
    UNIQUE, 
    OBJECT, 
    CAMERA, 
    POINTLIGHT, 
    DIRECTIONALLIGHT, 
    SPOTLIGHT
  };
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern IntPtr basicApp_createUniqueType(Unique type);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_deleteUniqueType(IntPtr type);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern bool basicApp_saveUniqueType(IntPtr tType, string objName);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern IntPtr basicApp_instantiateUniqueType(string objName);

  //--------------------------------------------------



  //progBoiler
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_mainCameraLook();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setLookSpeed(float speed);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern float basicApp_lookSpeed();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_mainCameraMove();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setMoveSpeed(float speed);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern float basicApp_moveSpeed();
  //--------------------------------------------------



  //input
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyPressed(int key);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyHeld(int key);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyReleased(int key);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_scrolling();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_scrollUp();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_scrollDown();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_getNumlock();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_getShift();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_keyLatchKeys();
  //--------------------------------------------------



  //objects
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  static extern bool basicApp_setObjectMesh(IntPtr ptr, string mesh);
  //--------------------------------------------------



  //modelLoading
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  static extern bool basicApp_loadModel(string path, bool abs, string objName, bool flipUVs);
  //--------------------------------------------------





  //Keys
  const int KEY_ESCAPE = 256;
  const int KEY_Q = 81;
  const int KEY_T = 84;
  const int KEY_F = 70;
  const int KEY_N = 78;
  const int KEY_H = 72;
  const int KEY_E = 69;
  const int KEY_R = 82;
}