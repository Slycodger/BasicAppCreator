public partial class Material : BufferType {
  //(Vec4)albedo
  //--------------------------------------------------
  public Vec4 albedo {
    get => basicApp_materialAlbedo(buffer);
    set => basicApp_setMaterialAlbedo(buffer, value);
  }
  //--------------------------------------------------



  //(float)metallic
  //--------------------------------------------------
  public float metallic {
    get => basicApp_materialMetallic(buffer);
    set => basicApp_setMaterialMetallic(buffer, value);
  }
  //--------------------------------------------------



  //(float)roughness
  //--------------------------------------------------
  public float roughness {
    get => basicApp_materialRoughness(buffer);
    set => basicApp_setMaterialRoughness(buffer, value);
  }
  //--------------------------------------------------



  //(Texture)albedoTexture
  //--------------------------------------------------
  public Texture albedoTexture {
    get => new Texture(basicApp_materialAlbedoTexture(buffer));
    set => basicApp_setMaterialAlbedoTexture(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Texture)normalTexture
  //--------------------------------------------------
  public Texture normalTexture {
    get => new Texture(basicApp_materialNormalTexture(buffer));
    set => basicApp_setMaterialNormalTexture(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Texture)metallicTexture
  //--------------------------------------------------
  public Texture metallicTexture {
    get => new Texture(basicApp_materialMetallicTexture(buffer));
    set => basicApp_setMaterialMetallicTexture(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Texture)roughnessTexture
  //--------------------------------------------------
  public Texture roughnessTexture {
    get => new Texture(basicApp_materialRoughnessTexture(buffer));
    set => basicApp_setMaterialRoughnessTexture(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Texture)ambientOcclusionTexture
  //--------------------------------------------------
  public Texture ambientOcclusionTexture {
    get => new Texture(basicApp_materialAmbientOcclusionTexture(buffer));
    set => basicApp_setMaterialAmbientOcclusionTexture(buffer, value.buffer);
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