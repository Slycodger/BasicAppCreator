#define _MATERIAL
#include "material.h"

//Local globals
//--------------------------------------------------
std::map<std::string, Material*> globalMaterials;
//--------------------------------------------------





Material* createMaterial(std::string name) {
				if (globalMaterials.contains(name))
								return nullptr;

				Material* nMat = new Material;
				globalMaterials.insert({ name, nMat });
				return nMat;
}

Material* getMaterial(std::string name) {
				if (!globalMaterials.contains(name))
								return nullptr;

				return globalMaterials[name];
}

bool deleteMaterial(std::string name) {
				if (!globalMaterials.contains(name))
								return false;

				delete (globalMaterials[name]);
				return globalMaterials.erase(name);
}



namespace nMaterial {
				void end() {
								for (auto& mat : globalMaterials)
												delete(mat.second);
								globalMaterials.clear();
				}
}