using System.Runtime.InteropServices;

public partial class SpotLight {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_spotLightDirection(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setSpotLightDirection(IntPtr ptr, Vec4 val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec4 basicApp_spotLightColor(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setSpotLightColor(IntPtr ptr, Vec4 val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_spotLightFollowRotations(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setSpotLightFollowRotations(IntPtr ptr, bool val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_spotLightInnerCutoff(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setSpotLightInnerCutoff(IntPtr ptr, float val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_spotLightOuterCutoff(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setSpotLightOuterCutoff(IntPtr ptr, float val);
}