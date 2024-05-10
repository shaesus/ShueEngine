#include "ImageTexture.h"

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "Renderer.h"

#include <sstream>

namespace Shue {

	ImageTexture::ImageTexture(const std::string& filePath, const std::string& type, const std::string& directory) : Texture(), 
		m_Path(filePath), m_Type(type)
	{
		stbi_set_flip_vertically_on_load(1);

		std::stringstream ss;
		ss << directory << filePath;
		std::string path = ss.str();

		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		if (m_LocalBuffer)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));

			stbi_image_free(m_LocalBuffer);
		}
	}

}