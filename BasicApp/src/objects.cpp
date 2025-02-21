#define _OBJECTS
#include "objects.h"
#include "uniqueTypes.h"
#include "light.h"
#include "graphicsSettings.h"
#include "basicApp.h"


unsigned int whiteSinglePixelTexture;
unsigned int graySinglePixelTexture;
unsigned int blackSinglePixelTexture;

unsigned char whiteSinglePixelData[4] = { 255, 255, 255, 255 };
unsigned char graySinglePixelData[4] = { 127, 127, 127, 255 };
unsigned char blackSinglePixelData[4] = { 0, 0, 0, 255 };

unsigned int squareVBO, squareTriCount;
unsigned int triangleVBO, triangleTriCount;
unsigned int cubeVBO, cubeTriCount;

unsigned int shaderMaterialUBO = 0;
unsigned int shaderPointLightUBO = 0;
unsigned int shaderDirectionalLightUBO = 0;
unsigned int shaderSpotLightUBO = 0;

unsigned int UIFBO, UITexture, UIDepth;
unsigned int postFBO, postTexture, postDepth;


Shader noLightingShader;
Shader lightingShader;
Shader cubeMapShader;
Shader minShader;
Shader UIShader;
Shader postProcessingShader;
Shader equirectangularCubemapShader;
Shader irradianceShader;
Shader prefilterShader;
Shader brdfShader;
uint VAO;

Texture* environmentMapTexture;
Texture* skyMapTexture;
Texture* irradianceMapTexture;
Texture* prefilterMapTexture;
Texture* brdfLUTTexture;
bool skyMapActive = true;


glm::mat4 transform;
Camera* mainCamera = nullptr;

std::map<std::string, Mesh*> objMeshes;

