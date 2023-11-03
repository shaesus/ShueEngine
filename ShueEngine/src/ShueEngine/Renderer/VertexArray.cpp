#include "VertexArray.h"

#include "Renderer.h"

#include "VertexBufferLayout.h"

namespace Shue {

	VertexArray::VertexArray()
		: m_ID(0)
	{
		GLCall(glGenVertexArrays(1, &m_ID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_ID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}