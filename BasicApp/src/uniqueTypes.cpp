#define _UNIQUE_TYPES
#include "UniqueTypes.h"
#include "basicApp.h"


//App globals
//--------------------------------------------------
bool _showUI = true;
//--------------------------------------------------



//Local globals
//--------------------------------------------------
static std::map<std::string, UniqueType*> savedUniques;

uint uniqueCount = 0;
UniqueType* globalUniqueTypes[_MAX_UNIQUE_TYPES];

static glm::mat4 _transform(1);
//--------------------------------------------------





//--------------------------------------------------
void* basicApp_createUniqueType(Unique::Types type) {
  return createUniqueType(type);
}







namespace nUniqueTypes {
  //Creates default objects
  void start() {
    for (uint i = 0; i < _MAX_UNIQUE_TYPES; i++) {
      globalUniqueTypes[i] = nullptr;
    }

  }

  //Deletes at the end
  void end() {
    for (auto savedObj : savedUniques) {
      deleteUniqueType(savedObj.second, 'c');
    }
    savedUniques.clear();
  }
}


//---------------------OBJECT----HANDLING


bool saveUniqueType(UniqueType* tType, std::string objName) {
  if (!tType || savedUniques.count(objName))
    return false;

  UniqueType* typeCopy = tType->copySelf();

  return savedUniques.insert(std::pair<std::string, UniqueType*>{objName, typeCopy}).second;
}

UniqueType* instantiateUniqueType(std::string objName) {
  if (!savedUniques.count(objName))
    return nullptr;

  UniqueType* ret = nullptr;
  ret = savedUniques.at(objName)->copySelf();
  addGlobalUniqueType(ret);
  startUniqueType(ret);

  return ret;
}



//Create an object with a mesh
UniqueType* createUniqueType(Unique::Types type) {
  UniqueType* ret = nullptr;

  switch (type) {
  case Unique::INVALID:
    return nullptr;
    break;
  case Unique::UNIQUE :
    ret = new UniqueType();
    break;
  case Unique::OBJECT:
    ret = new Object();
    break;
  case Unique::CAMERA:
    ret = new Camera(70, 0.001f, 100.f, _screenRatio, _screenRatio, 1, 1);
    break;
  case Unique::POINTLIGHT:
    ret = new PointLight({ 0 }, { 1 });
    break;
  case Unique::DIRECTIONALLIGHT:
    ret = new DirectionalLight();
    break;
  case Unique::SPOTLIGHT:
    ret = new SpotLight();
    break;
  }


  if (!addGlobalUniqueType(ret)) {
    delete(ret);
    return nullptr;
  }

  return ret;
}


//Create an object without adding it to the global context
UniqueType* createUniqueType(Unique::Types type, char) {
  UniqueType* ret = nullptr;

  switch (type) {
  case Unique::INVALID:
    return nullptr;
    break;
  case Unique::OBJECT:
    ret = new Object();
    break;
  case Unique::CAMERA:
    ret = new Camera(70, 0.001f, 100.f, _screenRatio, 1.f, 1, 1);
    break;
  case Unique::POINTLIGHT:
    ret = new PointLight();
    break;
  case Unique::SPOTLIGHT:
    ret = new SpotLight();
    break;
  }


  return ret;
}


//Finds the first open slot in 'globalObjects'
uint findUniqueSlot() {
  for (uint i = 0; i < _MAX_UNIQUE_TYPES; i++) {
    if (globalUniqueTypes[i] == nullptr)
      return i;
  }
  return _MAX_UNIQUE_TYPES;
}

//Returns if it is able to add an object to 'globalObjects'
bool addGlobalUniqueType(UniqueType*& tType) {
  if (tType->index > -1) {
    for (auto child : tType->children) {
      addGlobalUniqueType(child);
    }
    return false;
  }

  uint objSlot = findUniqueSlot();
  if (objSlot == _MAX_UNIQUE_TYPES)
    return false;

  globalUniqueTypes[objSlot] = tType;
  globalUniqueTypes[objSlot]->index = objSlot;

  for (auto child : tType->children) {
    addGlobalUniqueType(child);
  }

  uniqueCount++;
  return true;
}

//Deletes all objects
void deleteAll() {
  for (uint i = 0; i < _MAX_UNIQUE_TYPES; i++) {
    if (globalUniqueTypes[i] == nullptr || globalUniqueTypes[i]->parent != nullptr)
      continue;
    clearUniqueTypeScripts(globalUniqueTypes[i]);
    clearUniqueTypeChildren(globalUniqueTypes[i]);
    delete(globalUniqueTypes[i]);
    globalUniqueTypes[i] = nullptr;
  }
  uniqueCount = 0;
}

//Deletes an object without removing from global objects, meant for objects that are self-contained elsewhere
void deleteUniqueType(UniqueType* tType, const char) {
  if (tType == nullptr)
    return;
  clearUniqueTypeScripts(tType);
  for (UniqueType* child : tType->children)
    deleteUniqueType(child, 'c');

  delete(tType);
  tType = nullptr;
}

