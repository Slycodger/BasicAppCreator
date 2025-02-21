#define STB_IMAGE_IMPLEMENTATION
#define _TEXTURE_LOADING
#include "textureLoading.h"
#include "basicApp.h"


//--------------------------------------------------
void basicApp_removeTexture(const char* name) {
  removeTexture(name);
}



//--------------------------------------------------
void* basicApp_getTexture(const char* name) {
  return getTexture(name);
}



//--------------------------------------------------
void* basicApp_loadEnvironmentTexture(const char* name, bool abs, bool flip) {
  Texture* retTex = nullptr;
  loadEnvironmentTexture(name, &retTex, abs, flip);
  return retTex;
}



//--------------------------------------------------
void* basicApp_loadCubeMapTexture(const char* name, const char* textures[6], int texType, bool abs, bool flip, bool gCorrection) {
  Texture* retTex = nullptr;
  loadCubeMapTexture(name, { textures[0], textures[1], textures[2], textures[3], textures[4], textures[5] }, &retTex, Texture::type(texType), abs, flip, gCorrection);
  return retTex;
}



//--------------------------------------------------
void* basicApp_loadTexture(const char* name, int texType, bool abs, bool flip, bool gCorrection) {
  Texture* retTex = nullptr;
  loadTexture(name, &retTex, Texture::type(texType), abs, flip, gCorrection);
  return retTex;
}







std::map<std::string, Texture*> globalTextures;

void includeTexture(std::string name, Texture* texture) {
  if (!texture || !texture->texture)
    return;

  globalTextures.insert({ name, texture });
}

void removeTexture(std::string name) {
  if (!globalTextures.contains(name))
    return;

  glDeleteTextures(1, &globalTextures[name]->texture);
  delete (globalTextures[name]);
  globalTextures.erase(name);
}

Texture* getTexture(std::string name) {
  if (globalTextures.contains(name))
    return globalTextures[name];
  return nullptr;
}

bool loadEnvironmentTexture(std::string name, Texture** retTexture, bool abs, bool flip) {
  Texture* useTexture = nullptr;

  if (retTexture) {
    delete(*retTexture);
    *retTexture = nullptr;
  }
  if (globalTextures.contains(name)) {
    if (retTexture)
      *retTexture = globalTextures[name];
    return true;
  }

  useTexture = new Texture;
  useTexture->texType = Texture::ALBEDO;

  if (retTexture)
    *retTexture = useTexture;

  glDeleteTextures(1, &useTexture->texture);
  glGenTextures(1, &useTexture->texture);

  glBindTexture(GL_TEXTURE_2D, useTexture->texture);

  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  float* imageData = nullptr;
  int channels = 0;

  stbi_set_flip_vertically_on_load(flip);
  imageData = stbi_loadf(((abs ? "" : "./environments/") + name).c_str(), &useTexture->width, &useTexture->height, &channels, 0);

  if (imageData) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, useTexture->width, useTexture->height, 0, GL_RGB, GL_FLOAT, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    globalTextures.insert({ name, useTexture });
    return true;
  } else {
    delete(useTexture);
    useTexture = nullptr;
    stbi_image_free(imageData);
    return false;
  }
}


bool loadCubeMapTexture(std::string name, std::vector<std::string> textures, Texture** retTexture, Texture::type t, bool abs, bool flip, bool gCorrection) {
  Texture* useTexture = nullptr;

  if (retTexture) {
    delete(*retTexture);
    *retTexture = nullptr;
  }
  if (globalTextures.contains(name)) {
    if (retTexture)
      *retTexture = globalTextures[name];
    return true;
  }

  if (textures.size() != 6)
    return false;

  useTexture = new Texture;
  useTexture->texType = t;

  if (retTexture)
    *retTexture = useTexture;

  glGenTextures(1, &useTexture->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, useTexture->texture);


  unsigned char* imageData = nullptr;
  int channels = 0;
  short internalImageType = GL_RED;
  short imageType = GL_RED;

  stbi_set_flip_vertically_on_load(flip);
  for (int i = 0; i < 6; i++) {
    imageData = stbi_load(((abs ? "" : "./Textures/") + textures[i]).c_str(), &useTexture->width, &useTexture->height, &channels, 0);

    if (imageData) {
      switch (channels) {
      case 2:
        internalImageType = GL_RG;
        imageType = GL_RG;
        break;
      case 3:
        if (!gCorrection)
          internalImageType = GL_RGB;
        else
          internalImageType = GL_SRGB;
        imageType = GL_RGB;
        break;
      case 4:
        if (!gCorrection)
          internalImageType = GL_RGBA;
        else
          internalImageType = GL_SRGB_ALPHA;
        imageType = GL_RGB;
        break;
      default:
        internalImageType = GL_RED;
        imageType = GL_RED;
        break;
      }
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalImageType, useTexture->width, useTexture->height, 0, imageType, GL_UNSIGNED_BYTE, imageData);
      stbi_image_free(imageData);
    } else {
      delete(useTexture);
      useTexture = nullptr;
      stbi_image_free(imageData);
      return false;
    }
  }

  useTexture->width = 0;
  useTexture->height = 0;
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  globalTextures.insert({ name, useTexture });
  return true;

}

bool loadTexture(std::string name, Texture** retTexture, Texture::type t, bool abs, bool flip, bool gCorrection) {
  Texture* useTexture = nullptr;

  if (retTexture) {
    delete(*retTexture);
    *retTexture = nullptr;
  }
  if (globalTextures.contains(name)) {
    if (retTexture)
      *retTexture = globalTextures[name];
    return true;
  }

  useTexture = new Texture;
  useTexture->texType = t;

  if (retTexture)
    *retTexture = useTexture;

  glDeleteTextures(1, &useTexture->texture);
  glGenTextures(1, &useTexture->texture);

  glBindTexture(GL_TEXTURE_2D, useTexture->texture);

  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  unsigned char* imageData = nullptr;
  int channels = 0;
  int imageType = GL_RED;
  int internalImageType = GL_RED;

  stbi_set_flip_vertically_on_load(flip);
  imageData = stbi_load(((abs ? "" : "./Textures/") + name).c_str(), &useTexture->width, &useTexture->height, &channels, 0);

  if (imageData) {
    switch (channels) {
    case 2:
      internalImageType = GL_RG;
      imageType = GL_RG;
      break;
    case 3:
      if (!gCorrection)
        internalImageType = GL_RGB;
      else
        internalImageType = GL_SRGB;
      imageType = GL_RGB;
      break;
    case 4:
      if (!gCorrection)
        internalImageType = GL_RGBA;
      else
        internalImageType = GL_SRGB_ALPHA;
      imageType = GL_RGBA;
      break;
    default:
      internalImageType = GL_RED;
      imageType = GL_RED;
      break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalImageType, useTexture->width, useTexture->height, 0, imageType, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    globalTextures.insert({ name, useTexture });
    return true;
  } else {
    delete(useTexture);
    useTexture = nullptr;
    stbi_image_free(imageData);
    return false;
  }
}

void deleteAllTextures() {
  for (auto& obj : globalTextures) {
    delete(obj.second);
  }
}