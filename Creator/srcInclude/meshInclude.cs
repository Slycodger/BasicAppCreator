using System.Runtime.InteropServices;

public partial class Mesh {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_meshVerticeBuffer(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern uint basicApp_meshTriCount(IntPtr ptr);
}