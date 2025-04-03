#pragma once
#include "objScripts.h"
#include "vector.h"
#include <Vector>
#include "Unique.h"

class Transform {
public:
  Vec3 position = 0;
  Vec3 scale = 1;
  Vec3 rotation = 0;

  Transform() : position(0), scale(1), rotation(0) {}
};

class UniqueType {
public:
  Transform transform;
  Transform relativeTransform;
  UniqueType* parent = nullptr;
  std::vector<UniqueType*> children;
  std::vector<void*> scripts;
  bool node = true;
  bool scriptCreated = false;
  int index = -1;
  bool active = true;

  virtual const Unique::Types getType() const { return Unique::INVALID; }
  virtual UniqueType* copySelf() { return this; }
  virtual void update() {}
  virtual void end() {}

  int getChildIndex(UniqueType* child) {
    for (int i = 0; i < children.size(); i++)
      if (children[i] == child)
        return i;
    return -1;
  }
  void setParent(UniqueType* nParent) {
    removeParent();

    if (!nParent)
      return;

    nParent->children.push_back(this);
    parent = nParent;
    relativeTransform.position = (transform.position - parent->transform.position) / parent->transform.scale;
    relativeTransform.scale = transform.scale / parent->transform.scale;
    relativeTransform.rotation = transform.rotation - parent->transform.rotation;
  }
  void setToRelative() {
    if (parent == nullptr)
      return;

    glm::mat4 Translation(1);
    if (node) {
      Translation = glm::rotate(Translation, glm::radians<float>(relativeTransform.rotation.z + parent->transform.rotation.z), glm::vec3(0, 0, 1));
      Translation = glm::rotate(Translation, glm::radians<float>(relativeTransform.rotation.y + parent->transform.rotation.y), glm::vec3(0, 1, 0));
      Translation = glm::rotate(Translation, glm::radians<float>(relativeTransform.rotation.x + parent->transform.rotation.x), glm::vec3(1, 0, 0));
    }
    Translation = glm::translate(Translation, (relativeTransform.position * parent->transform.scale).toGLM());

    transform.position = Translation * glm::vec4(0, 0, 0, 1);
    transform.position += parent->transform.position;
    transform.rotation = parent->transform.rotation;
    transform.scale = parent->transform.scale * relativeTransform.scale;
  }
  void removeParent() {
    if (parent == nullptr)
      return;
    int index = parent->getChildIndex(this);
    if (index >= 0)
      parent->children.erase(parent->children.begin() + index);


    parent = nullptr;
  }
  void* getScriptType(std::string scriptType) {
    for (auto scrV : scripts) {
      scriptBase* scr = (scriptBase*)scrV;
      if (scr->getName() == scriptType)
        return (void*)scrV;
    }
  }

  bool chainActive() {
    if (!active)
      return false;
    if (parent == nullptr)
      return true;
    if (!parent->active)
      return false;
    return parent->chainActive();
  }


  UniqueType() : transform(), relativeTransform(), parent(nullptr), children(0), node(true), scriptCreated(false), active(true), index(-1), scripts() {}
};