#include "Renderer.h"

#include <iostream>

namespace Shue {

	Renderer::~Renderer()
	{
		for (auto& [str, font] : m_Fonts)
		{
			for (auto& [c, character] : *font)
				delete character.Texture;
			delete font;
		}

		FT_Done_FreeType(m_Ft);
	}

	void Renderer::InitGlad() const
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	void Renderer::InitFreeType()
	{
		if (FT_Init_FreeType(&m_Ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}
	}

	void Renderer::Clear() const
	{
		GLCall(glClear(m_DepthTest ? GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT : GL_COLOR_BUFFER_BIT));
	}

	void Renderer::ClearColor(float r, float g, float b, float a) const
	{
		GLCall(glClearColor(r, g, b, a));
	}

	void Renderer::ClearColor(const glm::vec4& rgba) const
	{
		GLCall(glClearColor(rgba.r, rgba.g, rgba.b, rgba.a));
	}

	void Renderer::DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		va.Bind();
		ib.Bind();
		shader.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr));
		va.Unbind();
		ib.Unbind();
		shader.Unbind();
	}

	void Renderer::DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count) const
	{
		va.Bind();
		shader.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
		va.Unbind();
		shader.Unbind();
	}

	void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader) const
	{
		/*unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		const auto& textures = mesh.Textures();*/
		const auto& indices = mesh.Indices();
		/*for (unsigned int i = 0; i < textures.size(); i++)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			std::string number;
			std::string name = textures[i].Type();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.Bind();
			shader.SetUniform1i(("u_Material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID());
		}
		GLCall(glActiveTexture(GL_TEXTURE0));*/
		
		GLCall(glBindVertexArray(mesh.VA()));
		shader.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
		GLCall(glBindVertexArray(0));
		shader.Unbind();
	}

	void Renderer::DrawModel(const Model& model, const Shader& shader) const
	{
		for (const Mesh& mesh : model.Meshes())
			DrawMesh(mesh, shader);
	}

	void Renderer::AddFont(const std::string& fontPath, const std::string& name)
	{
		Font* font = CreateFont(fontPath);
		if (font) m_Fonts.insert(std::pair<std::string, Font*>(name, font));
	}

	void Renderer::DrawText(const VertexArray& va, const VertexBuffer& vb, Shader& shader, 
		const std::string& text, float x, float y, float scale, const glm::vec3& color, const std::string& fontName)
	{
		shader.Bind();
		shader.SetUniform3f("u_TextColor", color.x, color.y, color.z);
		va.Bind();

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = (*m_Fonts[fontName])[*c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[6][5] = {
				{ xpos,     ypos + h, 0.0f, 0.0f, 0.0f },
				{ xpos,     ypos,     0.0f, 0.0f, 1.0f },
				{ xpos + w, ypos,     0.0f, 1.0f, 1.0f },

				{ xpos,     ypos + h, 0.0f, 0.0f, 0.0f },
				{ xpos + w, ypos,     0.0f, 1.0f, 1.0f },
				{ xpos + w, ypos + h, 0.0f, 1.0f, 0.0f }
			};
			// render glyph texture over quad
			ch.Texture->Bind();
			// update content of VBO memory
			vb.BufferSubData(sizeof(vertices), vertices);
			// render quad
			DrawTriangles(va, shader, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}

		va.Unbind();
		shader.Unbind();
	}

	void Renderer::DrawLines(const VertexArray& va, const Shader& shader, unsigned int count) const
	{
		va.Bind();
		shader.Bind();
		GLCall(glDrawArrays(GL_LINES, 0, count));
		va.Unbind();
		shader.Unbind();
	}

	void Renderer::SetFrontFace(unsigned int mode) const
	{
		GLCall(glFrontFace(mode));
	}

	void Renderer::SetBlending(bool blending, unsigned int sfactor, unsigned int dfactor)
	{
		m_Blending = blending;

		if (blending)
		{
			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(sfactor, dfactor));
		}
		else
		{
			GLCall(glDisable(GL_BLEND));
		}
	}

	void Renderer::SetCulling(bool culling, unsigned int mode)
	{
		m_Culling = culling;

		if (culling)
		{
			GLCall(glEnable(GL_CULL_FACE));
			GLCall(glCullFace(mode));
		}
		else
		{
			GLCall(glDisable(GL_CULL_FACE));
		}
	}

	void Renderer::SetDepthTest(bool depthTest, GLboolean depthMask, GLenum func)
	{
		m_DepthTest = depthTest;

		if (depthTest)
		{
			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glDepthMask(depthMask));
			GLCall(glDepthFunc(func));
		}
		else
		{
			GLCall(glDisable(GL_DEPTH_TEST));
		}
	}

	VertexArray& Renderer::GetLineVA(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		float lineVertices[] = {
			x1, y1, z1,
			x2, y2, z2
		};
		Shue::VertexArray* lineVA = new VertexArray();
		lineVA->Bind();
		Shue::VertexBuffer lineVB(sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
		Shue::VertexBufferLayout lineLayout;
		lineLayout.Push<float>(3);
		lineVA->AddBuffer(lineVB, lineLayout);
		lineVA->Unbind();
		return *lineVA;
	}

	Renderer::Font* Renderer::CreateFont(const std::string& fontPath)
	{
		Font* font = new Font;

		FT_Face face;
		if (FT_New_Face(m_Ft, fontPath.c_str(), 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return nullptr;
		}

		FT_Set_Pixel_Sizes(face, 0, 48);

		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // disable byte-alignment restriction

		for (unsigned char c = 0; c < 128; c++)
		{
			// load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			CharTexture* texture = new CharTexture(face);

			// now store character for later use
			Renderer::Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			font->insert(std::pair<char, Renderer::Character>(c, character));
		}

		FT_Done_Face(face);

		return font;
	}

}