#include <Ladoo.h>
#include <Ladoo/Base/EntryPoint.h>

#include "Ladoo2D.h"

class Sandbox : public Ladoo::Application
{
public: 
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Ladoo2D());
	}

	~Sandbox()
	{

	}
};

Ladoo::Application* Ladoo::CreateApplication()
{
	return new Sandbox();
}