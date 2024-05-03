#include "Mesh.h"

#include "VertexBufferLayout.h";

namespace Shue {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ImageTexture> textures)
		: m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		SetupMesh();
	}

	void Mesh::SetupMesh()
	{
        m_VA.Bind();

        m_VB = VertexBuffer(m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
        m_IB = IndexBuffer(m_indices.size(), &m_indices[0]);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VA.AddBuffer(m_VB, layout);

        //// vertex positions
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //// vertex normals
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        //// vertex texture coords
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        m_VA.Unbind();
	}

}