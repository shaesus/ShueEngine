#include "Material.h"

namespace Shue {

	Material::Material(int diffuseMap, glm::vec3 specular, float shininess)
	{
		m_DiffuseMap = diffuseMap;
		m_Specular = specular;
		m_Shininess = shininess;
	}

}