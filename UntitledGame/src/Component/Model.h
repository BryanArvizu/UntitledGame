#pragma once

#include "Component.h"
#include "Mesh.h"

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ret {
    class Renderer;
    class Entity;

    class Model : public Component
    {
    public:
        std::vector<ret::Mesh> meshes;
        std::string directory;
        std::string filename;

    public:
        Model();
        Model(std::string path);

        virtual void Start() {};
        virtual void FixedUpdate() {};
        virtual void Update() {};

        void loadModel(std::string path);

    private:
        void processNode(aiNode* node, const aiScene* scene);
        ret::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<ret::Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };

    class ModelManager
    {
    public:
        static std::unordered_map<std::string, Model> models;
        static Model* GetModel(std::string path);
    };
}

