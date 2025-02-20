#include "modelLoading.h"
using namespace nModelLoading;

std::vector<std::tuple<uint*, uint*, std::vector<Vertex>>> meshContainers;

Object* processMesh(aiMesh* mesh, const aiScene* scene, std::string nodeName, std::string modelPath) {
  if (mesh->mNumVertices == 0 || mesh->mNumFaces == 0)
    return nullptr;

  Mesh* retMesh = nullptr;
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  Vertex vert;

  Vec3 faceNormal = { 0 };


  for (uint i = 0; i < mesh->mNumVertices; i++) {
    vert = Vertex();

    vert.position.x = mesh->mVertices[i].x;
    vert.position.y = mesh->mVertices[i].y;
    vert.position.z = mesh->mVertices[i].z;


    if (!mesh->mNormals) {
      if (i % 3 == 0) {
        faceNormal = vert.position;
      }
      if (i % 3 == 1) {
        faceNormal = Vec3::normalize(Vec3::cross(faceNormal, vert.position));
        vert.normal = faceNormal;
        vertices[vertices.size() - 2].normal = faceNormal;
      } else
        vert.normal = faceNormal;
    } else {
      vert.normal.x = mesh->mNormals[i].x;
      vert.normal.y = mesh->mNormals[i].y;
      vert.normal.z = mesh->mNormals[i].z;
    }

    if (mesh->mTangents) {
      vert.tangent.x = mesh->mTangents[i].x;
      vert.tangent.y = mesh->mTangents[i].y;
      vert.tangent.z = mesh->mTangents[i].z;
    }


    if (mesh->mTextureCoords[0]) {
      vert.uv.x = mesh->mTextureCoords[0][i].x;
      vert.uv.y = mesh->mTextureCoords[0][i].y;
    }

    vertices.push_back(vert);
  }

  for (uint j = 0; j < mesh->mNumFaces; j++) {
    aiFace face = mesh->mFaces[j];
    for (uint k = 0; k < face.mNumIndices; k++) {
      indices.push_back(face.mIndices[k]);
    }
  }
  if (mesh->mNumFaces) {
    std::vector<Vertex> tempVerts = vertices;
    vertices.clear();

    for (uint index : indices) {
      vertices.push_back(tempVerts[index]);
    }
    tempVerts.clear();
  }

  retMesh = new Mesh({ vertices.data(), vertices.size() });

  meshContainers.push_back({ 0, 0, {} });

  std::get<0>(meshContainers[meshContainers.size() - 1]) = new uint(0);
  std::get<1>(meshContainers[meshContainers.size() - 1]) = new uint(mesh->mNumFaces);
  std::get<2>(meshContainers[meshContainers.size() - 1]) = std::move(vertices);
  createMeshBuffers(
    *std::get<0>(meshContainers[meshContainers.size() - 1]),
    reinterpret_cast<float*>(retMesh->vertices.data()),
    retMesh->vertices.size_bytes());

  retMesh->VBO = std::get<0>(meshContainers[meshContainers.size() - 1]);
  retMesh->triCount = std::get<1>(meshContainers[meshContainers.size() - 1]);

  if (!loadMesh(retMesh, mesh->mName.C_Str() + std::string("__") + nodeName))
    return nullptr;

  Object* obj = (Object*)createUniqueType(Unique::OBJECT, 'c');
  setObjMesh(obj, mesh->mName.C_Str() + std::string("__") + nodeName);


  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];


    //-----------------------------------------------------------
    if (mat->GetTextureCount(aiTextureType_DIFFUSE)) {
      aiString aiStr;
      std::string str;
      mat->GetTexture(aiTextureType_DIFFUSE, 0, &aiStr);

      str = modelPath + aiStr.C_Str();

      Texture* genTexture = nullptr;
      if (loadTexture(str, &genTexture, Texture::ALBEDO, true, true, true))
        obj->srcMaterial.albedoMap = genTexture;
    } else {
      obj->srcMaterial.albedo = 1;
      aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, (aiColor4D*)&obj->srcMaterial.albedo);
    }


    //-----------------------------------------------------------
    if (mat->GetTextureCount(aiTextureType_METALNESS)) {
      aiString aiStr;
      std::string str;
      mat->GetTexture(aiTextureType_METALNESS, 0, &aiStr);

      str = modelPath + aiStr.C_Str();

      Texture* genTexture = nullptr;
      if (loadTexture(str, &genTexture, Texture::METALLIC, true, true, true))
        obj->srcMaterial.metallicMap = genTexture;
    } else {
      obj->srcMaterial.metallic = 0;
      aiGetMaterialFloat(mat, AI_MATKEY_REFLECTIVITY, &obj->srcMaterial.metallic);
    }


    //-----------------------------------------------------------
    if (mat->GetTextureCount(aiTextureType_SHININESS)) {
      aiString aiStr;
      std::string str;
      mat->GetTexture(aiTextureType_SHININESS, 0, &aiStr);

      str = modelPath + aiStr.C_Str();

      Texture* genTexture = nullptr;
      if (loadTexture(str, &genTexture, Texture::ROUGHNESS, true, true, true))
        obj->srcMaterial.roughnessMap = genTexture;
    } else {
      obj->srcMaterial.roughness = 0.5;
      aiGetMaterialFloat(mat, AI_MATKEY_ROUGHNESS_FACTOR, &obj->srcMaterial.roughness);
    }


    //-----------------------------------------------------------
    if (mat->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION)) {
      aiString aiStr;
      std::string str;
      mat->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &aiStr);

      str = modelPath + aiStr.C_Str();

      Texture* genTexture = nullptr;
      if (loadTexture(str, &genTexture, Texture::AO, true, true, true))
        obj->srcMaterial.aoMap = genTexture;
    }


    //-----------------------------------------------------------
    if (mat->GetTextureCount(aiTextureType_NORMAL_CAMERA)) {
      aiString aiStr;
      std::string str;
      mat->GetTexture(aiTextureType_NORMAL_CAMERA, 0, &aiStr);
      str = modelPath + aiStr.C_Str();

      Texture* genTexture = nullptr;
      if (loadTexture(str, &genTexture, Texture::NORMAL, true, true, false))
        obj->srcMaterial.normalMap = genTexture;
    }
  }



  obj->node = false;
  return obj;
}

