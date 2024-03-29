#include "VertexBuffer.h"

#include "glad/glad.h"

#include "Renderer.h"

namespace Shue {

	VertexBuffer::VertexBuffer(unsigned int size, const void* data, unsigned int drawType)
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawType));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::BufferSubData(unsigned int size, const void* data) const
	{
		Bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		Unbind();
	}

}