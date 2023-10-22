#pragma once

#ifdef SH_PLATFORM_WINDOWS

extern Shue::Application* Shue::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Shue::CreateApplication();
	app->Run();
	delete app;
}

#endif