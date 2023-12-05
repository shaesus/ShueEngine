#include "Renderer.h"

#include <iostream>

namespace Shue {

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

	void Renderer::RenderText(const VertexArray& va, const VertexBuffer& vb, Shader& shader, 
		const std::string& text, float x, float y, float scale, const glm::vec3& color)
	{
		// activate corresponding render state	
		shader.Bind();
		shader.SetUniform3f("u_TextColor", color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		va.Bind();

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = m_Characters[*c];

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
			GLCall(glBindTexture(GL_TEXTURE_2D, ch.TextureID));
			// update content of VBO memory
			vb.Bind();
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::InsertCharacter(char c, Character character)
	{
		m_Characters.insert(std::pair<char, Renderer::Character>(c, character));
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

}