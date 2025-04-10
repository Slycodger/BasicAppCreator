#pragma once
#include "objScripts.h"
#include "typeDefs.h"
#include "vector.h"
#include <Set>
#include <string>
#include <Vector>
#include <limits>
#include "shapes.h"
#include "mathConstants.h"
#include <span>
#include "textureLoading.h"
#include "material.h"
#include "transform.h"
#include "camera.h"
#include "globalVars.h"

class Vertex {
public:
  Vec3 position;
  Vec3 normal;
  Vec3 tangent;
  Vec2 uv;

  Vertex() : position(0), normal(0), tangent(0), uv(0) {}
  Vertex(Vec3 Pos, Vec3 norm, Vec3 tan, Vec2 Uv) : position(Pos), normal(norm), tangent(tan), uv(Uv) {}
};

class Mesh {
public:
  std::span<Vertex> vertices;
  uint* VBO = nullptr;
  uint* triCount = nullptr;


  Mesh() : vertices(), VBO(nullptr), triCount(nullptr) {}
  Mesh(std::span<Vertex> verts) : vertices(verts), VBO(nullptr), triCount(nullptr) {}
  Mesh(std::span<Vertex> verts, uint* vbo, uint* tCount) : vertices(verts), VBO(vbo), triCount(tCount) {}
};


class MeshData {
public:
  uint* VBO;
  uint* triCount;
  Mesh* mesh;
};


void drawObj(UniqueType* tType);


class Object : public UniqueType {
public:
  std::vector<Object*> dependencies;
  Object* dependent = nullptr;
  Material* material = nullptr;
  Material srcMaterial = Material();
  Mesh* mesh = nullptr;
  std::string objType;
  uint index = 0;
  bool ui = false;

  //-------------------Constructor
  Object() : UniqueType(),
    ui(false), mesh(nullptr),
    material(nullptr), srcMaterial(),
    dependencies(), dependent(nullptr), index(0) {
    bool setObjMesh(UniqueType*, std::string);
    setObjMesh(this, "cube");
  }

  //-------------------Destructor
  ~Object() {}

  const Unique::Types getType() const override { return Unique::OBJECT; }

  UniqueType* copySelf() override {
    Object* ret = new Object();

    setToRelative();
    for (auto child : children)
      child->setToRelative();

    void addUniqueTypeScript(UniqueType* obj, void* script, char c);
    for (auto& scrV : scripts) {
      void* newScr = ((ScriptBase*)scrV)->getNew();
      addUniqueTypeScript(ret, newScr, 'c');
    }

    for (auto& child : children) {
      if (child->scriptCreated)
        continue;

      UniqueType* temp = nullptr;

      temp = child->copySelf();

      temp->setParent(ret);
    }

    ret->active = this->active;
    ret->node = this->node;
    ret->material = this->material;
    ret->srcMaterial = this->srcMaterial;

    if (!this->mesh)
      return ret;

    ret->mesh = this->mesh;

    return ret;
  }

  void update() override {
    drawObj(this);
  }


  //Dependent object stuff

  int getDependencyIndex(Object* obj) {
    for (int i = 0; i < dependencies.size(); i++)
      if (dependencies[i] == obj)
        return i;
    return -1;
  }

  void setDependent(Object* obj) {
    removeDependent();

    if (!obj)
      return;

    dependent = obj;
    obj->dependencies.push_back(this);
  }

  void removeDependent() {
    if (dependent == nullptr)
      return;
    int index = dependent->getChildIndex(this);
    if (index >= 0)
      dependent->dependencies.erase(dependent->dependencies.begin() + dependent->getDependencyIndex(this));
    dependent = nullptr;
  }



  //------------------------------Checking functions



  //---------------------------------Debugging stuff


  /*
  * TODO
  * Fix this
  */
  /*std::string hierarchyTree(int level = 0) {
      std::string ret = "";
      for (int i = 0; i < level; i++)
          ret += "---|";

      ret += (node ? "NODE" : objType) + '\n';

      if (!level)
          ret += '\n';

      for (auto child : children) {
          ret += child->hierarchyTree(level + 1);
      }

      return ret + (children.size() ? '\0' : '\n');
  }*/
};


void drawObjStencil(Object* tType);
void drawSkyMap();
bool unloadMesh(std::string name);
bool loadMesh(Mesh* mesh, std::string name);
void deleteObjMeshes();
void updateMeshBuffers(uint& VBO, const float* vertices, size_t vertSize);
void createMeshBuffers(uint& VBO, float* vertices, size_t vertSize);
void createMeshBuffers(uint& VBO, const float* vertices, size_t vertSize);
bool setObjMesh(UniqueType* tType, std::string mesh);
void setBufferSettings();
void setSkymapSwitch(bool active);
void toggleSkymap();
void setSkymapTexture(std::vector<std::string> textures, bool abs, bool gCorrection);
void drawUI();
void drawPostProcessing();
void generateIBL();


namespace nObjects {
  void start();
  void update();
  void end();
}