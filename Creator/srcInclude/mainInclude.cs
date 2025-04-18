﻿using System.Runtime.InteropServices;

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
  const int KEY_SPACE = 32;
  const int KEY_APOSTROPHE = 39;
  const int KEY_COMMA = 44;
  const int KEY_MINUS = 45;
  const int KEY_PERIOD = 46;
  const int KEY_SLASH = 47;
  const int KEY_0 = 48;
  const int KEY_1 = 49;
  const int KEY_2 = 50;
  const int KEY_3 = 51;
  const int KEY_4 = 52;
  const int KEY_5 = 53;
  const int KEY_6 = 54;
  const int KEY_7 = 55;
  const int KEY_8 = 56;
  const int KEY_9 = 57;
  const int KEY_SEMICOLON = 59;
  const int KEY_EQUAL = 61;
  const int KEY_A = 65;
  const int KEY_B = 66;
  const int KEY_C = 67;
  const int KEY_D = 68;
  const int KEY_E = 69;
  const int KEY_F = 70;
  const int KEY_G = 71;
  const int KEY_H = 72;
  const int KEY_I = 73;
  const int KEY_J = 74;
  const int KEY_K = 75;
  const int KEY_L = 76;
  const int KEY_M = 77;
  const int KEY_N = 78;
  const int KEY_O = 79;
  const int KEY_P = 80;
  const int KEY_Q = 81;
  const int KEY_R = 82;
  const int KEY_S = 83;
  const int KEY_T = 84;
  const int KEY_U = 85;
  const int KEY_V = 86;
  const int KEY_W = 87;
  const int KEY_X = 88;
  const int KEY_Y = 89;
  const int KEY_Z = 90;
  const int KEY_LEFT_BRACKET = 91;
  const int KEY_BACKSLASH = 92;
  const int KEY_RIGHT_BRACKET = 93;
  const int KEY_GRAVE_ACCENT = 96;
  const int KEY_WORLD_1 = 161;
  const int KEY_WORLD_2 = 162;
  const int KEY_ESCAPE = 256;
  const int KEY_ENTER = 257;
  const int KEY_TAB = 258;
  const int KEY_BACKSPACE = 259;
  const int KEY_INSERT = 260;
  const int KEY_DELETE = 261;
  const int KEY_RIGHT = 262;
  const int KEY_LEFT = 263;
  const int KEY_DOWN = 264;
  const int KEY_UP = 265;
  const int KEY_PAGE_UP = 266;
  const int KEY_PAGE_DOWN = 267;
  const int KEY_HOME = 268;
  const int KEY_END = 269;
  const int KEY_CAPS_LOCK = 280;
  const int KEY_SCROLL_LOCK = 281;
  const int KEY_NUM_LOCK = 282;
  const int KEY_PRINT_SCREEN = 283;
  const int KEY_PAUSE = 284;
  const int KEY_F1 = 290;
  const int KEY_F2 = 291;
  const int KEY_F3 = 292;
  const int KEY_F4 = 293;
  const int KEY_F5 = 294;
  const int KEY_F6 = 295;
  const int KEY_F7 = 296;
  const int KEY_F8 = 297;
  const int KEY_F9 = 298;
  const int KEY_F10 = 299;
  const int KEY_F11 = 300;
  const int KEY_F12 = 301;
  const int KEY_F13 = 302;
  const int KEY_F14 = 303;
  const int KEY_F15 = 304;
  const int KEY_F16 = 305;
  const int KEY_F17 = 306;
  const int KEY_F18 = 307;
  const int KEY_F19 = 308;
  const int KEY_F20 = 309;
  const int KEY_F21 = 310;
  const int KEY_F22 = 311;
  const int KEY_F23 = 312;
  const int KEY_F24 = 313;
  const int KEY_F25 = 314;
  const int KEY_KP_0 = 320;
  const int KEY_KP_1 = 321;
  const int KEY_KP_2 = 322;
  const int KEY_KP_3 = 323;
  const int KEY_KP_4 = 324;
  const int KEY_KP_5 = 325;
  const int KEY_KP_6 = 326;
  const int KEY_KP_7 = 327;
  const int KEY_KP_8 = 328;
  const int KEY_KP_9 = 329;
  const int KEY_KP_DECIMAL = 330;
  const int KEY_KP_DIVIDE = 331;
  const int KEY_KP_MULTIPLY = 332;
  const int KEY_KP_SUBTRACT = 333;
  const int KEY_KP_ADD = 334;
  const int KEY_KP_ENTER = 335;
  const int KEY_KP_EQUAL = 336;
  const int KEY_LEFT_SHIFT = 340;
  const int KEY_LEFT_CONTROL = 341;
  const int KEY_LEFT_ALT = 342;
  const int KEY_LEFT_SUPER = 343;
  const int KEY_RIGHT_SHIFT = 344;
  const int KEY_RIGHT_CONTROL = 345;
  const int KEY_RIGHT_ALT = 346;
  const int KEY_RIGHT_SUPER = 347;
  const int KEY_MENU = 348;
}