Object* processNode(aiNode* node, const aiScene* scene, Object* parent, std::string nodeName, std::string modelPath) {
  Object* obj = nullptr;
  Object* nodeObj = nullptr;


  for (uint i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    obj = processMesh(mesh, scene, nodeName, modelPath);

    if (!obj)
      continue;

    if (!nodeObj) {
      nodeObj = new Object();
      nodeObj->setParent(parent);
    }

    obj->setParent(nodeObj);
  }

  for (uint i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene, nodeObj ? nodeObj : parent, nodeName + std::to_string(i), modelPath);
  }



  return parent;
}

Object* handleNode(Object* obj, aiNode* node) {
  aiVector3t<float> position;
  aiVector3t<float> rotation;
  aiVector3t<float> scale;

  node->mTransformation.Decompose(scale, rotation, position);

  obj->relativeTransform.position.x = position.x;
  obj->relativeTransform.position.y = position.y;
  obj->relativeTransform.position.z = position.z;

  obj->relativeTransform.rotation.x = rotation.x * _radToDeg;
  obj->relativeTransform.rotation.y = rotation.y * _radToDeg;
  obj->relativeTransform.rotation.z = rotation.z * _radToDeg;

  obj->relativeTransform.scale.x = scale.x;
  obj->relativeTransform.scale.y = scale.y;
  obj->relativeTransform.scale.z = scale.z;

  uint childOn = 0;
  for (uint i = 0; i < node->mNumChildren; i++) {
    if (node->mChildren[i]->mNumMeshes == 0)
      continue;

    while (true) {
      if (childOn >= obj->children.size())
        continue;

      if (!((Object*)obj->children[childOn])->mesh) {
        handleNode(((Object*)obj->children[childOn]), node->mChildren[i]);
        childOn++;
        break;
      }
      childOn++;
    }
  }

  return obj;
}


namespace nModelLoading {
  void start(std::string str, std::string objName, bool flipUVs) {
    Assimp::Importer importer;
    importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
    const aiScene* scene = importer.ReadFile(str.c_str(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FixInfacingNormals | (flipUVs ? aiProcess_FlipUVs : 0) | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cout << "Failed to load model\n";
      return;
    }
    Object* mesh = new Object();
    saveUniqueType(handleNode(processNode(scene->mRootNode, scene, mesh, objName, str.substr(0, str.find_last_of('/') + 1)), scene->mRootNode), objName);
  }

  void end() {
    for (auto& g : meshContainers) {
      glDeleteBuffers(1, std::get<0>(g));
      glDeleteBuffers(1, std::get<1>(g));
      delete(std::get<0>(g));
      delete(std::get<1>(g));
      std::get<2>(g).clear();
    }
    meshContainers.clear();
  }
}