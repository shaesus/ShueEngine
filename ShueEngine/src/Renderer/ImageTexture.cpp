#include "ImageTexture.h"

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "Renderer.h"

namespace Shue {

	ImageTexture::ImageTexture(const char* filePath, const std::string& type) : Texture(), 
		m_Type(type)
	{
		stbi_set_flip_vertically_on_load(1);

		m_LocalBuffer = stbi_load(filePath, &m_Width, &m_Height, &m_BPP, 4);

		if (m_LocalBuffer)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));

			stbi_image_free(m_LocalBuffer);
		}
	}

}