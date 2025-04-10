using System.Runtime.InteropServices;

public partial class TextBox {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  public static extern IntPtr basicApp_createTextBox();

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  static extern void basicApp_setTextBoxText(IntPtr ptr, string str);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
  static extern string basicApp_textBoxText(IntPtr ptr);

  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setTextBoxFontSize(IntPtr ptr, float size);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_textBoxFontSize(IntPtr ptr);


  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_setTextBoxLineSize(IntPtr ptr, float size);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern float basicApp_textBoxLineSize(IntPtr ptr);


  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_textBoxUpdateText(IntPtr ptr);
}