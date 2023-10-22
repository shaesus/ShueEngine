#pragma once

namespace Shue {

	class Texture
	{
	public:
		Texture(const char* filePath);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

	private:
		unsigned int m_ID;
		int m_Width, m_Height, m_BPP;
		unsigned char* m_LocalBuffer;
	};

}