using System.Runtime.InteropServices;

public partial class MeshData {
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern IntPtr basicApp_createMeshBuffers(IntPtr vertices, Int64 vertSize, UInt64 triCount);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_updateMeshBuffersWithNew(IntPtr mesh, IntPtr vertices, Int64 vertSize, UInt64 triCount);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_updateMeshBuffers(IntPtr mesh);
  [DllImport("BasicApp.dll", CallingConvention = CallingConvention.Cdecl)]
  static extern void basicApp_deleteMeshData(IntPtr mData);
}