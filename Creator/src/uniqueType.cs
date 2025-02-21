public unsafe partial class UniqueType : BufferType {
  //(SceneTransform)transform
  //--------------------------------------------------
  public SceneTransform transform {
    get => basicApp_uniqueTypeTransform(buffer);
    set => basicApp_setUniqueTypeTransform(buffer, value);
  }

  public Vec3 position {
    get => basicApp_uniqueTypeTransformPosition(buffer);
    set => basicApp_setUniqueTypeTransformPosition(buffer, value);
  }

  public Vec3 scale {
    get => basicApp_uniqueTypeTransformScale(buffer);
    set => basicApp_setUniqueTypeTransformScale(buffer, value);
  }

  public Vec3 rotation {
    get => basicApp_uniqueTypeTransformRotation(buffer);
    set => basicApp_setUniqueTypeTransformRotation(buffer, value);
  }
  //--------------------------------------------------



  //(SceneTransform)relativeTransform
  //--------------------------------------------------
  public SceneTransform relativeTransform {
    get => basicApp_uniqueTypeRelativeTransform(buffer);
    set => basicApp_setUniqueTypeRelativeTransform(buffer, value);
  }

  public Vec3 relativePosition {
    get => basicApp_uniqueTypeRelativeTransformPosition(buffer);
    set => basicApp_setUniqueTypeRelativeTransformPosition(buffer, value);
  }

  public Vec3 relativeScale {
    get => basicApp_uniqueTypeRelativeTransformScale(buffer);
    set => basicApp_setUniqueTypeRelativeTransformScale(buffer, value);
  }

  public Vec3 relativeRotation {
    get => basicApp_uniqueTypeRelativeTransformRotation(buffer);
    set => basicApp_setUniqueTypeRelativeTransformRotation(buffer, value);
  }
  //--------------------------------------------------



  //(UniqueType)parent
  //--------------------------------------------------
  public UniqueType parent {
    get => new UniqueType(basicApp_uniqueTypeParent(buffer));
    set => basicApp_setUniqueTypeParent(buffer, value.buffer);
  }
  //--------------------------------------------------



  //(PtrVector)children
  //--------------------------------------------------
  public PtrVector children { get; private set; }
  //--------------------------------------------------



  //(bool)active
  //--------------------------------------------------
  public bool active {
    get => basicApp_uniqueTypeActive(buffer);
    set => basicApp_setUniqueTypeActive(buffer, value);
  }
  //--------------------------------------------------





  public UniqueType(IntPtr ptr) : base(ptr) {
    children = new PtrVector(basicApp_uniqueTypeChildren(buffer));
  }
}