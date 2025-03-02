using System.Runtime.InteropServices;

public partial class DirectionalLight {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_directionalLightDirection(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setDirectionalLightDirection(IntPtr ptr, Vec4 val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_directionalLightColor(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setDirectionalLightColor(IntPtr ptr, Vec4 val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_directionalLightFollowRotations(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setDirectionalLightFollowRotations(IntPtr ptr, bool val);
}