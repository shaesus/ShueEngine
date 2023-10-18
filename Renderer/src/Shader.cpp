#include "Shader.h"

#include "glad/glad.h"

#include <iostream>

#include "Renderer.h"

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
	: m_ID(0)
{
	m_ID = CreateShader(vertexShaderSource, fragmentShaderSource);
	GLCall(glUseProgram(m_ID));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_ID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_ID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

unsigned int Shader::CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	GLCall(unsigned int shaderProgram = glCreateProgram());
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	GLCall(glAttachShader(shaderProgram, vertexShader));
	GLCall(glAttachShader(shaderProgram, fragmentShader));
	GLCall(glLinkProgram(shaderProgram));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return shaderProgram;
}

unsigned int Shader::CompileShader(unsigned int type, const char* shaderSource)
{
	GLCall(unsigned int shader = glCreateShader(type));
	GLCall(glShaderSource(shader, 1, &shaderSource, nullptr));
	GLCall(glCompileShader(shader));

	int result;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shader, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int v)
{
	GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end())
		return m_UniformLocationsCache[name];

	GLCall(int location = glGetUniformLocation(m_ID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_UniformLocationsCache[name] = location;
	return location;
}
