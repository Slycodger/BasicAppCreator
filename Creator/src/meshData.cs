
public partial class MeshData {
  public IntPtr meshData { get; }





  //Updates the mesh with the pointers it already has
  //--------------------------------------------------
  public void Update() {
    basicApp_updateMeshBuffers(meshData);
  }



  //Updates the mesh
  //--------------------------------------------------
  public void Update(Array<float> vertices, UInt64 tCount) {
    basicApp_updateMeshBuffersWithNew(meshData, vertices.buffer, vertices.length, tCount);
  }





  public MeshData(Array<float> vertices, UInt64 tCount) {
    meshData = basicApp_createMeshBuffers(vertices.buffer, vertices.length, tCount);
  }

  private MeshData() { }





  ~MeshData() {
    basicApp_deleteMeshData(meshData);
  }
}