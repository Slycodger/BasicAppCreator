using System.Runtime.InteropServices;

public partial class PointLight {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_pointLightColor(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setPointLightColor(IntPtr ptr, Vec4 val);
}