#include "ShueEngine.h"

class Sandbox : public Shue::Application
{
public:
	Sandbox() 
	{
	}

	~Sandbox() 
	{
	}
};

Shue::Application* Shue::CreateApplication()
{
	return new Sandbox();
}