public enum TextureType { ALBEDO, NORMAL, METALLIC, ROUGHNESS, AO };

public partial class Texture : BufferType {
  //(int)width
  //--------------------------------------------------
  public int width {
    get => basicApp_textureWidth(buffer);
  }
  //--------------------------------------------------



  //(int)height
  //--------------------------------------------------
  public int height {
    get => basicApp_textureHeight(buffer);
  }
  //--------------------------------------------------

  

  //(TextureType)type
  //--------------------------------------------------
  public TextureType type {
    get => (TextureType)basicApp_textureType(buffer);
  }
  //--------------------------------------------------





  public Texture(IntPtr ptr) : base(ptr) { }


}