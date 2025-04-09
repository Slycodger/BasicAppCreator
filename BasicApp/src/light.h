#pragma once
#include "vector.h"
#include <vector>
#include "constants.h"
#include "uniqueTypes.h"


class ShaderPointLight {
public:
  Vec4 position;
  Vec4 color;

  ShaderPointLight() : position(0), color(1) {}
  ShaderPointLight(Vec4 p, Vec4 c) : position(p), color(c) {}
};

class ShaderDirectionalLight {
public:
  Vec4 direction;
  Vec4 color;

  ShaderDirectionalLight() : direction(0, 0, -1, 0), color(1) {}
  ShaderDirectionalLight(Vec4 dir, Vec4 c) : direction(dir), color(c) {}
};


class ShaderSpotLight {
public:
  Vec4 position;
  Vec4 direction;
  Vec4 color;
  float innerCutoff;
  float outerCutoff;

  Vec2 extra;

  ShaderSpotLight() : position(0), direction(0, 0, -1, 0), color(1), innerCutoff(1), outerCutoff(1), extra(0) {}
  ShaderSpotLight(Vec4 pos, Vec4 dir, Vec4 c, float iR, float oR) : position(pos), direction(dir), color(c), innerCutoff(iR), outerCutoff(oR), extra(0) {}
};




class PointLight : public UniqueType {
public:
  const Unique::Types getType() const override { return Unique::POINTLIGHT; }


  static PointLight* lights[_MAX_UNIQUE_TYPES];
  static int pointLightCount;


  ShaderPointLight activeLight;
  int index = -1;

  UniqueType* copySelf() override {
    PointLight* ret = new PointLight('c');
    ret->activeLight = activeLight;
    return ret;
  }

  void update() override {
    activeLight.position = transform.position;
  }

  void end() override {
    if (index >= 0) {
      lights[index] = lights[pointLightCount - 1];
      lights[index]->index = index;
      lights[pointLightCount - 1] = nullptr;
      pointLightCount--;
    }
  }


  PointLight(char) : activeLight(ShaderPointLight()), index(-1) {}

  PointLight() {
    activeLight = ShaderPointLight();
    index = pointLightCount;
    lights[index] = this;
    pointLightCount++;
  }

  PointLight(Vec4 p, Vec4 c) {
    activeLight = ShaderPointLight(p, c);
    index = pointLightCount;
    lights[index] = this;
    pointLightCount++;
  }
};

class DirectionalLight : public UniqueType {
public:
  const Unique::Types getType() const override { return Unique::POINTLIGHT; }


  static DirectionalLight* lights[_MAX_UNIQUE_TYPES];
  static int directionalLightCount;


  ShaderDirectionalLight activeLight;
  bool followRotations = false;
  int index = -1;

  UniqueType* copySelf() override {
    DirectionalLight* ret = new DirectionalLight('c');
    ret->activeLight = activeLight;
    return ret;
  }

  glm::mat4 rotationMatrix = glm::mat4(1);
  void update() override {
    if (followRotations) {
      float pitch = transform.rotation.x * _degToRadF;
      float yaw = transform.rotation.y * _degToRadF;

      activeLight.direction.x = cos(yaw) * cos(pitch);
      activeLight.direction.y = sin(pitch);
      activeLight.direction.z = sin(yaw) * cos(pitch);
    }
  }

  void end() override {
    if (index >= 0) {
      lights[index] = lights[directionalLightCount - 1];
      lights[index]->index = index;
      lights[directionalLightCount - 1] = nullptr;
      directionalLightCount--;
    }
  }


  DirectionalLight(char) : activeLight(ShaderDirectionalLight()), index(-1), followRotations(false) {}

  DirectionalLight() {
    activeLight = ShaderDirectionalLight();
    index = directionalLightCount;
    lights[index] = this;
    directionalLightCount++;
    followRotations = false;
  }

  DirectionalLight(Vec4 dir, Vec4 c) {
    activeLight = ShaderDirectionalLight(dir, c);
    index = directionalLightCount;
    lights[index] = this;
    directionalLightCount++;
    followRotations = false;
  }
};


class SpotLight : public UniqueType {
public:
  const Unique::Types getType() const override { return Unique::SPOTLIGHT; }


  static SpotLight* lights[_MAX_UNIQUE_TYPES];
  static int spotLightCount;


  bool followRotations = false;

  ShaderSpotLight activeLight;
  int index = -1;


  UniqueType* copySelf() override {
    SpotLight* ret = new SpotLight('c');
    ret->activeLight = activeLight;
    return ret;
  }

  void update() override {
    activeLight.position = transform.position;
    if (followRotations) {
      float pitch = transform.rotation.x * _degToRadF;
      float yaw = transform.rotation.y * _degToRadF;

      activeLight.direction.x = cos(yaw) * cos(pitch);
      activeLight.direction.y = sin(pitch);
      activeLight.direction.z = sin(yaw) * cos(pitch);
    }
  }

  void end() override {
    if (index >= 0) {
      lights[index] = lights[spotLightCount - 1];
      lights[index]->index = index;
      lights[spotLightCount - 1] = nullptr;
      spotLightCount--;
    }
  }


  SpotLight(char) : activeLight(ShaderSpotLight()), index(-1), followRotations(false) {}

  SpotLight() : followRotations(false) {
    activeLight = ShaderSpotLight();
    index = spotLightCount;
    lights[index] = this;
    spotLightCount++;
  }

  SpotLight(Vec4 pos, Vec4 dir, Vec4 c, float iR, float oR) : followRotations(false) {
    activeLight = ShaderSpotLight(pos, dir, c, iR, oR);
    index = spotLightCount;
    lights[index] = this;
    spotLightCount++;
  }
};


class PointLightContainer {
public:
  ShaderPointLight lights[_MAX_ACTING_POINT_LIGHTS] = {};
  PointLightContainer() : lights() {}
};

class DirectionalLightContainer {
public:
  ShaderDirectionalLight lights[_MAX_ACTING_POINT_LIGHTS] = {};
  DirectionalLightContainer() : lights() {}
};

class SpotLightContainer {
public:
  ShaderSpotLight lights[_MAX_ACTING_SPOT_LIGHTS] = {};
  SpotLightContainer() : lights() {}
};