#version 460 core

layout(std140, binding=0) uniform Material {
  vec4 albedo;
  float metallic;
  float roughness;

  bool useAlbedoMap;
  bool useNormalMap;
  bool useMetallicMap;
  bool useRoughnessMap;
  bool useAoMap;
} material;

uniform sampler2D albedoMap;


in vec2 uvCoord;

out vec4 fragColor;

void main() {
		fragColor = material.albedo;
		if (material.useAlbedoMap)
				fragColor *= texture(albedoMap, uvCoord);
}