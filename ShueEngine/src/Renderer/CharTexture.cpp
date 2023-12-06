#include "CharTexture.h"

#include "glad/glad.h"

#include "Renderer.h"

namespace Shue {

	CharTexture::CharTexture(FT_Face face) : Texture()
	{
		m_Width = face->glyph->bitmap.width;
		m_Height = face->glyph->bitmap.rows;
		m_LocalBuffer = face->glyph->bitmap.buffer;

		if (m_LocalBuffer)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0,
				GL_RED, GL_UNSIGNED_BYTE, m_LocalBuffer));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}

}