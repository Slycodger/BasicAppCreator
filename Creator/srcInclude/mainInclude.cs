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
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_keyLatchKeys();
  //--------------------------------------------------



  //progBoiler
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyPressed(int key);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyHeld(int key);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_keyReleased(int key);
  //--------------------------------------------------





  //Keys
  const int KEY_ESCAPE = 256;
  const int KEY_Q = 81;
  const int KEY_T = 84;
  const int KEY_F = 70;
  const int KEY_N = 78;
  const int KEY_H = 72;
}