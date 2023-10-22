#include "IndexBuffer.h"

#include "Renderer.h"

namespace Shue {

	IndexBuffer::IndexBuffer(unsigned int size, const void* data)
		: m_ID(0), m_Size(size)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}