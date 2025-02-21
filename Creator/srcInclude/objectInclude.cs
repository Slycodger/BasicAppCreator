using System.Runtime.InteropServices;

public partial class Object {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_objectDependent(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setObjectDependent(IntPtr obj, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_objectDependencies(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_objectMaterial(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setObjectMaterial(IntPtr ptr, IntPtr val);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_objectSrcMaterial(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setObjectSrcMaterial(IntPtr ptr, IntPtr val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_objectMesh(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern string basicApp_objectType(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern bool basicApp_objectUi(IntPtr ptr);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setObjectUi(IntPtr ptr, bool val);
}