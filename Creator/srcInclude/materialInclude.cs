using System.Runtime.InteropServices;

public partial class Material {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialAlbedo(IntPtr ptr, Vec4 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_materialAlbedo(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialMetallic(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_materialMetallic(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialRoughness(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_materialRoughness(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialAlbedoTexture(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_materialAlbedoTexture(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialNormalTexture(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_materialNormalTexture(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialMetallicTexture(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_materialMetallicTexture(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialRoughnessTexture(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_materialRoughnessTexture(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setMaterialAmbientOcclusionTexture(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_materialAmbientOcclusionTexture(IntPtr ptr);
}