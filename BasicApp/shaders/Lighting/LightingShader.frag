#version 460 core

const int MAX_POINT_LIGHTS = 8;
const int MAX_DIRECTIONAL_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 8;


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
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;


struct PointLight {
  vec4 position;
		vec4 color;
};

struct DirectionalLight {
  vec4 direction;
  vec4 color;
};

struct SpotLight {
  vec4 position;
  vec4 direction;
  vec4 color;
  float innerCutoff;
  float outerCutoff;

  vec2 extra;
};

layout(std140, binding=1) uniform InPointLight {
  PointLight pointLights[MAX_POINT_LIGHTS];
};


layout(std140, binding=2) uniform InDirectionalLight {
  DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
};

layout(std140, binding=3) uniform InSpotLight {
  SpotLight spotLights[MAX_SPOT_LIGHTS];
};


in VS_OUT {
  vec3 fragNormal;
  vec3 fragPos;
  vec2 uvCoord;
  mat3 TBN;
};

out vec4 fragColor;

uniform vec3 cameraPos;

uniform int pointLightCount;
uniform int directionalLightCount;
uniform int spotLightCount;

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;

const float PI = 3.14159265359;
const float MAX_REFLECTION_LOD = 4.0f;

// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float a = roughness*roughness;
  float a2 = a*a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH*NdotH;

  float nom   = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness) {
  float r = (roughness + 1.0);
  float k = (r*r) / 8.0;

  float nom   = NdotV;
  float denom = NdotV * (1.0 - k) + k;

  return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
  float NdotV = max(dot(N, V), 0.0);
  float NdotL = max(dot(N, L), 0.0);
  float ggx2 = GeometrySchlickGGX(NdotV, roughness);
  float ggx1 = GeometrySchlickGGX(NdotL, roughness);

  return ggx1 * ggx2;
}

// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {
  return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}   

// ----------------------------------------------------------------------------
float calculateSpotLightIntensity(vec3 lightDir, SpotLight light) {
  float theta = dot(lightDir, normalize(-light.direction.xyz));
  float epsilon = light.innerCutoff - light.outerCutoff;
  float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);
  return intensity;
}

void main() {
  vec3 N = fragNormal;
  if (material.useNormalMap)
		  N = TBN * (texture(normalMap, uvCoord).xyz * 2 - 1);
  N = normalize(N);

  vec3 albedo = material.albedo.xyz;
		if (material.useAlbedoMap)
    albedo = texture(albedoMap, uvCoord).xyz;

  float metallic = material.metallic;
  if (material.useMetallicMap)
    metallic = texture(metallicMap, uvCoord).x;

  float roughness = material.roughness;
  if (material.useRoughnessMap)
    roughness = texture(roughnessMap, uvCoord).x;

  float ao = 1.f;
  if (material.useAoMap)
    ao = texture(aoMap, uvCoord).x;

		fragColor = vec4(0, 0, 0, 1);
		float lightDist = 0;
		float attenuation = 0;
  float NDF = 0;
  float G = 0;
  float denominator = 0;
  float NdotL = 0;
  vec3 numerator = vec3(0);
  vec3 F = vec3(0);
		vec3 L = vec3(0, 0, 0);
  vec3 H = vec3(0);
		vec3	V = normalize(cameraPos - fragPos);
  vec3 radiance = vec3(0);
  vec3 Lo = vec3(0);
  vec3 kS = vec3(0);
  vec3 kD = vec3(0);
  vec3 R = reflect(-V, N); 

  vec3 F0 = vec3(0.04); 
  F0 = mix(F0, albedo, metallic);


		for (int i = 0; i < pointLightCount; i++) {
    L           = normalize(pointLights[i].position.xyz - fragPos);
    lightDist   = length(pointLights[i].position.xyz - fragPos);
    attenuation = 1 / (lightDist * lightDist);
    H           = normalize(V + L);
  
    radiance    = pointLights[i].color.xyz * attenuation;

    NDF         = DistributionGGX(N, H, roughness);   
    G           = GeometrySmith(N, V, L, roughness);      
    F           = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

    numerator   = NDF * G * F; 
    denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular    = numerator / denominator;

    kS          = F;
    kD          = vec3(1.0) - kS;
    kD          *= 1.0 - metallic;	  

    NdotL       = max(dot(N, L), 0.0);        

    Lo          += (kD * albedo / PI + specular) * radiance * NdotL;
		}

  F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness); 
  kS = F;
  kD = 1.0 - kS;
  kD *= 1.0 - metallic;

  vec3 irradiance = texture(irradianceMap, N).rgb;
  vec3 diffuse    = irradiance * albedo;

  vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;    
  vec2 brdf  = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
  vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);


  vec3 ambient    = (kD * diffuse + specular) * ao; 

  fragColor         = vec4(Lo + ambient, 1);
}