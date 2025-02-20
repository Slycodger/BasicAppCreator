public struct SceneTransform {
  //(Vec3)position
  //--------------------------------------------------
  public Vec3 position;
  //--------------------------------------------------



  //(Vec3)scale
  //--------------------------------------------------
  public Vec3 scale;
  //--------------------------------------------------



  //(Vec3)rotation
  //--------------------------------------------------
  public Vec3 rotation;
  //--------------------------------------------------





  public SceneTransform() {
    position = new(0);
    scale = new(1);
    rotation = new(0);
  }
}