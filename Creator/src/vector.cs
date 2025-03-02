using System;

//--------------------------------------------------
public struct Vec2 {
  public float x;
  public float y;





  //--------------------------------------------------
  public override string ToString() {
    return $"{{{x}, {y}}}";
  }





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

  //(Vec3)vec = (Vec4){1, 2, 3, 4}
  public static implicit operator Vec3(Vec4 vec) { return new Vec3(vec.x, vec.y, vec.z); }

  public static Vec3 operator -(Vec3 a, Vec3 b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
  public static Vec3 operator +(Vec3 a, Vec3 b) { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
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
public struct Vec4 {
  public float x;
  public float y;
  public float z;
  public float w;




  //--------------------------------------------------
  public override string ToString() {
    return $"{x}, {y}, {z}, {w}";
  }





  //--------------------------------------------------
  //(Vec4)vec = (Vec3){1, 2, 3}
  public static implicit operator Vec4(Vec3 vec) { return new Vec4(vec.x, vec.y, vec.z, 0); }
  //--------------------------------------------------





  public Vec4(float X, float Y, float Z, float W) {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }
}
//--------------------------------------------------