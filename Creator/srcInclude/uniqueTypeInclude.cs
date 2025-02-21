using System.Runtime.InteropServices;

public partial class UniqueType {
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_uniqueTypeParent(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setUniqueTypeParent(IntPtr ptr, IntPtr val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_uniqueTypeChildren(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_uniqueTypeActive(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setUniqueTypeActive(IntPtr ptr, bool val);
  //--------------------------------------------------



  //Transform
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern SceneTransform basicApp_uniqueTypeTransform(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeTransform(IntPtr ptr, SceneTransform val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeTransformPosition(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeTransformPosition(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeTransformScale(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeTransformScale(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeTransformRotation(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeTransformRotation(IntPtr ptr);
  //--------------------------------------------------



  //Relative transform
  //--------------------------------------------------
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern SceneTransform basicApp_uniqueTypeRelativeTransform(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeRelativeTransform(IntPtr ptr, SceneTransform val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeRelativeTransformPosition(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeRelativeTransformPosition(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeRelativeTransformScale(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeRelativeTransformScale(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_setUniqueTypeRelativeTransformRotation(IntPtr ptr, Vec3 val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern Vec3 basicApp_uniqueTypeRelativeTransformRotation(IntPtr ptr);
  //--------------------------------------------------
}