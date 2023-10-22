#pragma once

#include "glad/glad.h"

namespace Shue {

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int size, const void* data);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetSize() const { return m_Size; }

	private:
		unsigned int m_ID;
		unsigned int m_Size;
	};

}