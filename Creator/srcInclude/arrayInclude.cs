using System.Runtime.InteropServices;

public class ArrayData {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern IntPtr basicApp_createArray(Int64 size);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern void basicApp_deleteArray(IntPtr ptr);
}