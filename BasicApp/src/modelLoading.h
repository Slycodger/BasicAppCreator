#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "textureLoading.h"
#include "objects.h"
#include "mathConstants.h"
#include "UniqueTypes.h"

bool loadModel(std::string path, bool abs, std::string objName, bool flipUVs);


namespace nModelLoading {
				void end();
}