#pragma once
#if defined(_UNIQUE_TYPES) || defined(_FLOW_CONTROL)
#include <map>
#include <stdexcept>
#include "constants.h"
#include <algorithm>
#include "intializeShader.h"
#include "openGL.h"
#include "GlobalVars.h"
#include "camera.h"
#include "light.h"
#include <format>
#include "objects.h"
namespace nUniqueTypes {
  void start();
  void end();
}
#endif

#include "Unique.h"
#include "transform.h"
#include "objects.h"




void addUniqueTypeScript(UniqueType* tType, void* script);
void removeUniqueTypeScript(UniqueType* tType, unsigned int index);
unsigned int getUniqueTypeScriptIndex(UniqueType* tType, std::string name);
void updateUniqueTypeScripts(UniqueType* tType);
void clearUniqueTypeScripts(UniqueType* tType);
void updateUniqueTypeChildren(UniqueType* tType);
void clearUniqueTypeChildren(UniqueType* tType);
void deleteUniqueType(UniqueType* tType);
void deleteUniqueType(UniqueType* tType, int);
void deleteAll();
void updateAllUniques();
uint findUniqueSlot();
bool addGlobalUniqueType(UniqueType*& tType);
UniqueType* instantiateUniqueType(std::string objName);
UniqueType* createUniqueType(Unique::Types type);
bool saveUniqueType(UniqueType* tType, std::string objName);
void addUniqueTypeScript(UniqueType* tType, void* script, char c);
void deleteUniqueType(UniqueType* tType, const char);
void startUniqueType(UniqueType* tType);
void createScriptUniqueTypes(std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>);
glm::mat4 createUniqueTypeTransformMatrix(UniqueType* obj);
UniqueType* createUniqueType(Unique::Types type, char);