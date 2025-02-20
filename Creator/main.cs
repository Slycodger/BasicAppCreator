public partial class Program {
  static int Main() {
    if (basicApp_start("My Window") > 0)
      return 1;

    Object cube = new Object(basicApp_createUniqueType(Unique.OBJECT));
    Object cube1 = new Object(basicApp_createUniqueType(Unique.OBJECT));
    Object cube2 = new Object(basicApp_createUniqueType(Unique.OBJECT));
    SceneTransform newTransform = new SceneTransform();
    newTransform.position = new Vec3(3.0f, 1.0f, -5.0f);
    newTransform.scale = new Vec3(2.0f, 1.0f, 0.5f);

    cube1.position = new Vec3(0, 0, -3);
    cube2.position = new Vec3(0, 0, -6);

    cube1.parent = cube;
    cube2.parent = cube;

    cube.srcMaterial.roughness = 1;
    cube1.srcMaterial.metallic = 1;
    cube2.srcMaterial.albedo = new Vec4(1, 0, 0, 1);
    cube2.srcMaterial.roughness = 0.75f;

    Console.WriteLine(cube2.mesh.triCount);
    Console.WriteLine($"Vertex 7 on {nameof(cube2)} has uv {cube2.mesh.vertices[7].uv}");

    basicApp_createUniqueType(Unique.CAMERA);
    basicApp_setMouseHide(true);

    PtrVector cubeChildren = cube.children;



    while (!basicApp_shouldClose()) {
      basicApp_update();
      basicApp_mainCameraLook();
      basicApp_mainCameraMove();



      if (basicApp_keyPressed(KEY_ESCAPE))
        basicApp_closeApp();



      if (basicApp_keyPressed(KEY_Q))
        basicApp_swapMouseHide();



      if (basicApp_keyPressed(KEY_F))
        cube.transform = newTransform;



      if (basicApp_keyHeld(KEY_T))
        cube.position = new Vec3(0, 0, cube.position.z - 0.5f * basicApp_deltaTime());



      if (basicApp_keyPressed(KEY_H))
        if (cubeChildren.length > 1)
          cubeChildren.Remove(1);
        else if (cubeChildren.length > 0)
          cube1.parent = new(0);
        else {
          cube1.parent = cube;
          cube2.parent = cube;
        }


      if (basicApp_keyHeld(KEY_N))
        if (cubeChildren.length > 1) {
          UniqueType child = new(cubeChildren[1]);
          child.relativePosition = new Vec3(child.relativePosition.x + 0.5f * basicApp_deltaTime(), 0, child.relativePosition.z);
        } else if (cubeChildren.length > 0) {
          UniqueType child = new(cubeChildren[0]);
          child.relativePosition = new Vec3(child.relativePosition.x - 0.5f * basicApp_deltaTime(), 0, child.relativePosition.z);
        }

      basicApp_keyLatchKeys();
    }

    basicApp_end();

    return 0;
  }
}
