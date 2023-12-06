#pragma once

#include "Texture.h"

namespace Shue {

	class SHUE_API ImageTexture : public Texture
	{
	public:
		ImageTexture(const char* filePath);
	};

}