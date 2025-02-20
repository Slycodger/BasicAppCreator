#pragma once
#include "input.h"
#include "camera.h"
#include "globalVars.h"

namespace Movement {
				void camera(Camera* cam, float speed);
				void freeMove(Camera* cam, float speed);
}