//Deletes an object
void deleteUniqueType(UniqueType* tType) {
  if (tType == nullptr)
    return;
  uint index = tType->index;
  clearUniqueTypeScripts(tType);
  clearUniqueTypeChildren(tType);
  tType->removeParent();

  delete(tType);
  if (index > -1) {
    globalUniqueTypes[index] = nullptr;
    uniqueCount--;
  }
  tType = nullptr;
}

//Deletes an object without updating the parent
void deleteUniqueType(UniqueType* tType, int) {
  if (tType == nullptr)
    return;
  uint index = tType->index;
  clearUniqueTypeScripts(tType);
  clearUniqueTypeChildren(tType);

  delete(tType);
  if (index > -1) {
    globalUniqueTypes[index] = nullptr;
    uniqueCount--;
  }
  tType = nullptr;
}


//--------------------FOR-OBJECTS

//Starts an objects scripts
void startUniqueType(UniqueType* obj) {
  for (auto scr : obj->scripts) {
    if (!((scriptBase*)scr)->started) {
      createScriptUniqueTypes(((scriptBase*)scr)->objsNeeded());
      ((scriptBase*)scr)->start();
    }
  }
  for (auto child : obj->children) {
    startUniqueType(child);
  }
}

//Creates the objects needed for a script
void createScriptUniqueTypes(std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> pair) {
  for (auto typeOf : pair.first) {
    pair.second.push_back(createUniqueType(typeOf.first));
    if (typeOf.first == Unique::OBJECT)
      setObjMesh((UniqueType*)pair.second[pair.second.size() - 1], typeOf.second);
    ((UniqueType*)pair.second[pair.second.size() - 1])->scriptCreated = true;
  }
}

//Adds an object script
void addUniqueTypeScript(UniqueType* tType, void* script) {
  tType->scripts.push_back(script);
  scriptBase* realScr = (scriptBase*)script;
  createScriptUniqueTypes(realScr->objsNeeded());
  realScr->vThisObj = tType;
  realScr->start();
}

//Add an object script without starting it
void addUniqueTypeScript(UniqueType* tType, void* script, char c) {
  tType->scripts.push_back(script);
  scriptBase* realScr = (scriptBase*)script;
  realScr->vThisObj = tType;
}

//Remove an object script at a specific index
void removeUniqueTypeScript(UniqueType* tType, unsigned int index) {
  ((scriptBase*)(tType->scripts[index]))->end();
  delete(tType->scripts[index]);
  tType->scripts.erase(tType->scripts.begin() + index);
}

//Get the index of a script on an object with a certain name
unsigned int getUniqueTypeScriptIndex(UniqueType* tType, std::string name) {
  for (uint i = 0; i < tType->scripts.size(); i++) {
    scriptBase* realScr = (scriptBase*)tType->scripts[i];
    if (realScr->getName() == name) {
      return i;
    }
  }
  return UINT_MAX;
}


//Updates an objects scripts
void updateUniqueTypeScripts(UniqueType* tType) {
  for (uint i = 0; i < tType->scripts.size(); i++) {
    scriptBase* realScr = (scriptBase*)tType->scripts[i];
    realScr->update();
  }
}

//Deletes an objects scripts
void clearUniqueTypeScripts(UniqueType* tType) {
  for (uint i = 0; i < tType->scripts.size(); i++) {
    ((scriptBase*)tType->scripts[i])->end();
    delete(tType->scripts[i]);
  }
  tType->scripts.clear();
}

//Deletes an objects children
void clearUniqueTypeChildren(UniqueType* tType) {
  if (tType->children.size() == 0)
    return;
  for (UniqueType*& child : tType->children) {
    deleteUniqueType(child, 0);
  }
  tType->children.clear();
}

//Updates an objects children
void updateUniqueTypeChildren(UniqueType* tType) {
  if (tType->children.size() == 0)
    return;
  for (UniqueType* child : tType->children) {
    child->setToRelative();
    updateUniqueTypeChildren(child);
  }
}

//Creates the transformation matrix for an object
glm::mat4 createUniqueTypeTransformMatrix(UniqueType* obj) {

  glm::mat4 ret = glm::mat4(1);
  ret = glm::translate(ret, obj->transform.position.toGLM());
  ret = glm::rotate(ret, (float)_degToRad * obj->transform.rotation.x, glm::vec3(1, 0, 0));
  ret = glm::rotate(ret, (float)_degToRad * obj->transform.rotation.y, glm::vec3(0, 1, 0));
  ret = glm::rotate(ret, (float)_degToRad * obj->transform.rotation.z, glm::vec3(0, 0, 1));
  ret = glm::scale(ret, obj->transform.scale.toGLM());

  return ret;
}


void updateAllUniques() {
  if (!uniqueCount)
    return;

  int uniquesHandled = 0;

  for (int i = 0; i < _MAX_UNIQUE_TYPES; i++) {
    if (uniquesHandled >= uniqueCount)
      break;

    UniqueType* tType = globalUniqueTypes[i];
    if (!tType)
      continue;

    if (tType->parent == nullptr)
      updateUniqueTypeChildren(tType);
    updateUniqueTypeScripts(tType);

    tType->update();
    uniquesHandled++;
  }
}