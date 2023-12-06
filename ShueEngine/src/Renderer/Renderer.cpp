#include "Renderer.h"

#include <iostream>

namespace Shue {

	Renderer::~Renderer()
	{
		for (auto& [str, font] : m_Fonts)
		{
			for (auto& [c, character] : *font)
			{
				delete character.Texture;
			}
			delete font;
		}
	}

	void Renderer::Clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::ClearColor(float r, float g, float b, float a) const
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	}

	void Renderer::DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		va.Bind();
		ib.Bind();
		shader.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count)
	{
		va.Bind();
		shader.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
	}

	void Renderer::AddFont(FT_Library ft, const std::string& fontPath, const std::string& name)
	{
		Font* font = CreateFont(ft, fontPath);
		if (font) m_Fonts.insert(std::pair<std::string, Font*>(name, font));
	}

	void Renderer::RenderText(const VertexArray& va, const VertexBuffer& vb, Shader& shader, 
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
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
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
	}

	void Renderer::SetBlending(bool blending, unsigned int sfactor, unsigned int dfactor)
	{
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

	Renderer::Font* Renderer::CreateFont(FT_Library ft, const std::string& fontPath)
	{
		Font* font = new Font;

		FT_Face face;
		if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
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