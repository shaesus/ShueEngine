#pragma once

#include "Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace Shue {

	class SHUE_API CharTexture : public Texture
	{
	public:
		CharTexture(FT_Face face);
	};

}