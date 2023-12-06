#pragma once

#include "Core.h"

namespace Shue {

	class SHUE_API Texture
	{
	public:
		virtual ~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

	protected:
		Texture();

	protected:
		unsigned int m_ID;
		int m_Width, m_Height, m_BPP;
		unsigned char* m_LocalBuffer;
	};

}