public partial class Camera : UniqueType {
  //(Vec3)rotation
  //--------------------------------------------------
  public override Vec3 rotation {
    get => basicApp_uniqueTypeTransformRotation(buffer);
    set => basicApp_setCameraRotation(buffer, value);
  }
  //--------------------------------------------------



  //(float)FOV
  //--------------------------------------------------
  public float FOV {
    get => basicApp_cameraFOV(buffer);
    set => basicApp_setCameraFOV(buffer, value);
  }
  //--------------------------------------------------



  //(float)nearClip
  //--------------------------------------------------
  public float nearClip {
    get => basicApp_cameraNearClip(buffer);
    set => basicApp_setCameraNearClip(buffer, value);
  }
  //--------------------------------------------------



  //(float)farClip
  //--------------------------------------------------
  public float farClip {
    get => basicApp_cameraFarClip(buffer);
    set => basicApp_setCameraFarClip(buffer, value);
  }
  //--------------------------------------------------



  //(float)ratio
  //--------------------------------------------------
  public float ratio {
    get => basicApp_cameraRatio(buffer);
    set => basicApp_setCameraRatio(buffer, value);
  }
  //--------------------------------------------------



  //(float)width
  //--------------------------------------------------
  public float width {
    get => basicApp_cameraWidth(buffer);
    set => basicApp_setCameraWidth(buffer, value);
  }
  //--------------------------------------------------



  //(float)height
  //--------------------------------------------------
  public float height {
    get => basicApp_cameraHeight(buffer);
    set => basicApp_setCameraHeight(buffer, value);
  }
  //--------------------------------------------------



  //(float)depth
  //--------------------------------------------------
  public float depth {
    get => basicApp_cameraDepth(buffer);
    set => basicApp_setCameraDepth(buffer, value);
  }
  //--------------------------------------------------



  //(Vec3)forwardDirection
  //--------------------------------------------------
  public Vec3 forwardDirection {
    get => basicApp_cameraForwardDirection(buffer);
  }
  //--------------------------------------------------



  //(Vec3)rightDirection
  //--------------------------------------------------
  public Vec3 rightDirection {
    get => basicApp_cameraRightDirection(buffer);
  }
  //--------------------------------------------------



  //(Vec3)upDirection
  //--------------------------------------------------
  public Vec3 upDirection {
    get => basicApp_cameraUpDirection(buffer);
  }
  //--------------------------------------------------



  //(int)index
  //--------------------------------------------------
  public int index {
    get => basicApp_cameraIndex(buffer);
  }
  //--------------------------------------------------





  //--------------------------------------------------
  public void UpdatePerspectiveView() {
    basicApp_cameraUpdatePerspective(buffer);
  }



  //--------------------------------------------------
  public void UpdateOrthographicView() {
    basicApp_cameraUpdateOrthographic(buffer);
  }



  //--------------------------------------------------
  public void SetPerspectiveView(float fov, float ratio, float nearClip, float farClip) {
    basicApp_setCameraPerspective(buffer,fov, ratio, nearClip, farClip);
  }



  //--------------------------------------------------
  public void SetOrthograhicView(float width, float height, float depth) {
    basicApp_setCameraOrthographic(buffer, width, height, depth);
  }





  public Camera(IntPtr ptr) : base(ptr) { }
}