constexpr float identityMatrix[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

PointLight* PointLight::lights[_MAX_UNIQUE_TYPES] = {};
int PointLight::pointLightCount = 0;

DirectionalLight* DirectionalLight::lights[_MAX_UNIQUE_TYPES] = {};
int DirectionalLight::directionalLightCount = 0;

SpotLight* SpotLight::lights[_MAX_UNIQUE_TYPES] = {};
int SpotLight::spotLightCount = 0;




//--------------------------------------------------
bool basicApp_setObjectMesh(UniqueType* ptr, const char* mesh) {
  return setObjMesh(ptr, mesh);
}



//--------------------------------------------------
bool basicApp_loadMesh(MeshData* mesh, const char* name) {
  return loadMesh(mesh->mesh, name);
}



//--------------------------------------------------
bool basicApp_unloadMesh(const char* name) {
  return unloadMesh(name);
}



//--------------------------------------------------
void basicApp_updateMeshBuffersWithNew(MeshData* mData, float* vertices, uint64_t vertSize, uint64_t triCount) {
  if (!mData)
    return;

  mData->mesh->vertices = { reinterpret_cast<Vertex*>(vertices), vertSize / sizeof(float) };
  *mData->triCount = triCount;

  glBindBuffer(GL_ARRAY_BUFFER, *mData->VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



//--------------------------------------------------
void basicApp_updateMeshBuffers(MeshData* mData) {
  if (!mData)
    return;

  glBindBuffer(GL_ARRAY_BUFFER, *mData->VBO);
  glBufferData(GL_ARRAY_BUFFER, mData->mesh->vertices.size() * sizeof(Vertex), mData->mesh->vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



//--------------------------------------------------
void* basicApp_createMeshBuffers(float* vertices, int64_t vertSize, uint triCount) {
  MeshData* mData = new MeshData();
  mData->VBO = new uint(0);
  mData->triCount = new uint(triCount);
  mData->mesh = new Mesh({ reinterpret_cast<Vertex*>(vertices), vertSize / sizeof(float)}, mData->VBO, mData->triCount);

  glCreateBuffers(1, mData->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, *mData->VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return mData;
}



//--------------------------------------------------
void basicApp_deleteMeshData(MeshData* mData) {
  delete(mData->VBO);
  delete(mData->triCount);
  delete(mData);
}






namespace nObjects {
  void start() {
    glGenVertexArrays(1, &VAO);

    createMeshBuffers(triangleVBO, triangleVertices, triangleVerticeSize);
    triangleTriCount = 1;
    loadMesh(new Mesh({ reinterpret_cast<Vertex*>(triangleVertices), triangleVerticeSize / sizeof(float) },
      &triangleVBO, &triangleTriCount), "triangle");


    createMeshBuffers(squareVBO, squareVertices, squareVerticeSize);
    squareTriCount = 2;
    loadMesh(new Mesh({ reinterpret_cast<Vertex*>(squareVertices), squareVerticeSize / sizeof(float) },
      &squareVBO, &squareTriCount), "square");


    createMeshBuffers(cubeVBO, cubeVertices, cubeVerticeSize);
    cubeTriCount = 12;
    loadMesh(new Mesh({ reinterpret_cast<Vertex*>(cubeVertices), cubeVerticeSize / sizeof(float) },
      &cubeVBO, &cubeTriCount), "cube");




    glGenTextures(1, &whiteSinglePixelTexture);
    glBindTexture(GL_TEXTURE_2D, whiteSinglePixelTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteSinglePixelData);

    glGenTextures(1, &graySinglePixelTexture);
    glBindTexture(GL_TEXTURE_2D, graySinglePixelTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, graySinglePixelData);

    glGenTextures(1, &blackSinglePixelTexture);
    glBindTexture(GL_TEXTURE_2D, blackSinglePixelTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackSinglePixelData);

    glBindTexture(GL_TEXTURE_2D, 0);

    shaderMaterial tMat = shaderMaterial();

    glGenBuffers(1, &shaderMaterialUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderMaterialUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(shaderMaterial), &tMat, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, shaderMaterialUBO);


    PointLightContainer tPointLight;
    DirectionalLightContainer tDirectionalLight;
    SpotLightContainer tSpotLight;

    glGenBuffers(1, &shaderPointLightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderPointLightUBO);
    glBufferData(GL_UNIFORM_BUFFER,  sizeof(PointLightContainer), &tPointLight, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, shaderPointLightUBO);

    glGenBuffers(1, &shaderDirectionalLightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderDirectionalLightUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(DirectionalLightContainer), &tDirectionalLight, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, shaderDirectionalLightUBO);

    glGenBuffers(1, &shaderSpotLightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderSpotLightUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(SpotLightContainer), &tSpotLight, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, shaderSpotLightUBO);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);


    noLightingShader.ID = getShader("noLightingShader");
    lightingShader.ID = getShader("lightingShader");
    minShader.ID = getShader("minShader");
    cubeMapShader.ID = getShader("cubeMapShader");
    UIShader.ID = getShader("UIShader");
    postProcessingShader.ID = getShader("postProcessingShader");
    equirectangularCubemapShader.ID = getShader("equirectangularCubemapShader");
    irradianceShader.ID = getShader("irradianceShader");
    prefilterShader.ID = getShader("prefilterShader");
    brdfShader.ID = getShader("brdfShader");
    


    glGenFramebuffers(1, &UIFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, UIFBO);

    glGenTextures(1, &UITexture);
    glBindTexture(GL_TEXTURE_2D, UITexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _screenWidth, _screenHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, UITexture, 0);

    glGenTextures(1, &UIDepth);
    glBindTexture(GL_TEXTURE_2D, UIDepth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _screenWidth, _screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, UIDepth, 0);


    glGenFramebuffers(1, &postFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);

    glGenTextures(1, &postTexture);
    glBindTexture(GL_TEXTURE_2D, postTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _screenWidth, _screenHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, postTexture, 0);

    glGenTextures(1, &postDepth);
    glBindTexture(GL_TEXTURE_2D, postDepth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _screenWidth, _screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, postDepth, 0);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);


    loadEnvironmentTexture("buildings.hdr", &environmentMapTexture, false, true);
    generateIBL();
  }

  void update() {

  }

  void end() {
    unloadMesh("square");
    unloadMesh("triangle");
    unloadMesh("cube");
    glDeleteBuffers(1, &squareVBO);
    glDeleteBuffers(1, &triangleVBO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteTextures(1, &whiteSinglePixelTexture);
    glDeleteTextures(1, &graySinglePixelTexture);
    glDeleteTextures(1, &blackSinglePixelTexture);
    deleteObjMeshes();

    unsigned int UIFBO, UITexture, UIDepth;
    unsigned int postFBO, postTexture, postDepth;

    glDeleteTextures(1, &UITexture);
    glDeleteTextures(1, &UIDepth);
    glDeleteTextures(1, &postTexture);
    glDeleteTextures(1, &postDepth);
    glDeleteFramebuffers(1, &UIFBO);
    glDeleteFramebuffers(1, &postFBO);
  }
}



//Creates the buffers for an object
void createMeshBuffers(uint& VBO, float* vertices, size_t vertSize) {
  glCreateBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//Exact same as createMeshBuffers, except doesn't generate VBO
void updateMeshBuffers(uint& VBO, const float* vertices, size_t vertSize) {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//Creates the buffers for an object
void createMeshBuffers(uint& VBO, const float* vertices, size_t vertSize) {
  glCreateBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Loads an object into a map
bool loadMesh(Mesh* mesh, std::string name) {
  return objMeshes.insert({ name, mesh }).second;
}

//Removes a specific object type from the map
bool unloadMesh(std::string name) {
  if (!objMeshes.contains(name))
    return false;

  delete (objMeshes[name]);
  objMeshes.erase(name);
  return true;
}

//Deletes all object types
void deleteObjMeshes() {
  for (auto& mesh : objMeshes) {
    delete (mesh.second);
  }

  objMeshes.clear();
}


bool setObjMesh(UniqueType* tType, std::string mesh) {
  if (tType->getType() != Unique::OBJECT || !objMeshes.count(mesh))
    return false;

  Object* obj = (Object*)tType;

  Mesh*& meshData = objMeshes.at(mesh);
  obj->mesh = meshData;
  obj->objType = mesh;
  return true;
}


void setSkymapSwitch(bool active) {
  skyMapActive = active;
}

void toggleSkymap() {
  skyMapActive = !skyMapActive;
}

void setSkymapTexture(std::vector<std::string> textures, bool abs, bool gCorrection) {
  removeTexture("skyMap");

  Texture* tTexture = nullptr;

  if (loadCubeMapTexture("skyMap", textures, &tTexture, Texture::ALBEDO, abs, false, gCorrection)) {
    skyMapTexture = tTexture;
    return;
  }
}


void drawPostProcessing() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  postProcessingShader.active();
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
  setBufferSettings();
  Shader::setInt("texTarget", 0);
  Shader::setFloat("gamma", graphicsSettings::gamma);
  Shader::setFloat("exposure", graphicsSettings::exposure);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, postTexture);
  glDrawArrays(GL_TRIANGLES, 0, squareTriCount * 3);
}


void drawUI() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);
  UIShader.active();
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
  setBufferSettings();
  Shader::setInt("texTarget", 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, UITexture);
  glDrawArrays(GL_TRIANGLES, 0, squareTriCount * 3);
  glEnable(GL_DEPTH_TEST);
}


//Sets the vertex attributes
void setBufferSettings() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
  glEnableVertexAttribArray(3);
}


void applyPointLights(Object* obj) {
  int selectedLightCount = 0;
  int closetLights[_MAX_ACTING_POINT_LIGHTS] = { 0 };
  if (PointLight::pointLightCount > _MAX_ACTING_POINT_LIGHTS) {
    for (int i = 0; i < PointLight::pointLightCount; i++) {
      if (selectedLightCount >= _MAX_ACTING_POINT_LIGHTS) {
        for (int j = 0; j < _MAX_ACTING_POINT_LIGHTS; j++) {
          if ((PointLight::lights[i]->transform.position - obj->transform.position).magnitude() <
            (PointLight::lights[closetLights[j]]->transform.position - obj->transform.position).magnitude())
            closetLights[j] = i;
        }
        continue;
      }

      closetLights[selectedLightCount] = i;
      selectedLightCount++;
    }
  } else {
    selectedLightCount = PointLight::pointLightCount;
    for (int i = 0; i < PointLight::pointLightCount; i++)
      closetLights[i] = i;
  }

  PointLightContainer container;
  
  for (int i = 0; i < selectedLightCount; i++)
    container.lights[i] = PointLight::lights[closetLights[i]]->activeLight;

  glBindBuffer(GL_UNIFORM_BUFFER, shaderPointLightUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PointLightContainer), &container);
  Shader::setInt("pointLightCount", selectedLightCount);
}


void applyDirectionalLights(Object* obj) {
  int selectedLightCount = 0;
  int closetLights[_MAX_ACTING_DIRECTIONAL_LIGHTS] = { 0 };
  if (DirectionalLight::directionalLightCount > _MAX_ACTING_DIRECTIONAL_LIGHTS) {
    for (int i = 0; i < DirectionalLight::directionalLightCount; i++) {
      if (selectedLightCount >= _MAX_ACTING_DIRECTIONAL_LIGHTS) {
        for (int j = 0; j < _MAX_ACTING_DIRECTIONAL_LIGHTS; j++) {
          if ((DirectionalLight::lights[i]->transform.position - obj->transform.position).magnitude() <
            (DirectionalLight::lights[closetLights[j]]->transform.position - obj->transform.position).magnitude())
            closetLights[j] = i;
        }
        continue;
      }

      closetLights[selectedLightCount] = i;
      selectedLightCount++;
    }
  } else {
    selectedLightCount = DirectionalLight::directionalLightCount;
    for (int i = 0; i < DirectionalLight::directionalLightCount; i++)
      closetLights[i] = i;
  }

  DirectionalLightContainer container;

  for (int i = 0; i < selectedLightCount; i++)
    container.lights[i] = DirectionalLight::lights[closetLights[i]]->activeLight;

  glBindBuffer(GL_UNIFORM_BUFFER, shaderDirectionalLightUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(DirectionalLightContainer), &container);
  Shader::setInt("directionalLightCount", selectedLightCount);
}


void applySpotLights(Object* obj) {
  int selectedLightCount = 0;
  int closetLights[_MAX_ACTING_SPOT_LIGHTS] = { 0 };
  if (SpotLight::spotLightCount > _MAX_ACTING_SPOT_LIGHTS) {
    for (int i = 0; i < SpotLight::spotLightCount; i++) {
      if (selectedLightCount >= _MAX_ACTING_SPOT_LIGHTS) {
        for (int j = 0; j < _MAX_ACTING_SPOT_LIGHTS; j++) {
          if ((SpotLight::lights[i]->transform.position - obj->transform.position).magnitude() <
            (SpotLight::lights[closetLights[j]]->transform.position - obj->transform.position).magnitude())
            closetLights[j] = i;
        }
        continue;
      }

      closetLights[selectedLightCount] = i;
      selectedLightCount++;
    }
  } else {
    selectedLightCount = SpotLight::spotLightCount;
    for (int i = 0; i < SpotLight::spotLightCount; i++)
      closetLights[i] = i;
  }

  SpotLightContainer container;

  for (int i = 0; i < selectedLightCount; i++)
    container.lights[i] = SpotLight::lights[closetLights[i]]->activeLight;

  glBindBuffer(GL_UNIFORM_BUFFER, shaderSpotLightUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(SpotLightContainer), &container);
  Shader::setInt("spotLightCount", selectedLightCount);
}



void drawObj(UniqueType* tType) {
  glBindVertexArray(VAO);

  if (tType->getType() != Unique::OBJECT)
    return;
  Object* obj = (Object*)tType;
  if (!obj->mesh)
    return;

  if (!obj->chainActive())
    return;


  transform = glm::mat4(1);
  mainCamera = Camera::getCurrentCamera();

  if (!mainCamera)
    return;


  if (!obj->ui) {
    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
    lightingShader.active();
    Shader::setMat4("projection", mainCamera->perspectiveView);
    Shader::setMat4("view", mainCamera->viewMatrix);

    Shader::setVec3("cameraPos", Vec3(mainCamera->transform.position.x, mainCamera->transform.position.y, mainCamera->transform.position.z));


    Shader::setInt("irradianceMap", 5);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMapTexture->texture);
    Shader::setInt("prefilterMap", 6);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMapTexture->texture);
    Shader::setInt("brdfLUT", 7);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture->texture);

    applyPointLights(obj);
    applyDirectionalLights(obj);
    applySpotLights(obj);


    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  } else {
    glBindFramebuffer(GL_FRAMEBUFFER, UIFBO);
    noLightingShader.active();
    Shader::setMat4("projection", mainCamera->orthographicView);
    Shader::setMat4("view", identityMatrix);
  }



  if (obj->dependent != nullptr) {
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_EQUAL, 0x01, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDisable(GL_DEPTH_TEST);
    glColorMask(0, 0, 0, 0);

    drawObjStencil(obj);

    glEnable(GL_DEPTH_TEST);
    glColorMask(1, 1, 1, 1);
  } else
    glDisable(GL_STENCIL_TEST);

  transform = createUniqueTypeTransformMatrix(obj);

  glBindBuffer(GL_UNIFORM_BUFFER, shaderMaterialUBO);

  if (obj->material)
    obj->material->apply();
  else
    obj->srcMaterial.apply();


  Shader::setMat4("transform", transform);


  glBindBuffer(GL_ARRAY_BUFFER, *obj->mesh->VBO);

  setBufferSettings();

  glDrawArrays(GL_TRIANGLES, 0, *obj->mesh->triCount * 3);
}




