public partial class Mesh : BufferType {
  //(Array<Vertex>)vertices
  //--------------------------------------------------
  public Array<Vertex> vertices { get; private set; }
  //--------------------------------------------------



  //(uint)triCount
  //--------------------------------------------------
  public uint triCount {
    get => basicApp_meshTriCount(buffer);
  }
  //--------------------------------------------------





  public Mesh(IntPtr ptr) : base(ptr) {
    //SIZEOF Vertex
    vertices = new Array<Vertex>(basicApp_meshVerticeBuffer(buffer), basicApp_meshVerticeLength(buffer), 44);
  }
}