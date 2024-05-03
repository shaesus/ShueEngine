#pragma once

#include "glm/glm.hpp"

#include "ImageTexture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <vector>

namespace Shue {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    class Mesh 
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ImageTexture> textures);

        const std::vector<Vertex>& Vertices() const { return m_vertices; }
        const std::vector<unsigned int>& Indices() const { return m_indices; }
        const std::vector<ImageTexture>& Textures() const { return m_textures; }

        const VertexArray& VA() const { return m_VA; }
        const VertexBuffer& VB() const { return m_VB; }
        const IndexBuffer& IB() const { return m_IB; }

    private:
        void SetupMesh();

    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<ImageTexture> m_textures;

        VertexArray m_VA;
        VertexBuffer m_VB;
        IndexBuffer m_IB;
    };

}