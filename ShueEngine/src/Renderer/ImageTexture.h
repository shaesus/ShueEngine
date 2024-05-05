#pragma once

#include "Texture.h"

#include <string>

namespace Shue {

	class SHUE_API ImageTexture : public Texture
	{
	public:
		ImageTexture(const std::string& filePath, const std::string& type = "", const std::string& directory = "");

		inline const std::string& Type() const { return m_Type; }
		inline const std::string& Path() const { return m_Path; }

	private:
		std::string m_Path;
		std::string m_Type;
	};

}