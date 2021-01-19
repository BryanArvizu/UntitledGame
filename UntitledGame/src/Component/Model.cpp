#include "Model.h"
#include "../Rendering/Renderer.h"
#include <iostream>

ret::Model::Model()
{
    std::vector<ret::Vertex> cubeVertices = {
		// FRONT
		ret::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0,0,1), glm::vec2(0,0)},
		ret::Vertex{glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0,0,1), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(0,0,1), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(0.5f,  0.5f, 0.5f),  glm::vec3(0,0,1), glm::vec2(1,1)},

		// LEFT
		ret::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1,0,0), glm::vec2(0,0)},
		ret::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(-1,0,0), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(-1,0,0), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(-1,0,0), glm::vec2(1,1)},

		// RIGHT
		ret::Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(1,0,0), glm::vec2(0,0)},
		ret::Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1,0,0), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec3(1,0,0), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec3(1,0,0), glm::vec2(1,1)},

		// BACK
		ret::Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(0,0,-1), glm::vec2(0,0)},
		ret::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0,0,-1), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec3(0,0,-1), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),	glm::vec3(0,0,-1), glm::vec2(1,1)},

		// TOP
		ret::Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec3(0,1,0), glm::vec2(0,0)},
		ret::Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec3(0,1,0), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0,1,0), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0,1,0), glm::vec2(1,1)},

		// BOTTOM
		ret::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0,-1,0), glm::vec2(1,1)},
		ret::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0,-1,0), glm::vec2(1,0)},
		ret::Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0,-1,0), glm::vec2(0,1)},
		ret::Vertex{glm::vec3(0.5f,  -0.5f, 0.5f),  glm::vec3(0,-1,0), glm::vec2(1,1)}
	};
    std::vector<unsigned int> cubeIndices = {  // note that we start from 0!
        0, 1, 3, 0, 3, 2,
        4, 5, 7, 4, 7, 6,
        8, 9, 11, 8, 11, 10,
        12, 13, 15, 12, 15, 14,
        16, 17, 19, 16, 19, 18,
        20, 23, 21, 20, 22, 23
    };

    Mesh mesh(cubeVertices, cubeIndices);
    meshes.push_back(mesh);
}

ret::Model::Model(std::string path)
{
    loadModel(path);
}

void ret::Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    meshes.clear();
    directory = path.substr(0, path.find_last_of('/'));
    filename = path.substr(path.find_last_of('/'), path.back());
    std::cout << "FILENAME: " << directory << std::endl;
    processNode(scene->mRootNode, scene);
}

void ret::Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process all of the node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Recursively call this function on all children (if any)
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

ret::Mesh ret::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Process all vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        ret::Vertex vertex;

        glm::vec3 tempVector;

        // Positional Vectors
        tempVector.x = mesh->mVertices[i].x;
        tempVector.y = mesh->mVertices[i].y;
        tempVector.z = mesh->mVertices[i].z;
        vertex.position = tempVector;

        // Normal Vectors
        tempVector.x = mesh->mNormals[i].x;
        tempVector.y = mesh->mNormals[i].y;
        tempVector.z = mesh->mNormals[i].z;
        vertex.normal = tempVector;

        // UV Vectors
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
        }
        else
        {
            vertex.uv = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process all indicies
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    ret::Material* mat = nullptr;
    // Process all textures
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        mat = ret::MaterialManager::GetMaterial(filename);
        mat->shader = ret::ShaderManager::GetShader("test_shader");

        std::vector<ret::Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        mat->textures.insert(mat->textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<ret::Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        mat->textures.insert(mat->textures.end(), specularMaps.begin(), specularMaps.end());

        
    }
    
    return Mesh(vertices, indices, mat);
}

std::vector<ret::Texture*> ret::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<ret::Texture*> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        ret::Texture* texture = ret::TextureManager::GetTexture(str.C_Str());
        texture->type = typeName;
        //texture->path = str.C_Str();
        textures.push_back(texture);
    }

    return textures;
}
