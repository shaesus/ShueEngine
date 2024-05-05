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

        const std::vector<Vertex>& Vertices() const { return m_Vertices; }
        const std::vector<unsigned int>& Indices() const { return m_Indices; }
        const std::vector<ImageTexture>& Textures() const { return m_Textures; }

        /*inline const VertexArray& VA() const { return m_VA; }
        inline const VertexBuffer& VB() const { return m_VB; }
        inline const IndexBuffer& IB() const { return m_IB; }*/

        inline unsigned int VA() const { return m_VAO; }
        inline unsigned int VB() const { return m_VBO; }
        inline unsigned int EB() const { return m_EBO; }

    private:
        void SetupMesh();

    private:
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
        std::vector<ImageTexture> m_Textures;

        /*VertexArray m_VA;
        VertexBuffer m_VB;
        IndexBuffer m_IB;*/

        unsigned int m_VAO, m_VBO, m_EBO;
    };

}