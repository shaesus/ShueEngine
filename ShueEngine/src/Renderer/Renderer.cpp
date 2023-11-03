#include "Renderer.h"

#include <iostream>

namespace Shue {

	void Renderer::Shutdown()
	{
		glfwTerminate();
	}

	int Renderer::InitGLFW()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return -1;
		}
		return 1;
	}

	int Renderer::InitGLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		return 1;
	}

	int Renderer::InitFreeType()
	{
		return 1;
	}

	void Renderer::GLFWSetOpenGLVersionAndProfile(int major, int minor, int profile)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
	}

	void Renderer::Clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::ClearColor(float r, float g, float b, float a) const
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	}

	void Renderer::DrawIb(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		va.Bind();
		ib.Bind();
		shader.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::DrawTriangles(const VertexArray& va, const Shader& shader, unsigned int count)
	{
		va.Bind();
		shader.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
	}

	void Renderer::SetBlending(bool blending, unsigned int sfactor, unsigned int dfactor)
	{
		if (blending)
		{
			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(sfactor, dfactor));
		}
		else
		{
			GLCall(glDisable(GL_BLEND));
		}
	}

}