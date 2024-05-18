#pragma once

#include "Core.h"

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

#include "Material.h"
#include "LightProperties.h"

namespace Shue {

	struct SHUE_API ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class SHUE_API Shader
	{
	public:
		Shader() : m_ID(0) {}
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform3f(const std::string& name, float v0, float v1, float v2) const;
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
		void SetUniformVec3(const std::string& name, glm::vec3 vector3) const;
		void SetUniformVec4(const std::string& name, glm::vec4 vector4) const;
		void SetUniform1i(const std::string& name, int v) const;
		void SetUniform1f(const std::string& name, float v) const;
		void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix) const;
		void SetUniformMaterial(const std::string& name, const Material& material) const;
		void SetUniformLightProperties(const std::string& name, const LightProperties& light) const;
	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
		int GetUniformLocation(const std::string& name) const;
	private:
		unsigned int m_ID;
		mutable std::unordered_map<std::string, int> m_UniformLocationsCache;
	};

}