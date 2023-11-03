#pragma once

#include "Core.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Shue {

	class SHUE_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_ID;
	};

}