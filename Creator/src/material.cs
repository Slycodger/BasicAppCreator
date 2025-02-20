public partial class Material : BufferType {
  //(Vec4)albedo
  //--------------------------------------------------
  public Vec4 albedo {
    get => basicApp_getMaterialAlbedo(buffer);
    set => basicApp_setMaterialAlbedo(buffer, value);
  }
  //--------------------------------------------------



  //(float)metallic
  //--------------------------------------------------
  public float metallic {
    get => basicApp_getMaterialMetallic(buffer);
    set => basicApp_setMaterialMetallic(buffer, value);
  }
  //--------------------------------------------------



  //(float)roughness
  //--------------------------------------------------
  public float roughness {
    get => basicApp_getMaterialRoughness(buffer);
    set => basicApp_setMaterialRoughness(buffer, value);
  }
  //--------------------------------------------------





  //Copies the values from the current material to another, without changing the internal buffer
  //--------------------------------------------------
  public void CopyTo(ref Material to) {
    to.albedo = albedo;
    to.metallic = metallic;
    to.roughness = roughness;
  }





  //--------------------------------------------------
  //Material mat = (IntPtr)4;
  public static implicit operator Material(IntPtr p) => new Material(p);
  //--------------------------------------------------





  public Material(IntPtr ptr) : base(ptr) { }
}