using System.Runtime.InteropServices;

public partial class Camera {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraFOV(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraFOV(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraNearClip(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraNearClip(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraFarClip(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraFarClip(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraRatio(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraRatio(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraWidth(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraWidth(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraHeight(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraHeight(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_cameraDepth(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraDepth(IntPtr ptr, float val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraRotation(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_cameraUpdatePerspective(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_cameraUpdateOrthographic(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraPerspective(IntPtr ptr, float fov, float ratio, float nearClip, float farClip);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setCameraOrthographic(IntPtr ptr, float width, float height, float depth);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec3 basicApp_cameraForwardDirection(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec3 basicApp_cameraRightDirection(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern Vec3 basicApp_cameraUpDirection(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_cameraIndex(IntPtr ptr);


  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_cameraCameraCount();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_cameraCurrentCameraIndex();
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_setCameraCurrentCameraIndex(int val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_cameraCurrentCamera();
}