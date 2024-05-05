#include "Model.h"

#include <iostream>
#include <vector>
#include <sstream>

namespace Shue {

	Model::Model(const std::string& path)
	{
		LoadModel(path);
	}

	void Model::LoadModel(const std::string& path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return;
		}
		m_Directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], scene);
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<ImageTexture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 tempVector;

			tempVector.x = mesh->mVertices[i].x;
			tempVector.y = mesh->mVertices[i].y;
			tempVector.z = mesh->mVertices[i].z;
			vertex.Position = tempVector;

			tempVector.x = mesh->mNormals[i].x;
			tempVector.y = mesh->mNormals[i].y;
			tempVector.z = mesh->mNormals[i].z;
			vertex.Normal = tempVector;

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 texCoords;
				texCoords.x = mesh->mTextureCoords[0][i].x;
				texCoords.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = texCoords;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<ImageTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<ImageTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<ImageTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<ImageTexture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			bool skip = false;
			for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
			{
				if (std::strcmp(m_LoadedTextures[j].Path().c_str(), str.C_Str()) == 0)
				{
					textures.push_back(m_LoadedTextures[j]);
					skip = true;
					break;
				}
			}

			if (skip == false)
			{
				ImageTexture* texture = new ImageTexture(str.C_Str(), typeName, m_Directory + "/");
				textures.push_back(*texture);
				m_LoadedTextures.push_back(*texture);
			}
		}
		return textures;
	}
}