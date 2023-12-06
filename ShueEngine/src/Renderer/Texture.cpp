#include "Texture.h"

#include "glad/glad.h"

#include "Renderer.h"

namespace Shue {

	Texture::Texture()
		: m_ID(0), m_Width(0), m_Height(0), m_BPP(0), m_LocalBuffer(nullptr)
	{
		GLCall(glGenTextures(1, &m_ID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_ID));
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

}