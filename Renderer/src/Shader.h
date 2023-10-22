#pragma once

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

namespace Shue {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform1i(const std::string& name, int v);
		void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_ID;
		std::unordered_map<std::string, int> m_UniformLocationsCache;
	};

}