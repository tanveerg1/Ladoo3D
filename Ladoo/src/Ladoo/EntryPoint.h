#pragma once

#ifdef LD_PLATFORM_WINDOWS

extern Ladoo::Application* Ladoo::CreateApplication();

int main(int argc, char** argv) 
{

	Ladoo::Log::Init();
	LD_CORE_WARN("Initialized Log!");
	int a = 5;
	LD_INFO("Hello! Var={0}", a);

	auto app = Ladoo::CreateApplication();
	app->Run();
	delete app;
}

#endif