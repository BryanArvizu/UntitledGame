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

    class Model : public Component
    {
    public:
        std::vector<ret::Mesh> meshes;
        std::string directory;

    public:
        Model();
        Model(std::string path);

        virtual void Start() {};
        virtual void FixedUpdate() {};
        virtual void Update() {};

        void loadModel(std::string path);
        void AddToRenderer(Renderer*);

    private:
        void processNode(aiNode* node, const aiScene* scene);
        ret::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<ret::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };
}

