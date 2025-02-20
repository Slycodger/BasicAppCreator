#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "textureLoading.h"
#include "objects.h"
#include "mathConstants.h"
#include "UniqueTypes.h"

namespace nModelLoading {
				void start(std::string str, std::string objName, bool flipUVs);
				void end();
}