#pragma once

#include "Core.h"

#include "glm/glm.hpp"

namespace Shue {

	class SHUE_API Material
	{
	public:
		Material(int diffuseMap, int specular, float shininess)
			: m_DiffuseMap(diffuseMap), m_Specular(specular), m_Shininess(shininess) {}

		inline const int DiffuseMap() const { return m_DiffuseMap; }
		inline const int Specular() const { return m_Specular; }
		inline float Shininess() const { return m_Shininess; }

	private:
		int m_DiffuseMap;
		int m_Specular;
		float m_Shininess;
	};

}