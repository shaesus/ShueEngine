#pragma once

#include "Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "Assertion.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>

namespace Shue {

	class SHUE_API Renderer
	{
	public:
		struct Character {
			unsigned int TextureID;  // ID handle of the glyph texture
			glm::ivec2   Size;       // Size of glyph
			glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
			unsigned int Advance;    // Offset to advance to next glyph
		};

		void Clear() const;
		void ClearColor(float r, float g, float b, float a) const;
		void DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count);
		void RenderText(const VertexArray& va, const VertexBuffer& vb, Shader& shader,
			const std::string& text, float x, float y, float scale, const glm::vec3& color);
		void InsertCharacter(char c, Character character);
		void SetBlending(bool blending, unsigned int sfactor = GL_SRC_ALPHA, unsigned int dfactor = GL_ONE_MINUS_SRC_ALPHA);

	private:
		std::map<char, Character> m_Characters;
	};

}