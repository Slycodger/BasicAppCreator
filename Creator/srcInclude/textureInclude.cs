using System.Runtime.InteropServices;

public partial class Texture {
  //Texture variables
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_textureWidth(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_textureHeight(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_textureType(IntPtr ptr);
  //--------------------------------------------------




  //Texture type
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern void basicApp_removeTexture(string name);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern IntPtr basicApp_getTexture(string name);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern IntPtr basicApp_loadEnvironmentTexture(string name, bool abs, bool flip);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern IntPtr basicApp_loadCubeMapTexture(string name, string[] textures, bool abs, bool flip, bool gCorrection);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern IntPtr basicApp_loadTexture(string name, int texType, bool abs, bool flip, bool gCorrection);
  //--------------------------------------------------
}