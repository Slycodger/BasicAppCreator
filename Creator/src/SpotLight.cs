public partial class SpotLight : UniqueType {
  //(Vec4)direction
  //--------------------------------------------------
  public Vec4 direction {
    get => basicApp_spotLightDirection(buffer);
    set => basicApp_setSpotLightDirection(buffer, value);
  }
  //--------------------------------------------------



  //(Vec4)color;
  //--------------------------------------------------
  public Vec4 color {
    get => basicApp_spotLightColor(buffer);
    set => basicApp_setSpotLightColor(buffer, value);
  }
  //--------------------------------------------------



  //(bool) followRotations
  //--------------------------------------------------
  public bool followRotations {
    get => basicApp_spotLightFollowRotations(buffer);
    set => basicApp_setSpotLightFollowRotations(buffer, value);
  }
  //--------------------------------------------------



  //(float) innerCutoff
  //--------------------------------------------------
  public float innerCutoff {
    get => basicApp_spotLightInnerCutoff(buffer);
    set => basicApp_setSpotLightInnerCutoff(buffer, value);
  }
  //--------------------------------------------------



  //(float) outerCutoff
  //--------------------------------------------------
  public float outerCutoff {
    get => basicApp_spotLightOuterCutoff(buffer);
    set => basicApp_setSpotLightOuterCutoff(buffer, value);
  }
  //--------------------------------------------------





  public SpotLight(IntPtr ptr) : base(ptr) { }
}