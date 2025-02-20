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
  bool rotations = false;
  int index = -1;

  UniqueType* copySelf() override {
    DirectionalLight* ret = new DirectionalLight('c');
    ret->activeLight = activeLight;
    return ret;
  }

  glm::mat4 rotationMatrix = glm::mat4(1);
  void update() override {
    if (rotations) {
      rotationMatrix = glm::mat4(1);
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.x * _degToRadF, glm::vec3(1, 0, 0));
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.y * _degToRadF, glm::vec3(0, 1, 0));
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.z * _degToRadF, glm::vec3(0, 0, 1));
      activeLight.direction = rotationMatrix * glm::vec4(0, 0, -1, 1);
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


  DirectionalLight(char) : activeLight(ShaderDirectionalLight()), index(-1), rotations(false) {}

  DirectionalLight() {
    activeLight = ShaderDirectionalLight();
    index = directionalLightCount;
    lights[index] = this;
    directionalLightCount++;
    rotations = false;
  }

  DirectionalLight(Vec4 dir, Vec4 c) {
    activeLight = ShaderDirectionalLight(dir, c);
    index = directionalLightCount;
    lights[index] = this;
    directionalLightCount++;
    rotations = false;
  }
};


class SpotLight : public UniqueType {
public:
  const Unique::Types getType() const override { return Unique::SPOTLIGHT; }


  static SpotLight* lights[_MAX_UNIQUE_TYPES];
  static int spotLightCount;


  bool rotations = false;

  ShaderSpotLight activeLight;
  int index = -1;

  glm::mat4 rotationMatrix = glm::mat4(1);

  UniqueType* copySelf() override {
    SpotLight* ret = new SpotLight('c');
    ret->activeLight = activeLight;
    return ret;
  }

  void update() override {
    activeLight.position = transform.position;
    if (rotations) {
      rotationMatrix = glm::mat4(1);
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.x * _degToRadF, glm::vec3(1, 0, 0));
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.y * _degToRadF, glm::vec3(0, 1, 0));
      rotationMatrix = glm::rotate(rotationMatrix, transform.rotation.z * _degToRadF, glm::vec3(0, 0, 1));
      activeLight.direction = rotationMatrix * glm::vec4(0, 0, -1, 1);
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


  SpotLight(char) : activeLight(ShaderSpotLight()), index(-1), rotations(false) {}

  SpotLight() : rotations(false) {
    activeLight = ShaderSpotLight();
    index = spotLightCount;
    lights[index] = this;
    spotLightCount++;
  }