void drawObjStencil(Object* obj) {
  glStencilFunc(GL_ALWAYS, 0x01, 0xFF);
  glStencilOp(GL_INCR, GL_INCR, GL_INCR);
  glDisable(GL_DEPTH_TEST);
  glColorMask(0, 0, 0, 0);
  glBindVertexArray(VAO);


  minShader.active();
  Shader::setMat4("transform", transform);
  if (!obj->ui) {
    Shader::setMat4("view", mainCamera->viewMatrix);
    Shader::setMat4("projection", mainCamera->perspectiveView);
  } else {
    Shader::setMat4("projection", mainCamera->orthographicView);
    Shader::setMat4("view", identityMatrix);
  }

  glBindBuffer(GL_ARRAY_BUFFER, *obj->mesh->VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glDrawArrays(GL_TRIANGLES, 0, *obj->mesh->triCount * 3);


}

void drawCube() {
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

  setBufferSettings();

  glDrawArrays(GL_TRIANGLES, 0, cubeTriCount * 3);
}

void drawQuad() {
  glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

  setBufferSettings();

  glDrawArrays(GL_TRIANGLES, 0, squareTriCount * 3);
}



void generateIBL() {
  if (!environmentMapTexture || !environmentMapTexture->texture)
    return;
  unsigned int captureFBO, captureRBO;

  glGenFramebuffers(1, &captureFBO);
  glGenRenderbuffers(1, &captureRBO);


  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1024, 1024);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

  if (skyMapTexture)
    glDeleteTextures(1, &skyMapTexture->texture);
  else
    skyMapTexture = new Texture(0, 1024, 1024, Texture::ALBEDO);

  includeTexture("skyMapTexture", skyMapTexture);

  glGenTextures(1, &skyMapTexture->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture->texture);

  for (int i = 0; i < 6; i++)
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 1024, 1024, 0, GL_RGB, GL_FLOAT, nullptr);


  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
  glm::mat4 captureViews[] = {
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
     glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
  };

  // convert HDR equirectangular environment map to cubemap equivalent
  equirectangularCubemapShader.active();
  Shader::setInt("equirectangularMap", 0);
  Shader::setMat4("projection", captureProjection);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, environmentMapTexture->texture);

  glViewport(0, 0, 1024, 1024); // don't forget to configure the viewport to the capture dimensions.
  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  glClearColor(0, 0, 0, 0);
  for (unsigned int i = 0; i < 6; i++) {
    Shader::setMat4("view", captureViews[i]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, skyMapTexture->texture, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCube(); // renders a 1x1 cube
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 5);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture->texture);
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


  //-----------------------------------------------------------------------------------------------------------------
  //Irradiance map
  if (irradianceMapTexture)
    glDeleteTextures(1, &irradianceMapTexture->texture);
  else
    irradianceMapTexture = new Texture(0, 32, 32, Texture::ALBEDO);

  includeTexture("irradianceMapTexture", irradianceMapTexture);


  glGenTextures(1, &irradianceMapTexture->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMapTexture->texture);
  for (int i = 0; i < 6; i++) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0,
      GL_RGB, GL_FLOAT, nullptr);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

  irradianceShader.active();
  Shader::setInt("environmentMap", 0);
  Shader::setMat4("projection", captureProjection);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture->texture);

  glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  for (int i = 0; i < 6; i++) {
    Shader::setMat4("view", captureViews[i]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMapTexture->texture, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCube();
  }






  //------------------------------------------------------------------------------------------------
  //Prefilter
  if (prefilterMapTexture)
    glDeleteTextures(1, &prefilterMapTexture->texture);
  else
    prefilterMapTexture = new Texture(0, 128, 128, Texture::ALBEDO);

  includeTexture("prefilterMapTexture", prefilterMapTexture);


  glGenTextures(1, &prefilterMapTexture->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMapTexture->texture);
  for (unsigned int i = 0; i < 6; ++i) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



  prefilterShader.active();
  Shader::setInt("environmentMap", 0);
  Shader::setMat4("projection", captureProjection);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture->texture);

  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  unsigned int maxMipLevels = 5;
  for (unsigned int mip = 0; mip < maxMipLevels; mip++) {
    // reisze framebuffer according to mip-level size.
    unsigned int mipWidth = 512 * std::pow(0.5, mip);
    unsigned int mipHeight = 512 * std::pow(0.5, mip);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
    glViewport(0, 0, mipWidth, mipHeight);

    float roughness = (float)mip / (float)(maxMipLevels - 1);
    prefilterShader.setFloat("roughness", roughness);
    for (unsigned int i = 0; i < 6; ++i) {
      prefilterShader.setMat4("view", captureViews[i]);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMapTexture->texture, mip);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      drawCube();
    }
  }
  glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMapTexture->texture);
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);



  //------------------------------------------------------------------------------------------------------
  //BRDF

  if (brdfLUTTexture)
    glDeleteTextures(1, &brdfLUTTexture->texture);
  else
    brdfLUTTexture = new Texture(0, 512, 512, Texture::ALBEDO);

  includeTexture("brdfLUTTexture", brdfLUTTexture);

  glGenTextures(1, &brdfLUTTexture->texture);

  // pre-allocate enough memory for the LUT texture.
  glBindTexture(GL_TEXTURE_2D, brdfLUTTexture->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
  glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture->texture, 0);

  glViewport(0, 0, 512, 512);
  brdfShader.active();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawQuad();


  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &captureFBO);
  glDeleteRenderbuffers(1, &captureRBO);
  glViewport(0, 0, _screenWidth, _screenHeight);
}


void drawSkyMap() {
  if (skyMapActive && skyMapTexture) {
    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    mainCamera = Camera::getCurrentCamera();
    if (!mainCamera)
      return;

    cubeMapShader.active();
    Shader::setMat4("projection", mainCamera->perspectiveView);
    Shader::setMat4("view", glm::value_ptr(glm::mat4(glm::mat3(mainCamera->viewMatrix))));
    Shader::setInt("texTarget", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture->texture);

    drawCube();

    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
  }
}