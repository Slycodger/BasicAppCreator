#pragma once
#include "stb_image.h"
#include "openGL.h"
#include <string>
#include <map>
#include <vector>

class Texture {
public:

				enum type { ALBEDO, NORMAL, METALLIC, ROUGHNESS, AO };

				unsigned int texture;
				int width;
				int height;
				type texType;

				Texture() : texture(0), width(0), height(0), texType(ALBEDO) {}
				Texture(unsigned int tex, int w, int h, type t) : texture(tex), height(h), width(w), texType(t) {}
};

void removeTexture(std::string name);
bool loadTexture(std::string name, Texture** retTexture, Texture::type t, bool abs, bool flip, bool gCorrection);
void deleteAllTextures();
Texture* getTexture(std::string name);
bool loadCubeMapTexture(std::string name, std::vector<std::string> textures, Texture** retTexture, Texture::type t, bool abs, bool flip, bool gCorrection);
bool loadEnvironmentTexture(std::string name, Texture** retTexture, bool abs, bool flip);
void includeTexture(std::string name, Texture* texture);