#pragma once

#include "Core.h"

#include "Entity.h"

#include <unordered_set>

namespace Shue {

	class SHUE_API Scene
	{
	private:
		std::unordered_set<Entity> m_sceneObjects;
	};

}