public partial class Program {
  static float DegToRadF = MathF.PI / 180.0f;

  static int Main() {
    if (basicApp_start("My Window") > 0)
      return 1;

    basicApp_loadModel("ball/Ball.fbx", false, "ball", false);

    Camera cam = new Camera(basicApp_createUniqueType(Unique.CAMERA));

    Object cube = new Object(basicApp_instantiateUniqueType("ball"));
    Object cube1 = new Object(basicApp_createUniqueType(Unique.OBJECT));
    Object cube2 = new Object(basicApp_createUniqueType(Unique.OBJECT));

    PointLight light = new PointLight(basicApp_createUniqueType(Unique.POINTLIGHT));
    light.position = new Vec3(3, 0, 0);
    light.color = new Vec4(10, 0, 0, 0);

    DirectionalLight dLight = new DirectionalLight(basicApp_createUniqueType(Unique.DIRECTIONALLIGHT));
    dLight.color = new Vec4(0, 0, 4, 0);
    dLight.direction = new Vec4(0.1f, -1, 0, 0);

    SpotLight sLight = new SpotLight(basicApp_createUniqueType(Unique.SPOTLIGHT));
    sLight.color = new Vec4(0, 5, 0, 0);
    sLight.innerCutoff = MathF.Cos(1.0f * DegToRadF);
    sLight.outerCutoff = MathF.Cos(45.0f * DegToRadF);
    sLight.direction = new Vec4(0, 0, -1, 0);
    sLight.parent = cam;
    sLight.followRotations = true;


    cube1.position = new Vec3(0, 0, -3);
    cube2.position = new Vec3(0, 0, -6);

    cube1.parent = cube;
    cube2.parent = cube;

    cube1.srcMaterial.metallic = 1;
    cube1.srcMaterial.roughness = 0;


    TextBox box = new TextBox(TextBox.basicApp_createTextBox());
    box.Text = "Hello, World";
    box.UpdateText();




    basicApp_setMouseHide(true);


    Array<float> meshVertices = new Array<float>(33, 4);
    MeshData mData = new MeshData(meshVertices, 3);
    Mesh.basicApp_loadMesh(mData.meshData, "myTriangle");

    Texture albedo = new Texture(Texture.basicApp_loadTexture("cube_diff.png", (int)TextureType.ALBEDO, false, false, false));
    cube2.srcMaterial.albedoTexture = albedo;
    cube2.srcMaterial.roughness = 1;
    cube2.srcMaterial.metallic = 0;


    while (!basicApp_shouldClose()) {
      basicApp_update();
      basicApp_mainCameraLook();
      basicApp_mainCameraMove();


      if (basicApp_keyPressed(KEY_ESCAPE))
        basicApp_closeApp();


      if (basicApp_keyHeld(KEY_KP_1))
        light.position = light.position - new Vec3(0, 0, 3 * basicApp_deltaTime());


      if (basicApp_keyPressed(KEY_Q))
        basicApp_swapMouseHide();

      if (basicApp_keyPressed(KEY_F))
        Console.WriteLine(basicApp_setObjectMesh(cube1.buffer, "myTriangle"));

      if (basicApp_keyPressed(KEY_E))
        meshVertices.CopyFrom(new float[33] {
          -0.5f, -0.5f, 0.0f,       0, 0, 1,        0, 0, 0,        0, 0,
          0.5f, -0.5f, 0.0f,        0, 0, 1,        0, 0, 0,        1, 0,
          0.0f, 0.5f, 0.0f,         0, 0, 1,        0, 0, 0,        1, 0
        });

      if (basicApp_keyPressed(KEY_R))
        mData.Update();

      if (basicApp_keyPressed(KEY_I))
        box.FontSize += 0.1f;

      if (basicApp_keyPressed(KEY_U))
        box.FontSize -= 0.1f;

      if (basicApp_keyPressed(KEY_N))
        box.LineSize -= 0.1f;
      if (basicApp_keyPressed(KEY_M))
        box.LineSize += 0.1f;

      


      if (basicApp_scrollDown()) {
        box.scale = new Vec3(box.scale.x + 0.1f, box.scale.y, box.scale.z);
        cube.rotation = new Vec3(cube.rotation.x + 1.0f, 0, 0);
      }

      if (basicApp_scrollUp()) {
        box.scale = new Vec3(box.scale.x - 0.1f, box.scale.y, box.scale.z);
        cube.rotation = new Vec3(cube.rotation.x - 1.0f, 0, 0);
      }

      if (basicApp_keyPressed(KEY_O))
        box.UpdateText();

      cam.UpdatePerspectiveView();


      if (basicApp_keyHeld(KEY_T))
        cube.position = new Vec3(0, 0, cube.position.z - 0.5f * basicApp_deltaTime());



      if (basicApp_keyPressed(KEY_H))
        if (cube.children.length > 1)
          cube2.parent = new(0);
        else if (cube.children.length > 0)
          cube1.parent = new(0);
        else {
          cube1.parent = cube;
          cube2.parent = cube;
        }

      if (basicApp_keyHeld(KEY_V))
        if (cube.children.length > 1) {
          UniqueType child = new(cube.children[1]);
          child.relativePosition = new Vec3(child.relativePosition.x + 0.5f * basicApp_deltaTime(), 0, child.relativePosition.z);
        } else if (cube.children.length > 0) {
          UniqueType child = new(cube.children[0]);
          child.relativePosition = new Vec3(child.relativePosition.x - 0.5f * basicApp_deltaTime(), 0, child.relativePosition.z);
        }

      basicApp_keyLatchKeys();
    }

    basicApp_end();

    return 0;
  }
}
