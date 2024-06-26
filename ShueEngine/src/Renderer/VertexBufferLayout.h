#pragma once

#include <vector>
#include <stdexcept>

#include "glad/glad.h"

namespace Shue {

	struct SHUE_API VertexBufferLayoutElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
			}
			return 0;
		}
	};

	class SHUE_API VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		template <typename T>
		void Push(unsigned int count)
		{
			std::runtime_error(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
		}

		//TODO Push<Vertex>

		inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferLayoutElement> m_Elements;
		unsigned int m_Stride;
	};

}