  SpotLight(Vec4 pos, Vec4 dir, Vec4 c, float iR, float oR) : rotations(false) {
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



constexpr const char* POINTLIGHTCOLOR0 = "pointLights[0].color";
constexpr const char* POINTLIGHTCOLOR1 = "pointLights[1].color";
constexpr const char* POINTLIGHTCOLOR2 = "pointLights[2].color";
constexpr const char* POINTLIGHTCOLOR3 = "pointLights[3].color";
constexpr const char* POINTLIGHTCOLOR4 = "pointLights[4].color";
constexpr const char* POINTLIGHTCOLOR5 = "pointLights[5].color";
constexpr const char* POINTLIGHTCOLOR6 = "pointLights[6].color";
constexpr const char* POINTLIGHTCOLOR7 = "pointLights[7].color";
constexpr const char* POINTLIGHTCOLOR[8] = { POINTLIGHTCOLOR0, POINTLIGHTCOLOR1, POINTLIGHTCOLOR2, POINTLIGHTCOLOR3, POINTLIGHTCOLOR4, POINTLIGHTCOLOR5, POINTLIGHTCOLOR6, POINTLIGHTCOLOR7 };

constexpr const char* POINTLIGHTPOS0 = "pointLights[0].pos";
constexpr const char* POINTLIGHTPOS1 = "pointLights[1].pos";
constexpr const char* POINTLIGHTPOS2 = "pointLights[2].pos";
constexpr const char* POINTLIGHTPOS3 = "pointLights[3].pos";
constexpr const char* POINTLIGHTPOS4 = "pointLights[4].pos";
constexpr const char* POINTLIGHTPOS5 = "pointLights[5].pos";
constexpr const char* POINTLIGHTPOS6 = "pointLights[6].pos";
constexpr const char* POINTLIGHTPOS7 = "pointLights[7].pos";
constexpr const char* POINTLIGHTPOS[8] = { POINTLIGHTPOS0, POINTLIGHTPOS1, POINTLIGHTPOS2, POINTLIGHTPOS3, POINTLIGHTPOS4, POINTLIGHTPOS5, POINTLIGHTPOS6, POINTLIGHTPOS7 };

constexpr const char* POINTLIGHTCONSTANT0 = "pointLights[0].constant";
constexpr const char* POINTLIGHTCONSTANT1 = "pointLights[1].constant";
constexpr const char* POINTLIGHTCONSTANT2 = "pointLights[2].constant";
constexpr const char* POINTLIGHTCONSTANT3 = "pointLights[3].constant";
constexpr const char* POINTLIGHTCONSTANT4 = "pointLights[4].constant";
constexpr const char* POINTLIGHTCONSTANT5 = "pointLights[5].constant";
constexpr const char* POINTLIGHTCONSTANT6 = "pointLights[6].constant";
constexpr const char* POINTLIGHTCONSTANT7 = "pointLights[7].constant";
constexpr const char* POINTLIGHTCONSTANT[8] = { POINTLIGHTCONSTANT0, POINTLIGHTCONSTANT1, POINTLIGHTCONSTANT2, POINTLIGHTCONSTANT3, POINTLIGHTCONSTANT4, POINTLIGHTCONSTANT5, POINTLIGHTCONSTANT6, POINTLIGHTCONSTANT7 };

constexpr const char* POINTLIGHTLINEAR0 = "pointLights[0].linear";
constexpr const char* POINTLIGHTLINEAR1 = "pointLights[1].linear";
constexpr const char* POINTLIGHTLINEAR2 = "pointLights[2].linear";
constexpr const char* POINTLIGHTLINEAR3 = "pointLights[3].linear";
constexpr const char* POINTLIGHTLINEAR4 = "pointLights[4].linear";
constexpr const char* POINTLIGHTLINEAR5 = "pointLights[5].linear";
constexpr const char* POINTLIGHTLINEAR6 = "pointLights[6].linear";
constexpr const char* POINTLIGHTLINEAR7 = "pointLights[7].linear";
constexpr const char* POINTLIGHTLINEAR[8] = { POINTLIGHTLINEAR0, POINTLIGHTLINEAR1, POINTLIGHTLINEAR2, POINTLIGHTLINEAR3, POINTLIGHTLINEAR4, POINTLIGHTLINEAR5, POINTLIGHTLINEAR6, POINTLIGHTLINEAR7 };

constexpr const char* POINTLIGHTQUADRATIC0 = "pointLights[0].quadratic";
constexpr const char* POINTLIGHTQUADRATIC1 = "pointLights[1].quadratic";
constexpr const char* POINTLIGHTQUADRATIC2 = "pointLights[2].quadratic";
constexpr const char* POINTLIGHTQUADRATIC3 = "pointLights[3].quadratic";
constexpr const char* POINTLIGHTQUADRATIC4 = "pointLights[4].quadratic";
constexpr const char* POINTLIGHTQUADRATIC5 = "pointLights[5].quadratic";
constexpr const char* POINTLIGHTQUADRATIC6 = "pointLights[6].quadratic";
constexpr const char* POINTLIGHTQUADRATIC7 = "pointLights[7].quadratic";
constexpr const char* POINTLIGHTQUADRATIC[8] = { POINTLIGHTQUADRATIC0, POINTLIGHTQUADRATIC1, POINTLIGHTQUADRATIC2, POINTLIGHTQUADRATIC3, POINTLIGHTQUADRATIC4, POINTLIGHTQUADRATIC5, POINTLIGHTQUADRATIC6, POINTLIGHTQUADRATIC7 };

constexpr const char* POINTLIGHT0 = "PointLight[0]";
constexpr const char* POINTLIGHT1 = "PointLight[1]";
constexpr const char* POINTLIGHT2 = "PointLight[2]";
constexpr const char* POINTLIGHT3 = "PointLight[3]";
constexpr const char* POINTLIGHT4 = "PointLight[4]";
constexpr const char* POINTLIGHT5 = "PointLight[5]";
constexpr const char* POINTLIGHT6 = "PointLight[6]";
constexpr const char* POINTLIGHT7 = "PointLight[7]";
constexpr const char* POINTLIGHTS[8] = { POINTLIGHT0, POINTLIGHT1, POINTLIGHT2, POINTLIGHT3, POINTLIGHT4, POINTLIGHT5, POINTLIGHT6, POINTLIGHT7 };