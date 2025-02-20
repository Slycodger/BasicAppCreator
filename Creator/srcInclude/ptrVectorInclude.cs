using System;
using System.Runtime.InteropServices;

public partial class PtrVector {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern int basicApp_ptrVectorLength(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_ptrVectorAt(IntPtr ptr, Int64 val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_ptrVectorBegin(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_ptrVectorInsert(IntPtr ptr, IntPtr val);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_ptrVectorClear(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_ptrVectorRemove(IntPtr ptr, Int64 val);
}