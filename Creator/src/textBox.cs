using System;

public partial class TextBox : Object {

  public string Text {
    get => basicApp_textBoxText(buffer);
    set => basicApp_setTextBoxText(buffer, value);
  }

  public float FontSize {
    get => basicApp_textBoxFontSize(buffer);
    set => basicApp_setTextBoxFontSize(buffer, value);
  }

  public float LineSize {
    get => basicApp_textBoxLineSize(buffer);
    set => basicApp_setTextBoxLineSize(buffer, value);
  }


  public void UpdateText() {
    basicApp_textBoxUpdateText(buffer);
  }


  public TextBox(IntPtr ptr) : base (ptr) {

  }
}