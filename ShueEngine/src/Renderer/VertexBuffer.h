#pragma once

#include "Core.h"

namespace Shue {

	class SHUE_API VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size, const void* data, unsigned int drawType);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_ID;
	};

}