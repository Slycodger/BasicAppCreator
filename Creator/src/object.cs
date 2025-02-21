public partial class Object : UniqueType {
  //(PtrVector)dependencies
  //--------------------------------------------------
  public PtrVector dependencies { get; private set; }
  //--------------------------------------------------



  //(IntPtr)dependent
  //--------------------------------------------------
  public Object dependent {
    get => new Object(basicApp_objectDependent(buffer));
    set => basicApp_setObjectDependent(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Material)material
  //--------------------------------------------------
  public Material material {
    get => new Material(basicApp_objectMaterial(buffer));
    set => basicApp_setObjectMaterial(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Material)srcMaterial
  //--------------------------------------------------
  private Material _srcMaterial;
  public Material srcMaterial {
    get => _srcMaterial;
    set => basicApp_setObjectSrcMaterial(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(Mesh)mesh
  //--------------------------------------------------
  public Mesh mesh {
    get => new Mesh(basicApp_objectMesh(buffer));
  }
  //--------------------------------------------------



  //(string)objType
  //--------------------------------------------------
  public string objType {
    get => basicApp_objectType(buffer);
  }
  //--------------------------------------------------



  //(bool)ui
  //--------------------------------------------------
  public bool ui {
    get => basicApp_objectUi(buffer);
    set => basicApp_setObjectUi(buffer, value);
  }
  //--------------------------------------------------





  public Object(IntPtr ptr) : base(ptr) {
    dependencies = new PtrVector(basicApp_objectDependencies(buffer));
    _srcMaterial = new Material(basicApp_objectSrcMaterial(buffer));
  }
}