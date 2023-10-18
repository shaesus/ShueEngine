#pragma once

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int CompileShader(unsigned int type, const char* shaderSource);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int v);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);

	int GetUniformLocation(const std::string& name);

private:
	unsigned int m_ID;
	std::unordered_map<std::string, int> m_UniformLocationsCache;
};