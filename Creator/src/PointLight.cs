public partial class PointLight : UniqueType {
  //(Vec4)color
  //--------------------------------------------------
  public Vec4 color {
    get => basicApp_pointLightColor(buffer);
    set => basicApp_setPointLightColor(buffer, value);
  }
  //--------------------------------------------------





  public PointLight(IntPtr ptr) : base(ptr) { }
}