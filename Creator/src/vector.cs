using System;

//--------------------------------------------------
public struct Vec4 {
  public float x;
  public float y;
  public float z;
  public float w;






  public Vec4(float X, float Y, float Z, float W) {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }
}
//--------------------------------------------------





//--------------------------------------------------
public struct Vec3 {
  public float x;
  public float y;
  public float z;





  //Returns the string version of the vector
  //--------------------------------------------------
  public override string ToString() {
    return $"{{{x}, {y}, {z}}}";
  }





  //--------------------------------------------------
  //(Vec3)vec = (float)4;
  public static implicit operator Vec3(float a) { return new Vec3(a); }
  //--------------------------------------------------





  public Vec3(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
  }

  public Vec3(float a) {
    x = y = z = a;
  }
}
//--------------------------------------------------





//--------------------------------------------------
public struct Vec2 {
  public float x;
  public float y;





  //--------------------------------------------------
  //(Vec2)vec = (float)3;
  public static implicit operator Vec2(float a) { return new Vec2(a); }
  //--------------------------------------------------





  public Vec2(float X, float Y) {
    x = X;
    y = Y;
  }

  public Vec2(float a) {
    x = y = a;
  }

  public override string ToString() {
    return $"{{{x}, {y}}}";
  }
}
//--------------------------------------------------