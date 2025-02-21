using System.Runtime.InteropServices;

public partial class Mesh {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_meshVerticeBuffer(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Int64 basicApp_meshVerticeLength(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern uint basicApp_meshTriCount(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern bool basicApp_loadMesh(IntPtr ptr, string name);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  public static extern bool basicApp_unloadMesh(string name);
}