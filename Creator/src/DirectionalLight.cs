public partial class DirectionalLight : UniqueType {
  //(Vec4)direction
  //--------------------------------------------------
  public Vec4 direction {
    get => basicApp_directionalLightDirection(buffer);
    set => basicApp_setDirectionalLightDirection(buffer, value);
  }
  //--------------------------------------------------



  //(Vec4)color;
  //--------------------------------------------------
  public Vec4 color {
    get => basicApp_directionalLightColor(buffer);
    set => basicApp_setDirectionalLightColor(buffer, value);
  }
  //--------------------------------------------------



  //(bool) followRotations
  //--------------------------------------------------
  public bool followRotations {
    get => basicApp_directionalLightFollowRotations(buffer);
    set => basicApp_setDirectionalLightFollowRotations(buffer, value);
  }
  //--------------------------------------------------





  public DirectionalLight(IntPtr ptr) : base(ptr) { }
}