public struct Vertex {
  public Vec3 position;
  public Vec3 normal;
  public Vec3 tangent;
  public Vec2 uv;

  public Vertex() {
    position = 0;
    normal = 0;
    tangent = 0;
    uv = 0;
  }

  public Vertex(Vec3 p, Vec3 n, Vec3 t, Vec2 u) {
    position = p;
    normal = n;
    tangent = t;
    uv = u;
  }
}