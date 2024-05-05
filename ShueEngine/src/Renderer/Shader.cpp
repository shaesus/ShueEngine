#include "Shader.h"

#include "glad/glad.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "Renderer.h"

namespace Shue {

	Shader::Shader(const std::string& filepath)
		: m_ID(0)
	{
		ShaderProgramSource	source = ParseShader(filepath);
		m_ID = CreateShader(source.VertexSource, source.FragmentSource);
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

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
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

	unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
	{
		GLCall(unsigned int shader = glCreateShader(type));
		const char* src = shaderSource.c_str();
		GLCall(glShaderSource(shader, 1, &src, nullptr));
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

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformVec3(const std::string& name, glm::vec3 vector)
	{
		SetUniform3f(name, vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform1i(const std::string& name, int v)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v));
	}

	void Shader::SetUniform1f(const std::string& name, float v)
	{
		GLCall(glUniform1f(GetUniformLocation(name), v));
	}

	void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	void Shader::SetUniformMaterial(const std::string& name, const Material& material)
	{
		SetUniform1i(name + ".diffuseMap", material.DiffuseMap());
		SetUniform1i(name + ".specularMap", material.Specular());
		SetUniform1f(name + ".shininess", material.Shininess());
	}

	void Shader::SetUniformLightProperties(const std::string& name, const LightProperties& light)
	{
		SetUniformVec3(name + ".position", light.Position());
		SetUniformVec3(name + ".ambient", light.Ambient());
		SetUniformVec3(name + ".diffuse", light.Diffuse());
		SetUniformVec3(name + ".specular", light.Specular());
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

}