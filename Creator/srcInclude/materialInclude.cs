using System.Runtime.InteropServices;

public partial class Material {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialAlbedo(IntPtr ptr, Vec4 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_getMaterialAlbedo(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialMetallic(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_getMaterialMetallic(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialRoughness(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_getMaterialRoughness(IntPtr ptr);
}