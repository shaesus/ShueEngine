#pragma once

#include "Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "CharTexture.h"
#include "ImageTexture.h"
#include "Mesh.h"
#include "Model.h"

#include "Assertion.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>

namespace Shue {

	class SHUE_API Renderer
	{
	public:
		struct Character {
			Texture* Texture;  // ID handle of the glyph texture
			glm::ivec2   Size;       // Size of glyph
			glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
			unsigned int Advance;    // Offset to advance to next glyph
		};

		using Font = std::map<char, Character>;

	public:
		~Renderer();

		void InitGlad() const;
		void InitFreeType();

		void Clear() const;
		void ClearColor(float r, float g, float b, float a) const;
		void DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count) const;
		void DrawMesh(const Mesh& mesh, const Shader& shader) const;
		void DrawModel(const Model& model, const Shader& shader) const;
		void AddFont(const std::string& fontPath, const std::string& name);
		void RenderText(const VertexArray& va, const VertexBuffer& vb, Shader& shader,
			const std::string& text, float x, float y, float scale, const glm::vec3& color, const std::string& fontName);
		void SetFrontFace(unsigned int mode = GL_CCW) const;
		void SetBlending(bool blending, unsigned int sfactor = GL_SRC_ALPHA, unsigned int dfactor = GL_ONE_MINUS_SRC_ALPHA);
		void SetCulling(bool culling, unsigned int mode = GL_BACK);
		void SetDepthTest(bool depthTest, GLboolean depthMask = GL_TRUE, GLenum func = GL_LESS);

		inline bool Blending() const { return m_Blending; }
		inline bool Culling() const { return m_Culling; }
		inline bool DepthTest() const { return m_DepthTest; }

	private:
		Font* CreateFont(const std::string& fontPath);

	private:
		FT_Library m_Ft;
		std::map<std::string, Font*> m_Fonts;

		bool m_Blending = false;
		bool m_Culling = false;
		bool m_DepthTest = false;
	};

}