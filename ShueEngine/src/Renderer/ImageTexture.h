#pragma once

#include "Texture.h"

#include <string>

namespace Shue {

	class SHUE_API ImageTexture : public Texture
	{
	public:
		ImageTexture(const char* filePath, const std::string& type = "");

		const std::string& Type() const { return m_Type; }

	private:
		std::string m_Type;
	};

}