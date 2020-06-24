#pragma once

#ifdef LD_PLATFORM_WINDOWS

extern Ladoo::Application* Ladoo::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Ladoo::CreateApplication();
	app->Run();
	delete app;
}

#endif