#include "LightProperties.h"

namespace Shue {

	Shue::LightProperties::LightProperties(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		m_Pos = pos;
		m_Ambient = ambient;
		m_Diffuse = diffuse;
		m_Specular = specular;
	}

}