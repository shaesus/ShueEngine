#pragma once

#include "Core.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace Shue {

	class SHUE_API Texture
	{
	public:
		Texture();
		Texture(const char* filePath);
		Texture(FT_Face face);
		virtual ~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

	protected:
		unsigned int m_ID;
		int m_Width, m_Height, m_BPP;
		unsigned char* m_LocalBuffer;
	};

}