#pragma once

#include "Core.h"
#include "Events/Event.h"

#include <iostream>

namespace Shue {

	class SHUE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};

}