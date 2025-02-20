#pragma once

#ifdef _MATERIAL

#include <map>

#endif

#include "vector.h"
#include "textureLoading.h"
#include "intializeShader.h"

class shaderMaterial {
public:
  Vec4 albedo;
  float metallic;
  float roughness;

  uint useAlbedoMap;
  uint useNormalMap;
  uint useMetallicMap;
  uint useRoughnessMap;
  uint useAoMap;

  shaderMaterial() : albedo(1), metallic(0), roughness(0), useAlbedoMap(0), useNormalMap(0), useMetallicMap(0), useRoughnessMap(0), useAoMap(0) {}
  shaderMaterial(Vec4 a, float m, float r, uint aM, uint nM, uint mM, uint rM, uint aoM) : albedo(a), metallic(m),
    roughness(r), useAlbedoMap(aM), useNormalMap(nM), useMetallicMap(mM), useRoughnessMap(rM), useAoMap(aoM) {}
};


class Material {
public:
  Vec4 albedo;
  float metallic;
  float roughness;

  Texture* albedoMap;
  Texture* normalMap;
  Texture* metallicMap;
  Texture* roughnessMap;
  Texture* aoMap;

  Material() : albedo(1), metallic(0), roughness(0), albedoMap(nullptr), normalMap(nullptr), metallicMap(nullptr), roughnessMap(nullptr), aoMap(nullptr) {}
  Material(Vec4 a, float m, float r, Texture* aM, Texture* nM, Texture* mM, Texture* rM, Texture* aoM) : albedo(a),
    metallic(m), roughness(r), albedoMap(aM), normalMap(nM), metallicMap(mM), roughnessMap(rM), aoMap(aoM) {}

  shaderMaterial asShaderType() {
    return shaderMaterial(albedo, metallic, roughness, albedoMap ? true : false, normalMap ? true : false, metallicMap ? true : false, roughnessMap ? true : false, aoMap ? true : false);
  }

  void apply() {
    shaderMaterial mat = asShaderType();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(shaderMaterial), &mat);

    if (albedoMap) {
      Shader::setInt("albedoMap", 0);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, albedoMap->texture);
    }

    if (normalMap) {
      Shader::setInt("normalMap", 1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, normalMap->texture);
    }

    if (metallicMap) {
      Shader::setInt("metallicMap", 2);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, metallicMap->texture);
    }

    if (roughnessMap) {
      Shader::setInt("roughnessMap", 3);
      glActiveTexture(GL_TEXTURE3);
      glBindTexture(GL_TEXTURE_2D, roughnessMap->texture);
    }

    if (aoMap) {
      Shader::setInt("aoMap", 4);
      glActiveTexture(GL_TEXTURE4);
      glBindTexture(GL_TEXTURE_2D, aoMap->texture);
    }
  }
};

namespace nMaterial {
  void end();
}

bool deleteMaterial(std::string name);
Material* getMaterial(std::string name);
Material* createMaterial(std::string name);