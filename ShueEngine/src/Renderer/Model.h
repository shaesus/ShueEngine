#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"
#include "ImageTexture.h"

#include <string>

namespace Shue {

    class SHUE_API Model
    {
    public:
        Model(const std::string& path);
        ~Model();

        inline const std::vector<Mesh>& Meshes() const { return m_Meshes; }

    private:
        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<ImageTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    private:
        std::vector<Mesh> m_Meshes;
        std::vector<ImageTexture> m_LoadedTextures;
        std::string m_Directory;
    };

}